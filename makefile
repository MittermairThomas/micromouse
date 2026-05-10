# -------- Projektparameter --------
MCU     = atmega328p
CC      = avr-gcc
OBJCOPY = avr-objcopy

PORT = /dev/ttyUSB0
#BAUTRATE = 57600
BAUTRATE = 115200

CFLAGS  = -mmcu=$(MCU) -Os -std=gnu11 -Wall -Wextra -pedantic
LDFLAGS = -mmcu=$(MCU)

SRCDIR = src
BINDIR = bin
TARGET  = main

SRCS    = $(wildcard $(SRCDIR)/*.c)
OBJS    = $(SRCS:$(SRCDIR)/%.c=$(BINDIR)/%.o)

# -------- Targets --------
all: $(BINDIR)/$(TARGET).hex

$(BINDIR)/%.o: $(SRCDIR)/%.c | $(BINDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR)/$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(BINDIR)/$(TARGET).hex: $(BINDIR)/$(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

clean:
	rm -f $(BINDIR)/*.o $(BINDIR)/*.elf

flash:
	avrdude -v -patmega328p -carduino -P$(PORT) -b$(BAUTRATE) -Uflash:w:$(BINDIR)/$(TARGET).hex:i
