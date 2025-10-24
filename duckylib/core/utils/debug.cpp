#include "debug.h"

namespace DL {
void DL::Debug::Log(string message, Severity severity) {
  time_t time = std::time(nullptr);
  tm* currentTime = localtime(&time);

  string AMOrPM;
  int hour = currentTime->tm_hour;

  if (hour > 12) {
    AMOrPM = " PM";
    hour -= 12;
  } else {
    AMOrPM = " AM";
  }

  int minute = currentTime->tm_min;
  int second = currentTime->tm_sec;
  string timeString = (to_string(hour) + ":" + to_string(minute) + ":" +
                       to_string(second) + AMOrPM);

  int day = currentTime->tm_mday;
  int month = currentTime->tm_mon + 1;
  int year = currentTime->tm_year + 1900;
  string dateString =
      (to_string(year) + "-" + to_string(month) + "-" + to_string(day));

  string sev;

  switch (severity) {
    case Severity::MSG:
      sev = "MSG";
      break;
    case Severity::WRN:
      sev = "WRN";
      break;
    case Severity::ERR:
      sev = "ERR";
      break;
    default:
      sev = "MSG";
      break;
  }

  string line = timeString + " - [" + sev + "] " + message;

  WriteFile(("data/logs/" + dateString + ".log").c_str(), line.c_str());
}

void DL::Debug::WriteFile(const char* path, const char* content) {
  std::ofstream file;

  file.open(path, std::ios::app);
  file << content << std::endl;
  file.close();
}
}  // namespace DL