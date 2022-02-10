#
# robin.py
#

# Apply customizations for a MKS Robin
def prepare(address, ldname, fwname):
	import pioutil
	if pioutil.is_pio_build():
		import mvcnc
		def encrypt(source, target, env):
			mvcnc.encrypt_mks(source, target, env, fwname)
		mvcnc.relocate_firmware(address)
		mvcnc.custom_ld_script(ldname)
		mvcnc.add_post_action(encrypt);
