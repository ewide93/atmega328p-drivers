#================================================================================
# Shell configurations.
#================================================================================
SHELL := bash
.SHELLFLAGS := -eu -o pipefail -c

#================================================================================
# Make configurations.
#================================================================================
MAKEFLAGS += --no-builtin-rules
MAKEFLAGS += --warn-undefined-variables
ifdef NUMBER_OF_PROCESSORS
	NUM_CORES := $(NUMBER_OF_PROCESSORS)
else
	NUM_CORES := 4
endif
MAKEFLAGS += -j$(NUM_CORES)

#================================================================================
# Define paths for project directory, define variables for build.
#================================================================================
SCRIPT_DIR = scripts
SRC_DIR = src
INC_DIR = inc
AVR_INC_DIR = C:/tools/avr8-gnu-toolchain/avr/include
BUILD_DIR = build

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))
DEP_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.d,$(SRC_FILES))

#================================================================================
# Compiler & toolchain configurations.
#================================================================================
TARGET := atmega328p-driver
CC := avr-gcc
OBJCOPY := avr-objcopy
AVRDUDE := avrdude
SIZE := avr-size

# Flash programming options.
PORT := COM6
PROGRAMMER := arduino
BAUD_RATE := 115200

# Hardware specific options.
MCU := atmega328p
F_CPU := 16000000UL

# Linter options.
LINTER := cppcheck
LINTER_CACHE_DIR = build/cppcheck_cache
LINTFLAGS = --enable=all --quiet --std=c99
LINTFLAGS += --platform=avr8 --cppcheck-build-dir=$(LINTER_CACHE_DIR)
LINT_INC = -I$(INC_DIR)
LINT_SUPPRESS = --suppress=missingIncludeSystem --suppress=unusedFunction

# Compilation options.
CFLAGS = -std=gnu99 -I$(INC_DIR) -I$(AVR_INC_DIR)
CFLAGS += -mmcu=$(MCU) -DF_CPU=$(F_CPU)
CFLAGS += -ffunction-sections -fdata-sections -fshort-enums -g3

# Compilation warnings.
CWARN = -Wall -Wextra -Wpedantic -Werror
CWARN += -Wunused-variable -Wunused-parameter -Wstrict-prototypes
CWARN += -Wshadow -Wold-style-definition -Wredundant-decls
CWARN += -Wnested-externs -Wmissing-include-dirs -Wjump-misses-init
CWARN += -Wlogical-op

# Dependency file generation.
DFLAGS = -MMD -MP

# Linker options.
LDFLAGS += -mmcu=$(MCU) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map -Wl,--cref
LDFLAGS += -Wl,--gc-sections

# Optimization level.
OPT := -O2

#================================================================================
# Unit test toolchain configuration.
#================================================================================
UT_DIR := unittests
TEST_MAKEFILES := $(wildcard $(UT_DIR)/*.mk)

#================================================================================
# Rule to invoke all rules necessary to produce the .hex-file.
#================================================================================
.PHONY: all
all: $(BUILD_DIR)/$(TARGET).hex
	@echo 'Compilation successful!'

#================================================================================
# Convert .elf-file to .hex-file.
#================================================================================
$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	@$(OBJCOPY) -j .text -j .data -O ihex $< $@
	@echo 'Generating binary image...'

#================================================================================
# Rule to link object files into .elf-file and .map-file.
#================================================================================
$(BUILD_DIR)/$(TARGET).elf: $(OBJ_FILES)
	@$(CC) $(LDFLAGS) $^ -o $@
	@echo 'Linking...'

#================================================================================
# Rule to compile source files into object files.
#================================================================================
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(CWARN) $(DFLAGS) $(OPT) -c $< -o $@
	@echo 'Compiling $<'

#================================================================================
# Rule to flash the .hex-file to the MCU.
#================================================================================
.PHONY: flash
flash: $(BUILD_DIR)/$(TARGET).hex
	@$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD_RATE) -U flash:w:$<

#================================================================================
# Rule to display memory resource utilization.
#================================================================================
.PHONY: size
size: $(BUILD_DIR)/$(TARGET).elf
	@$(SIZE) --mcu=$(MCU) --radix=10 --format=avr $^

#================================================================================
# Rule to remove build artefacts and outputs.
#================================================================================
.PHONY: clean
clean:
	@echo 'Cleaning project directory...'
	@rm -rf $(BUILD_DIR)/*.o
	@rm -rf $(BUILD_DIR)/*.d
	@rm -rf $(BUILD_DIR)/*.elf
	@rm -rf $(BUILD_DIR)/*.hex
	@rm -rf $(BUILD_DIR)/*.map
	@rm -rf $(TARGET)

#================================================================================
# Rule for running linter.
#================================================================================
.PHONY: lint
lint:
	@$(LINTER) $(LINTFLAGS) $(LINT_INC) $(LINT_SUPPRESS) $(SRC_DIR)

#================================================================================
# Rule to build & run unit tests.
#================================================================================
.PHONY: test
test:
	@$(MAKE) --makefile=$(UT_DIR)/test_lrc.mk
	@$(MAKE) --makefile=$(UT_DIR)/test_fifo.mk

#================================================================================
# Include the dependencies.
#================================================================================
-include $(DEP_FILES)