################################################################################
#
# frequencimetro
#
################################################################################

FREQUENCIMETRO_VERSION = 1.0.0
FREQUENCIMETRO_SITE = $(TOPDIR)/../frequencimetro
FREQUENCIMETRO_SITE_METHOD = local
FREQUENCIMETRO_DEPENDENCIES = wiringpi

define FREQUENCIMETRO_BUILD_CMDS
	$(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(@D)
endef

define FREQUENCIMETRO_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/freq $(TARGET_DIR)/usr/bin/freq

	$(INSTALL) -D -m 0755 $(@D)/frequencimetro-init $(TARGET_DIR)/etc/init.d/S90frequencimetro
endef

$(eval $(generic-package))
