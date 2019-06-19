PORT ?= /dev/ttyUSB0

all: lab3.lss lab3.hex

lab3.elf: *.c
	avr-g++ -mmcu=atmega324a -DF_CPU=16000000 -Wall -Wl,-u,vfprintf -lprintf_flt -lm -O3 -o $@ $^

lab3.hex: lab3.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@
	avr-size $@

lab3.lss: lab3.elf
	avr-objdump -t -h -S -C $^ > $@

upload: lab3.hex
	avrdude -c arduino -P $(PORT) -b 57600 -p atmega324p -U flash:w:$<:a

clean:
	rm -rf lab3.elf lab3.hex lab3.lss

.PHONY: all clean upload

