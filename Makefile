#
# Makefile for EV3onRules
#
# created by Atsushi TAKEDA
# https://github.com/takedarts/ev3onrules
#

#
# Set path of EV3RT(hrp2) directory
EV3RT_DIR := hrp2

# Include configurations of EV3RT SDK
include $(EV3RT_DIR)/sdk/Makefile.sdk.conf

# Paths
OBJ_DIR  := $(CURDIR)/build
SRC_DIR  := $(CURDIR)/src
RES_DIR  := $(CURDIR)/res
TEMP_DIR := $(CURDIR)/template

# Source files
APPL_CSRCS := $(shell if [ -e $(SRC_DIR) ]; then find $(SRC_DIR) -type f -name '*.c' -print; fi)
APPL_COBJS := $(patsubst $(SRC_DIR)/%.c, %.o, $(APPL_CSRCS))
APPL_CXXSRCS := $(shell if [ -e $(SRC_DIR) ]; then find $(SRC_DIR) -type f -name '*.cpp' -print; fi)
APPL_CXXOBJS := $(patsubst $(SRC_DIR)/%.cpp, %.o, $(APPL_CXXSRCS))

# Make Configuration Files
append_mkincfile = echo "" >> $(OBJ_DIR)/Makefile.inc && \
                   echo "\# ---- added by Makefile ----" >> $(OBJ_DIR)/Makefile.inc && \
                   echo "APPL_COBJS += $(APPL_COBJS)" >> $(OBJ_DIR)/Makefile.inc && \
                   echo "APPL_CXXOBJS += $(APPL_CXXOBJS)" >> $(OBJ_DIR)/Makefile.inc
append_cfgfile = echo "" >> $(OBJ_DIR)/app.cfg && \
                 echo "/* ---- added by Makefile ---- */" >> $(OBJ_DIR)/app.cfg && \
                 echo $(foreach obj,$(APPL_CXXOBJS),ATT_MOD\(\"$(obj)\"\)\;) >> $(OBJ_DIR)/app.cfg

# Target for an application module
all: list $(SRC_DIR)/Factory.cpp $(SRC_DIR)/Include.h $(OBJ_DIR)/Makefile.app
	@cd $(OBJ_DIR) && \
	make -f Makefile.app module_cfg.h && \
	make -f Makefile.app -j8
	cp -f build/app app

list:
	@mkdir -p $(OBJ_DIR)
	@echo perl $(CURDIR)/util/list.pl
	@perl $(CURDIR)/util/list.pl "$(OBJ_DIR)/src.list" "$(APPL_CSRCS) $(APPL_CXXSRCS)"

rule:
	@perl $(CURDIR)/util/rule.pl "$(TEMP_DIR)" "$(SRC_DIR)"

filter:
	@perl $(CURDIR)/util/filter.pl "$(TEMP_DIR)" "$(SRC_DIR)"

clean:
	rm -rf $(OBJ_DIR)

# prepare a build directory 
$(OBJ_DIR)/Makefile.app: $(RES_DIR)/app.cfg $(OBJ_DIR)/src.list
	@mkdir -p $(OBJ_DIR)
	@echo perl $(CURDIR)/util/config.pl
	@perl $(CURDIR)/util/config.pl \
		"$(SRC_DIR)" "$(OBJ_DIR)" "$(RES_DIR)" "$(EV3RT_DIR)" "$(APPL_COBJS)" "$(APPL_CXXOBJS)"

# generate source files
$(SRC_DIR)/Factory.cpp: $(OBJ_DIR)/src.list
	@echo perl $(CURDIR)/util/factory.pl
	@perl $(CURDIR)/util/factory.pl "$(TEMP_DIR)" "$(SRC_DIR)"

$(SRC_DIR)/Include.h: $(OBJ_DIR)/src.list
	@echo perl $(CURDIR)/util/include.pl
	@perl $(CURDIR)/util/include.pl "$(TEMP_DIR)" "$(SRC_DIR)"

.PHONY: clean app all rule filter check
