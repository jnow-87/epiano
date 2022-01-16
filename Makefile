################
###   init   ###
################

mcu := atmega88


####
## build system config
####


# build system variables
scripts_dir := scripts/build
project_type := c
config := .config
config_tree := scripts/config
use_config_sys := y
config_ftype := Pconfig
githooks_tree := .githooks

# source- and build-tree
default_build_tree := build/
src_dirs := main/


####
## include build system Makefile
####

include $(scripts_dir)/main.make


####
## flags
####

# init default target flags
cflags := \
	$(CFLAGS) \
	$(CONFIG_CFLAGS) \
	$(cflags) \
	-Os \
	-Wall \
	-Wextra \
	-Wshadow \
	-Wno-unused-parameter \
	-Wno-unused-label \
	-Wno-unknown-pragmas \
	-fshort-enums \
	-flto \
	-mmcu=$(mcu)

cxxflags := \
	$(CXXFLAGS) \
	$(CONFIG_CXXFLAGS) \
	$(cxxflags) \
	-Os \
	-Wall \
	-Wextra \
	-Wshadow \
	-Wno-unused-parameter \
	-Wno-unused-label \
	-Wno-unknown-pragmas \
	-fshort-enums \
	-flto \
	-mmcu=$(mcu)

cppflags := \
	$(CPPFLAGS) \
	$(CONFIG_CPPFLAGS) \
	$(cppflags) \
	-std=gnu99 \
	-I"$(src_tree)/include/" \
	-I"$(build_tree)/" \
	-DF_CPU=$(CONFIG_MCU_CLOCK_HZ) \
	-D__DELAY_BACKWARD_COMPATIBLE__

ldlibs := \
	$(LDLIBS) \
	$(CONFIG_LDLIBS) \
	$(ldlibs) \
	-static \
	-mmcu=$(mcu)

ldflags := \
	$(LDFLAGS) \
	$(CONFIG_LDFLAGS) \
	$(ldflags)

asflags := \
	$(ASFLAGS) \
	$(CONFIG_ASFLAGS) \
	$(asflags)

archflags := \
	$(ARCHFLAGS) \
	$(CONFIG_ARCHFLAGS) \
	$(archflags)

# init default host flags
hostcflags := \
	$(HOSTCFLAGS) \
	$(CONFIG_HOSTCFLAGS) \
	$(hostcflags) \
	-Wall \
	-Wextra \
	-Wshadow \
	-Wno-unused-parameter \
	-Wno-unused-label \
	-Wno-unknown-pragmas \
	-O2 \
	-flto

hostcxxflags := \
	$(HOSTCXXFLAGS) \
	$(CONFIG_HOSTCCCFLAGS) \
	$(hostcxxflags) \
	-Wall \
	-Wextra \
	-Wshadow \
	-Wno-unused-parameter \
	-Wno-unused-label \
	-Wno-unknown-pragmas \
	-O2 \
	-flto

hostcppflags := \
	$(HOSTCPPFLAGS) \
	$(CONFIG_HOSTCPPFLAGS) \
	$(hostcppflags) \
	-std=gnu99 \
	-I"$(build_tree)/"

hostldlibs := \
	$(HOSTLDLIBS) \
	$(CONFIG_HOSTLDLIBS) \
	$(hostldlibs)

hostldflags := \
	$(HOSTLDFLAGS) \
	$(CONFIG_HOSTLDFLAGS) \
	$(hostldflags)

hostasflags := \
	$(HOSTASFLAGS) \
	$(CONFIG_HOSTASFLAGS) \
	$(hostasflags)

hostarchflags := \
	$(HOSTARCHFLAGS) \
	$(CONFIG_HOSTARCHFLAGS) \
	$(hostarchflags)

yaccflags := \
	$(YACCFLAGS) \
	$(yaccflags)

lexflags := \
	$(LEXFLAGS) \
	$(lexflags)

gperfflags := \
	$(GPERFFLAGS) \
	$(gperfflags)


###################
###   targets   ###
###################

####
## build
####

.PHONY: all
ifeq ($(CONFIG_BUILD_DEBUG),y)
  cflags += -g
  cxxflags += -g
  asflags += -g
  ldlibs += -g
  hostcflags += -g -O0
  hostcxxflags += -g -O0
  hostasflags += -g
  hostldlibs += -g
endif

all: $(lib) $(hostlib) $(bin) $(hostbin)

####
## cleanup
####

.PHONY: clean
clean:
	$(rm) $(filter-out $(patsubst %/,%,$(dir $(build_tree)/$(scripts_dir))),$(wildcard $(build_tree)/*))

.PHONY: distclean
distclean:
	$(rm) $(config) $(config).old $(recent) $(build_tree)
