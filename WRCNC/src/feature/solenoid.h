/**
 * Webber Ranch CNC Firmware
*/
#pragma once

void enable_solenoid_on_active_extruder();
void disable_all_solenoids();
void enable_solenoid(const uint8_t num);
void disable_solenoid(const uint8_t num);
