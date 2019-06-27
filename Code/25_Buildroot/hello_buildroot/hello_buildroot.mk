################################################################################
#
# hello_buildroot
#
################################################################################

HELLO_BUILDROOT_VERSION = 1.0.0
HELLO_BUILDROOT_SITE = $(TOPDIR)/../hello_buildroot
HELLO_BUILDROOT_SITE_METHOD = local

define HELLO_BUILDROOT_BUILD_CMDS
	$(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(@D)
endef

define HELLO_BUILDROOT_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/hello_buildroot $(TARGET_DIR)/usr/bin/hello_buildroot

	$(INSTALL) -D -m 0755 $(@D)/hello_buildroot-init $(TARGET_DIR)/etc/init.d/S90hello_buildroot	
endef

$(eval $(generic-package))