/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/MarlinConfig.h"

#if HAS_PRUSA_MMU1

#include "../../MarlinCore.h"
#include "../../module/planner.h"
#include "../../module/stepper.h"

void mmu_init() {
  SET_OUTPUT(E_MUX0_PIN);
  SET_OUTPUT(E_MUX1_PIN);
  SET_OUTPUT(E_MUX2_PIN);
}

void select_multiplexed_stepper(const uint8_t e) {
  planner.synchronize();
  stepper.disable_e_steppers();
  WRITE(E_MUX0_PIN, TEST(e, 0) ? HIGH : LOW);
  WRITE(E_MUX1_PIN, TEST(e, 1) ? HIGH : LOW);
  WRITE(E_MUX2_PIN, TEST(e, 2) ? HIGH : LOW);
  safe_delay(100);
}

#endif // HAS_PRUSA_MMU1
