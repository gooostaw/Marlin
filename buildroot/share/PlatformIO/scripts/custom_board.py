#
# custom_board.py
#
# - For build.address replace VECT_TAB_ADDR to relocate the firmware
# - For build.ldscript use one of the linker scripts in buildroot/share/PlatformIO/ldscripts
#
import pioutil
if pioutil.is_pio_build():
	import wrcnc
	board = wrcnc.env.BoardConfig()

	address = board.get("build.address", "")
	if address:
		wrcnc.relocate_firmware(address)

	ldscript = board.get("build.ldscript", "")
	if ldscript:
		wrcnc.custom_ld_script(ldscript)
