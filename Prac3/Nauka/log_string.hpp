#pragma once

#include <time.h>
#include <iostream>
#include <string>
#include "id.hpp"
#include "ip.hpp"

const Id NULL_ID(0, 0, 0);
const Ip NULL_IP(0, 0, 0, 0, 0);

struct LogString {
  struct tm time;
  int timems;

  Id id = NULL_ID;

  std::string classification = "";
  int priority = 0;
  std::string communication_type = "";  // {UDP} {TCP}

  Ip ip_sender = NULL_IP;
  Ip ip_receiver = NULL_IP;

  void set_time(time_t time_tmp, int ms);
  void set_null();

  std::string to_string();

  friend std::ostream& operator<<(std::ostream& os, const LogString& id);
};