/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * InterruptVectors_Due.h
 *
 * This module relocates the Interrupt vector table to SRAM, allowing new
 * interrupt handlers to be added at runtime. This is required because the
 * Arduino runtime steals interrupt handlers that Marlin MUST use to support
 * extended functionality such as USB hosts and USB devices (MSD, MTP) and
 * custom serial port handlers. Rather than modifying and/or recompiling the
 * Arduino runtime, We just want to run as much as possible on Stock Arduino.
 *
 * Copyright (c) 2017 Eduardo José Tagle. All right reserved
 */

#ifdef ARDUINO_ARCH_SAM

// ISR handler type
typedef void (*pfnISR_Handler)();

// Install a new interrupt vector handler for the given irq, returning the old one
pfnISR_Handler install_isr(IRQn_Type irq, pfnISR_Handler newHandler);

#endif // ARDUINO_ARCH_SAM
