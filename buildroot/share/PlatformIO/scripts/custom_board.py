#
# custom_board.py
#
# - For build.address replace VECT_TAB_ADDR to relocate the firmware
# - For build.ldscript use one of the linker scripts in buildroot/share/PlatformIO/ldscripts
#
import pioutil
if pioutil.is_pio_build():
	import mvcnc
	board = mvcnc.env.BoardConfig()

	address = board.get("build.address", "")
	if address:
		mvcnc.relocate_firmware(address)

	ldscript = board.get("build.ldscript", "")
	if ldscript:
		mvcnc.custom_ld_script(ldscript)
