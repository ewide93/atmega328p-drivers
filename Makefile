# AVR-GCC, AVRDUDE, and project configuration
MCU = atmega328p
F_CPU = 16000000UL
TARGET = atmega328p-driver
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# Programmer settings
PORT = COM6  # Change this to the correct COM port on your system
PROGRAMMER = arduino
BAUD_RATE = 115200

# Compiler and linker flags
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Wall -Werror -Os
LDFLAGS = -mmcu=$(MCU)

# Source and build directories
SRCDIR = src
BUILDDIR = build

# List of source files
SRC = $(wildcard $(SRCDIR)/*.c)

# Object files (convert source paths to build paths)
OBJ = $(SRC:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

# Default target: Build the HEX file
all: $(BUILDDIR)/$(TARGET).hex

# Compile source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create ELF file
$(BUILDDIR)/$(TARGET).elf: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

# Convert ELF file to HEX file
$(BUILDDIR)/$(TARGET).hex: $(BUILDDIR)/$(TARGET).elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

# Flash the HEX file to the AVR
flash: $(BUILDDIR)/$(TARGET).hex
	$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD_RATE) -U flash:w:$<

# Clean up build files
clean:
	@echo "Removing contents of build folder"
	@rm -rf $(BUILDDIR)/*

# Phony targets for non-file targets
.PHONY: all flash clean
