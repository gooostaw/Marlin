/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "../gcode.h"

#include "../../module/planner.h"

/**
 * G8: Fake homing
 */
void GcodeSuite::G25()
{
    if (!parser.seen_test('X') && !parser.seen_test('Y') && !parser.seen_test('Z')) {
        set_axis_is_at_home(X_AXIS);
        set_axis_is_at_home(Y_AXIS);
        set_axis_is_at_home(Z_AXIS);
        SERIAL_ECHO("Fake home XYZ\n");
    } else {
        if (parser.seen_test('X')) {
            set_axis_is_at_home(X_AXIS);
            SERIAL_ECHO("Fake home X\n");
        }

        if (parser.seen_test('Y')) {
            set_axis_is_at_home(Y_AXIS);
            SERIAL_ECHO("Fake home Y\n");
        }

        if (parser.seen_test('Z')) {
            set_axis_is_at_home(Z_AXIS);
            SERIAL_ECHO("Fake home Z\n");
        }
    }

    report_current_position();
}