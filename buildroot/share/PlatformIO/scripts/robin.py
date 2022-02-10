#
# robin.py
#

# Apply customizations for a MKS Robin
def prepare(address, ldname, fwname):
	import pioutil
	if pioutil.is_pio_build():
		import wrcnc
		def encrypt(source, target, env):
			wrcnc.encrypt_mks(source, target, env, fwname)
		wrcnc.relocate_firmware(address)
		wrcnc.custom_ld_script(ldname)
		wrcnc.add_post_action(encrypt);
