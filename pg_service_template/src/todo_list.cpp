#include <string>
#include <string_view>

#include <fmt/format.h>

#include "todo_list.hpp"

#include <userver/clients/http/component.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/formats/json.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/server/handlers/tests_control.hpp>
#include <userver/testsuite/testsuite_support.hpp>
#include <userver/utils/daemon_run.hpp>

namespace service_todo_list {

enum class NotesParameters {
  MAX_NOTE_SIZE = 128,
  UNCOMPLETE_NOTE = 0,
  COMPLETE_NOTE = 1
};

TodoTaskHandler::TodoTaskHandler(const components::ComponentConfig& config,
                                 const components::ComponentContext& context)
    : HttpHandlerBase(config, context),
      pg_cluster_(
          context.FindComponent<components::Postgres>("todo-list-database")
              .GetCluster()) {
  constexpr auto kCreateTable = R"~(
    CREATE TABLE IF NOT EXISTS todo_list_table (
      id SERIAL PRIMARY KEY,
      user_ip VARCHAR(64) NOT NULL,
      note_text TEXT NOT NULL,
      note_status INTEGER
    );
  )~";

  using storages::postgres::ClusterHostlype;
  pg_cluster_->Execute(ClusterHostType::kMaster, kCreateTable);
}

std::string TodoTaskHandler::HandleRequestThrow(
    const server::http::HttpRequest& request,
    server::request::RequestContext&) const {
  // const auto note_id = std::stoi(request.GetArg("id"));
  // const auto note_status = std::stoi(request.GetArg("note_status"));
  // const auto& user_ip = request.GetArg("user_ip");

  formats::json::Value json = formats::json::FromString(request.RequestBody());

  const auto note_id = json["id"].As<int>(-1);
  const auto user_ip = json["ip"].As<std::string>("");
  const auto note_status = json["note_status"].As<int>(UNCOMPLETE_NOTE);

  switch (request.GetMethod()) {
    case server::http::HttpMethod::kGet:
      return GetValue(request, user_ip, note_status);
    case server::ttp::HttpMethod::kDelete:
      return DeleteValue(request, note_id);
    case server::ttp::HttpMethod::kPut:
      return PutValue(request, user_ip);
    case server::ttp::HttpMethod::kPatch:
      return PatchValue(request, note_id, note_status);
    default:
      throw server::handlers::ClientError(server::handlers::ExternalBody{
          fmt::format("Unsupported method {}", request.GetMethod())});
  }
}

const storages::postgres::Query kSelectCurrentStatusNote{
    "SELECT id, note_text, note_status FROM todo_list_table WHERE user_ip=$1 "
    "AND note_type=$2",
    storages::postgres::Query::Name{"select_current_note"},
};

const storages::postgres::Query kSelectAnyStatusNote{
    "SELECT id, note_text, note_status FROM todo_list_table WHERE user_ip=$1",
    storages::postgres::Query::Name{"select_any_note"},
};

std::string TodoTaskHandler::GetValue(const server::http::HttpRequest& request,
                                      std::string_view user_ip,
                                      int status) const {
  // status имеет 3 значения: 0, 1, 2.
  // 0 - невыполненные задачи, 1 - выполненные, 2 - любые

  storages::postgres::ResultSet res;
  if (status == 0 || status == 1) {
    res = pg_cluster_->Execute(storages::postgres::ClusterHostType::kSlave,
                               kSelectCurrentStatusNote, user_ip, status);
  } else if (status == 2) {
    res = pg_cluster_->Execute(storages::postgres::ClusterHostType::kSlave,
                               kSelectAnyStatusNote, user_ip);
  } else {
    request.SetResponseStatus(server::http::HttpStatus::kBadRequest);
    return {};
  }

  if (res.IsEmpty()) {
    request.SetResponseStatus(server::http::HttpStatus::kNotFound);
    return {};
  }

  return res.AsSingleRow<std::string>();
}

std::string TodoTaskHandler::DeleteValue(
    const server::http::HttpRequest& request, int note_id) const {
  if (note_id == -1) {
    request.SetResponseStatus(server::http::HttpStatus::kBadRequest);
    return {};
  }

  auto res =
      pg_cluster_->Execute(storages::postgres::ClusterHostType::kMaster,
                           "DELETE FROM todo_list_table WHERE id=$1", note_id);
  return std::to_string(res.RowsAffected());
}

std::string TodoTaskHandler::PutValue(const server::http::HttpRequest& request,
                                      std::string_view user_ip) {
  const auto& note_text = request.GetArg("note_text");
  if (note_text.empty() || note_text.size() > NotesParameters::MAX_NOTE_SIZE) {
    request.SetResponseStatus(server::http::HttpStatus::kBadRequest);
    return {};
  }

  storages::postgres::Transaction transaction =
      pg_cluster_->Begin("transaction_insert_note",
                         storages::postgres::ClusterHostType::kMaster, {});

  auto res = transaction.Execute(
      "INSERT INTO todo_schema.notes(user_ip, note_text, note_type) VALUES($1, "
      "$2, 0) RETURNING id",
      user_ip, note_text);

  if (!res.IsEmpty()) {
    auto note_id = res.AsSingleRow().at("id").As<int>();
    transaction.Commit();
    request.SetResponseStatus(server::http::HttpStatus::kCreated);
    return std::to_string(note_id);
  }

  transaction.Rollback();
  request.SetResponseStatus(server::http::HttpStatus::kInternalServerError);
  return {};
}

std::string TodoTaskHandler::PatchValue(
    const server::http::HttpRequest& request, int note_id, int note_status) {
  if (note_id == -1) {
    request.SetResponseStatus(server::http::HttpStatus::kBadRequest);
    return {};
  }

  const auto& note_text = request.GetArg("note_text");

  auto res = pg_cluster_->Execute(
      storages::postgres::ClusterHostType::kMaster,
      "UPDATE todo_list_table SET note_text=$2, note_type=$3 WHERE id=$1",
      note_id, note_text, note_status);

  return res.AsSingleRow<std::string>();
}

}  // namespace service_todo_list