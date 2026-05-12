# -------- Projektparameter --------
OBJCOPY = avr-objcopy

PORT = /dev/ttyUSB0
#BAUTRATE = 57600
BAUTRATE = 115200

SRCS    = $(wildcard src/*.c)
OBJS    = $(SRCS:src/%.c=bin/%.o)

# -------- Targets --------
all: bin/main.hex

bin:
	mkdir -p bin

bin/%.o: src/%.c | bin
	avr-gcc -mmcu=atmega328p -Os -std=gnu11 -Wall -Wextra -pedantic -c $< -o $@

bin/main.elf: $(OBJS)
	avr-gcc -mmcu=atmega328p -Os -std=gnu11 -Wall -Wextra -pedantic $^ -o $@

bin/main.hex: bin/main.elf
	avr-objcopy -O ihex -R .eeprom $< $@

clean:
	rm -f bin/*.o bin/*.elf

flash:
	avrdude -v -patmega328p -carduino -P$(PORT) -b$(BAUTRATE) -Uflash:w:bin/main.hex:i
