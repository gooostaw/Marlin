/**
 * Webber Ranch CNC Firmware
*/
#pragma once

// Perform a backtrace to the serial port
void backtrace();

// Perform a backtrace to the serial port
void backtrace_ex(unsigned long sp, unsigned long lr, unsigned long pc);
