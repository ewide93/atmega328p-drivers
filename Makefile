SHELL = /bin/sh
CC = avr-gcc
SOURCES = main.c
AVRLIB = C:/avr8-gnu-toolchain-3.7.0.1796-win32.any.x86_64/avr8-gnu-toolchain-win32_x86_64/avr/include/avr

all :
	$(CC) -mmcu=atmega328p -B $(AVRLIB) $(SOURCES) -O2
	avr-objcopy -O ihex -j .text -j .data a.out a.hex
flash :
	avrdude -C C:/AVRDUDE/avrdude.conf -v -p atmega328p -c arduino -PCOM5 \
	-b 115200 -D -U flash:w:a.hex:i
clean :
	rm a.out a.hex