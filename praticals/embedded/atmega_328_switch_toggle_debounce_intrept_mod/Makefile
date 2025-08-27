# -------- Configuration Variables --------
MCU        ?= atmega328p
F_CPU      ?= 16000000UL
PROGRAMMER ?= arduino
PORT       ?= /dev/ttyUSB0
BAUD       ?= 115200

# -------- Tools --------
CC         := avr-gcc
OBJCOPY    := avr-objcopy
AVRDUDE    := avrdude

CFLAGS     := -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -std=c11 -Iinclude
LDFLAGS    := -mmcu=$(MCU)

# -------- Required target check --------
ifndef target
$(error ❌ Please provide the target name using 'make target=<name>' (e.g. make target=led_on))
endif

TARGET      := $(target)
SRCFILE     := src/$(TARGET).c
OBJFILE     := build/$(TARGET).o
ELF         := build/$(TARGET).elf
HEX         := build/$(TARGET).hex

.PHONY: all clean flash

all: $(HEX)

# Step 1: Compile .c to .o
$(OBJFILE): $(SRCFILE) | build
	@echo "🔨 Compiling: $< → $@"
	@$(CC) $(CFLAGS) -c $< -o $@

# Step 2: Link .o to .elf
$(ELF): $(OBJFILE)
	@echo "📦 Linking: $^ → $@"
	@$(CC) $(LDFLAGS) -o $@ $^

# Step 3: Convert .elf to .hex
$(HEX): $(ELF)
	@echo "📦 Generating HEX: $< → $@"
	@$(OBJCOPY) -O ihex -R .eeprom $< $@

# Step 4: Flash the HEX file
flash: $(HEX)
	@echo "🚀 Flashing: $< to MCU $(MCU) on port $(PORT)"
	@$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$<

# Create build directory if needed
build:
	@mkdir -p build

# Clean artifacts
clean:
	@echo "🧹 Cleaning build files..."
	@rm -rf build
