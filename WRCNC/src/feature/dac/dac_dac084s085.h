/**
 * Webber Ranch CNC Firmware
*/
#pragma once

class dac084s085 {
  public:
    dac084s085();
    static void begin();
    static void setValue(const uint8_t channel, const uint8_t value);
  private:
    static void cshigh();
};
