/**
 * Modern Vintage CNC Firmware
*/

#include "stopwatch.h"

#include "../inc/mvCNCConfig.h"

#if ENABLED(EXTENSIBLE_UI)
  #include "../lcd/extui/ui_api.h"
#endif

Stopwatch::State Stopwatch::state;
millis_t Stopwatch::accumulator;
millis_t Stopwatch::startTimestamp;
millis_t Stopwatch::stopTimestamp;

bool Stopwatch::stop() {
  debug(F("stop"));

  if (isRunning() || isPaused()) {
    TERN_(EXTENSIBLE_UI, ExtUI::onPrintTimerStopped());
    state = STOPPED;
    stopTimestamp = millis();
    return true;
  }
  else return false;
}

bool Stopwatch::pause() {
  debug(F("pause"));

  if (isRunning()) {
    TERN_(EXTENSIBLE_UI, ExtUI::onPrintTimerPaused());
    state = PAUSED;
    stopTimestamp = millis();
    return true;
  }
  else return false;
}

bool Stopwatch::start() {
  debug(F("start"));

  TERN_(EXTENSIBLE_UI, ExtUI::onPrintTimerStarted());

  if (!isRunning()) {
    if (isPaused()) accumulator = duration();
    else reset();

    state = RUNNING;
    startTimestamp = millis();
    return true;
  }
  else return false;
}

void Stopwatch::resume(const millis_t with_time) {
  debug(F("resume"));

  reset();
  if ((accumulator = with_time)) state = RUNNING;
}

void Stopwatch::reset() {
  debug(F("reset"));

  state = STOPPED;
  startTimestamp = 0;
  stopTimestamp = 0;
  accumulator = 0;
}

millis_t Stopwatch::duration() {
  return accumulator + MS_TO_SEC((isRunning() ? millis() : stopTimestamp) - startTimestamp);
}

#if ENABLED(DEBUG_STOPWATCH)

  void Stopwatch::debug(FSTR_P const func) {
    if (DEBUGGING(INFO)) SERIAL_ECHOLNPGM("Stopwatch::", func, "()");
  }

#endif
