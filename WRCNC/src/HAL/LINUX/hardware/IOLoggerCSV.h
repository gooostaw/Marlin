/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include <mutex>
#include <list>
#include <fstream>
#include "Gpio.h"

class IOLoggerCSV: public IOLogger {
public:
  IOLoggerCSV(std::string filename);
  virtual ~IOLoggerCSV();
  void flush();
  void log(GpioEvent ev);

private:
  std::ofstream file;
  std::list<GpioEvent> events;
  std::mutex vector_lock;
};
