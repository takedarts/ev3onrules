#
# Makefile for a Loadable User Module for EV3onRules
#
# Edited by Atsushi TAKEDA ( https://github.com/takedarts/ev3onrules )
# An original file is in TOPPERS/EV3RT version beta6-3
#   created by TOPPERS project ( https://www.toppers.jp/ )
#

#
# Makefile for a Loadable User Module (LEGO Mindstorms EV3)
#

# Specify the directory of HRP2 source
KERNELDIR = @(EV3RT_DIR)
TARGETDIR = $(KERNELDIR)/target/ev3_gcc
LOADERDIR = $(KERNELDIR)/target/ev3_gcc/dmloader
APPLDIR   = @(SRC_DIR)
APPL_DIR  = $(APPLDIR)
SRCDIRS  += $(APPL_DIR) $(KERNELDIR)/target/ev3_gcc/TLSF-2.4.6/src

#
# Include the common Makefile of an EV3RT project
#
include Makefile.prj

# Compiler options
COPTS += -DBUILD_MODULE
GCC_TARGET = arm-none-eabi
INCLUDES += -I@(SRC_DIR) \
			-I@(EV3RT_DIR)/sdk/common \
			-I$(LOADERDIR)/app \
			-I$(KERNELDIR)/target/ev3_gcc \
			-I$(KERNELDIR)/target/ev3_gcc/drivers/common/include \
			-I$(KERNELDIR)/arch/arm_gcc/am1808 \
			-I$(KERNELDIR)/arch/arm_gcc/common \
		   	-I$(KERNELDIR)/target/ev3_gcc/TLSF-2.4.6/include \
		   	-I$(KERNELDIR)/target/ev3_gcc/platform/include \
		   	-I$(KERNELDIR)/target/ev3_gcc/pil/include
INCLUDES += $(PROJECT_INCLUDE)


OBJNAME = app

OBJFILE = $(OBJNAME)

all: $(OBJFILE)

MODOBJS += t_perror.o strerror.o vasyslog.o tlsf.o

MODCFG = app.cfg

MODDIR = $(PWD)

OMIT_DEBUG_INFO = 1

#
# Include common part
#
BUILD_LOADABLE_MODULE = 1
CONFIG_EV3RT_APPLICATION = 1
include Makefile.inc
ifeq ($(SRCLANG),c++)
  USE_CXX = true
  APPL_CXXOBJS +=
  CXXLIBS = -lstdc++ -lc -lm -lgcc
  #CXXRTS = crtbegin.o crtend.o
  #CXXRTS = cxxrt.o newlibrt.o
else
  MODOBJS +=
endif
#include $(KERNELDIR)/target/ev3_gcc/api/Makefile
MODOBJS += $(APPL_COBJS)

include Makefile.lum
