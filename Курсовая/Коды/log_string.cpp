#include "log_string.hpp"
#include <sstream>
#include <string>

void LogString::set_time(time_t time_tmp, int ms) {
  time = *(gmtime(&time_tmp));
  timems = ms;
}

std::string LogString::to_string() {
  std::stringstream ss;
  ss << asctime(&time) << id << classification << " {Priority: " << priority
     << "} [Communication type: " << communication_type
     << "] || IP sender: " << ip_sender << ", IP receiver: " << ip_receiver
     << " ||" << std::endl;
  return ss.str();
}

void LogString::set_null() {
  priority = 0;
  id = NULL_ID;
  ip_sender = NULL_IP;
  ip_receiver = NULL_IP;
}

std::ostream& operator<<(std::ostream& os, const LogString& ls) {
  os << asctime(&ls.time) << ls.id << ls.classification
     << " {Priority: " << ls.priority
     << "} [Communication type: " << ls.communication_type
     << "] || IP sender: " << ls.ip_sender
     << ", IP receiver: " << ls.ip_receiver << " ||" << std::endl;
  return os;
}