/**
 * Webber Ranch CNC Firmware
*/
#ifdef TARGET_LPC1768

#include "MarlinSerial.h"

#include "../../inc/MarlinConfig.h"

#if USING_HW_SERIAL0
  MarlinSerial _MSerial0(LPC_UART0);
  MSerialT MSerial0(true, _MSerial0);
  extern "C" void UART0_IRQHandler() { _MSerial0.IRQHandler(); }
#endif
#if USING_HW_SERIAL1
  MarlinSerial _MSerial1((LPC_UART_TypeDef *) LPC_UART1);
  MSerialT MSerial1(true, _MSerial1);
  extern "C" void UART1_IRQHandler() { _MSerial1.IRQHandler(); }
#endif
#if USING_HW_SERIAL2
  MarlinSerial _MSerial2(LPC_UART2);
  MSerialT MSerial2(true, _MSerial2);
  extern "C" void UART2_IRQHandler() { _MSerial2.IRQHandler(); }
#endif
#if USING_HW_SERIAL3
  MarlinSerial _MSerial3(LPC_UART3);
  MSerialT MSerial3(true, _MSerial3);
  extern "C" void UART3_IRQHandler() { _MSerial3.IRQHandler(); }
#endif

#if ENABLED(EMERGENCY_PARSER)

  bool MarlinSerial::recv_callback(const char c) {
    // Need to figure out which serial port we are and react in consequence (Marlin does not have CONTAINER_OF macro)
    if (false) {}
    #if USING_HW_SERIAL0
      else if (this == &_MSerial0) emergency_parser.update(MSerial0.emergency_state, c);
    #endif
    #if USING_HW_SERIAL1
      else if (this == &_MSerial1) emergency_parser.update(MSerial1.emergency_state, c);
    #endif
    #if USING_HW_SERIAL2
      else if (this == &_MSerial2) emergency_parser.update(MSerial2.emergency_state, c);
    #endif
    #if USING_HW_SERIAL3
      else if (this == &_MSerial3) emergency_parser.update(MSerial3.emergency_state, c);
    #endif
    return true;
  }

#endif

#endif // TARGET_LPC1768
