/**
 * Modern Vintage CNC Firmware
*/

#include "../../inc/mvCNCConfig.h"

#if ENABLED(MORGAN_SCARA)

#include "../gcode.h"
#include "../../module/scara.h"
#include "../../module/motion.h"
#include "../../mvCNCCore.h" // for IsRunning()

inline bool SCARA_move_to_cal(const uint8_t delta_a, const uint8_t delta_b) {
  if (IsRunning()) {
    forward_kinematics(delta_a, delta_b);
    do_blocking_move_to_xy(cartes);
    return true;
  }
  return false;
}

/**
 * M360: SCARA calibration: Move to cal-position ThetaA (0 deg calibration)
 */
bool GcodeSuite::M360() {
  SERIAL_ECHOLNPGM(" Cal: Theta 0");
  return SCARA_move_to_cal(0, 120);
}

/**
 * M361: SCARA calibration: Move to cal-position ThetaB (90 deg calibration - steps per degree)
 */
bool GcodeSuite::M361() {
  SERIAL_ECHOLNPGM(" Cal: Theta 90");
  return SCARA_move_to_cal(90, 130);
}

/**
 * M362: SCARA calibration: Move to cal-position PsiA (0 deg calibration)
 */
bool GcodeSuite::M362() {
  SERIAL_ECHOLNPGM(" Cal: Psi 0");
  return SCARA_move_to_cal(60, 180);
}

/**
 * M363: SCARA calibration: Move to cal-position PsiB (90 deg calibration - steps per degree)
 */
bool GcodeSuite::M363() {
  SERIAL_ECHOLNPGM(" Cal: Psi 90");
  return SCARA_move_to_cal(50, 90);
}

/**
 * M364: SCARA calibration: Move to cal-position PsiC (90 deg to Theta calibration position)
 */
bool GcodeSuite::M364() {
  SERIAL_ECHOLNPGM(" Cal: Theta-Psi 90");
  return SCARA_move_to_cal(45, 135);
}

#endif // MORGAN_SCARA
