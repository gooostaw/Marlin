/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * Low level pin manipulation routines - used by all the drivers.
 *
 * These are based on the LPC1768 pinMode, digitalRead & digitalWrite routines.
 *
 * Couldn't just call exact copies because the overhead killed the LCD update speed
 * With an intermediate level the softspi was running in the 10-20kHz range which
 * resulted in using about about 25% of the CPU's time.
 */

void u8g_SetPinOutput(uint8_t internal_pin_number);
void u8g_SetPinInput(uint8_t internal_pin_number);
void u8g_SetPinLevel(uint8_t  pin, uint8_t  pin_status);
uint8_t u8g_GetPinLevel(uint8_t pin);
