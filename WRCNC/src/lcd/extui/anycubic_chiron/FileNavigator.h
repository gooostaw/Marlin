/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * lcd/extui/anycubic_chiron/FileNavigator.h
 *
 * Extensible_UI implementation for Anycubic Chiron
 * Written By Nick Wells, 2020 [https://github.com/SwiftNick]
 *  (not affiliated with Anycubic, Ltd.)
 */

#include "chiron_tft_defs.h"
#include "../ui_api.h"

using namespace ExtUI;

namespace Anycubic {

class FileNavigator {
  public:
    FileNavigator();
    static void reset();
    static void getFiles(uint16_t, panel_type_t, uint8_t filesneeded=4);
    static void upDIR();
    static void changeDIR(const char *);
    static void sendFile(panel_type_t);
    static void refresh();
    static void skiptofileindex(uint16_t);

    static FileList filelist;
  private:
    static uint16_t lastpanelindex;
    static uint16_t currentindex;
    static uint8_t  currentfolderdepth;
    static uint16_t currentfolderindex[MAX_FOLDER_DEPTH];
    static char     currentfoldername[MAX_PATH_LEN + 1];
};

extern FileNavigator filenavigator;

}
