#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
.SECONDARY:

#---------------------------------------------------------------------------------
# Check for devkitPPC
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITPPC)),)
$(error "Please set DEVKITPPC in your environment. export DEVKITPPC=<path to>devkitPPC")
endif

include $(DEVKITPPC)/wii_rules

#---------------------------------------------------------------------------------
# Project configuration
#---------------------------------------------------------------------------------

TARGET		:=	Wiither

BUILD		:=	build
SOURCES		:=	source source/graphics libwiigui
DATA		:=	data
TEXTURES	:=	textures
INCLUDES	:=	include libwiigui

#---------------------------------------------------------------------------------
# Compiler options
#---------------------------------------------------------------------------------

CFLAGS		=	-g -O2 -Wall $(MACHDEP) $(INCLUDE)
CXXFLAGS	=	$(CFLAGS) -std=gnu++20

LDFLAGS		=	-g $(MACHDEP) -Wl,-Map,$(notdir $@).map

#---------------------------------------------------------------------------------
# Libraries
#---------------------------------------------------------------------------------

LIBS		:=	-lwiiuse -lbte -logc -lm

LIBDIRS	:=

#---------------------------------------------------------------------------------
# Don't edit below this point unless you know why
#---------------------------------------------------------------------------------

ifneq ($(BUILD),$(notdir $(CURDIR)))

export OUTPUT	:=	$(CURDIR)/$(TARGET)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
			$(foreach dir,$(DATA),$(CURDIR)/$(dir)) \
			$(foreach dir,$(TEXTURES),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# Source files
#---------------------------------------------------------------------------------

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
sFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.S)))

BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

SCFFILES	:=	$(foreach dir,$(TEXTURES),$(notdir $(wildcard $(dir)/*.scf)))
TPLFILES	:=	$(SCFFILES:.scf=.tpl)

#---------------------------------------------------------------------------------
# Use CXX for linking C++ projects
#---------------------------------------------------------------------------------

ifeq ($(strip $(CPPFILES)),)
	export LD	:=	$(CC)
else
	export LD	:=	$(CXX)
endif

#---------------------------------------------------------------------------------
# Object files
#---------------------------------------------------------------------------------

export OFILES	:=	$(addsuffix .o,$(BINFILES)) \
			$(addsuffix .o,$(TPLFILES)) \
			$(CPPFILES:.cpp=.o) \
			$(CFILES:.c=.o) \
			$(sFILES:.s=.o) \
			$(SFILES:.S=.o)

#---------------------------------------------------------------------------------
# Include paths
#---------------------------------------------------------------------------------

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			-I$(CURDIR)/$(BUILD) \
			-I$(LIBOGC_INC)

#---------------------------------------------------------------------------------
# Library paths
#---------------------------------------------------------------------------------

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib) \
			-L$(LIBOGC_LIB)

export OUTPUT	:=	$(CURDIR)/$(TARGET)

.PHONY: all $(BUILD) clean run

#---------------------------------------------------------------------------------
# Build
#---------------------------------------------------------------------------------

all: $(BUILD)

$(BUILD):
	+@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
# Clean
#---------------------------------------------------------------------------------

clean:
	@echo clean ...
	@rm -fr $(BUILD) $(OUTPUT).elf $(OUTPUT).dol

#---------------------------------------------------------------------------------
# Run using wiiload
#---------------------------------------------------------------------------------

run:
	wiiload $(OUTPUT).dol

#---------------------------------------------------------------------------------
else

#---------------------------------------------------------------------------------
# Main targets
#---------------------------------------------------------------------------------

all: $(OUTPUT).dol

$(OUTPUT).dol: $(OUTPUT).elf
$(OUTPUT).elf: $(OFILES)

#---------------------------------------------------------------------------------
# Link binary data
#---------------------------------------------------------------------------------

%.bin.o: %.bin
	@echo $(notdir $<)
	$(bin2o)

#---------------------------------------------------------------------------------
# Link texture data
#---------------------------------------------------------------------------------

%.tpl.o: %.tpl
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
# Dependency files
#---------------------------------------------------------------------------------

-include $(DEPSDIR)/*.d

#---------------------------------------------------------------------------------
endif