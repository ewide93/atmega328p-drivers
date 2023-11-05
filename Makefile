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

PORT := COM5
PROGRAMMER := arduino
BAUD_RATE := 115200

MCU := atmega328p
F_CPU := 16000000UL

CFLAGS = -Wall -Werror -Wextra -Wunused-variable -std=c99 -I$(INC_DIR)
CFLAGS += -mmcu=$(MCU) -DF_CPU=$(F_CPU)
DFLAGS = -MMD -MP
LDFLAGS += -mmcu=$(MCU)
OPT := -O2

#================================================================================
# Rule to invoke all rules necessary to produce the .hex-file.
#================================================================================
.PHONY: all
all: $(BUILD_DIR)/$(TARGET).hex

#================================================================================
# Convert .elf-file to .hex-file.
#================================================================================
$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

#================================================================================
# Rule to link object files into .elf-file.
#================================================================================
$(BUILD_DIR)/$(TARGET).elf: $(OBJ_FILES)
	$(CC) $(LDFLAGS) $^ -o $@

#================================================================================
# Rule to compile source files into object files.
#================================================================================
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(DFLAGS) $(OPT) -c $< -o $@

#================================================================================
# Rule to flash the .hex-file to the MCU.
#================================================================================
flash: $(BUILD_DIR)/$(TARGET).hex
	$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD_RATE) -U flash:w:$<

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
	@rm -rf $(TARGET)

#================================================================================
# Rule for running Python script.
#================================================================================
.PHONY: py
py:
	@python $(SCRIPT_DIR)/main.py

#================================================================================
# Include the dependencies.
#================================================================================
-include $(DEP_FILES)