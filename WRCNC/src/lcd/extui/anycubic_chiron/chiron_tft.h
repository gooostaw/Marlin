/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * lcd/extui/anycubic_chiron/chiron_tft.h
 *
 * Extensible_UI implementation for Anycubic Chiron
 * Written By Nick Wells, 2020 [https://github.com/SwiftNick]
 *  (not affiliated with Anycubic, Ltd.)
 */

#include "chiron_tft_defs.h"
#include "../../../inc/WRCNCConfigPre.h"
#include "../ui_api.h"

#if NONE(CHIRON_TFT_STANDARD, CHIRON_TFT_NEW)
  #define AUTO_DETECT_CHIRON_TFT 1
#endif

namespace Anycubic {

class ChironTFT {
  #if AUTO_DETECT_CHIRON_TFT
    static panel_type_t panel_type;
  #else
    static constexpr panel_type_t panel_type = TERN(CHIRON_TFT_NEW, AC_panel_new, AC_panel_standard);
  #endif
  static last_error_t last_error;
  static cnc_state_t  cnc_state;
  static paused_state_t   pause_state;
  static heater_state_t   hotend_state;
  static heater_state_t   hotbed_state;
  static xy_uint8_t       selectedmeshpoint;
  static char             panel_command[MAX_CMND_LEN + 1];
  static uint8_t          command_len;
  static char             selectedfile[MAX_PATH_LEN + 1];
  static float            live_Zoffset;
  static file_menu_t      file_menu;
  public:
    static void Startup();
    static void IdleLoop();
    static void CNCKilled(FSTR_P, FSTR_P);
    static void MediaEvent(media_event_t);
    static void TimerEvent(timer_event_t);
    static void FilamentRunout();
    static void ConfirmationRequest(const char * const);
    static void StatusChange(const char * const);
    static void PowerLossRecovery();
    static void CNCComplete();
    static void SendtoTFT(FSTR_P const=nullptr);
    static void SendtoTFTLN(FSTR_P const=nullptr);
  private:
    static void DetectPanelType();
    static bool ReadTFTCommand();
    static int8_t FindToken(char);
    static void CheckHeaters();
    static void SendFileList(int8_t);
    static void SelectFile();
    static void InjectCommandandWait(PGM_P);
    static void ProcessPanelRequest();
    static void PanelInfo(uint8_t);
    static void PanelAction(uint8_t);
    static void PanelProcess(uint8_t);
    static bool GetLastError();
};

extern ChironTFT Chiron;

} // Anycubic namespace
