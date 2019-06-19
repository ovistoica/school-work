PORT ?= COM12

all: lab2.hex lab2.lss

program: upload

lab2.elf: *.c *.h
	avr-g++ -mmcu=atmega324p -DF_CPU=16000000 -O3 -Wall -o $@ $^

lab2.hex: lab2.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@
	avr-size $@

lab2.lss: lab2.elf
	avr-objdump -t -h -S -C $^ > $@

upload: lab2.hex
	avrdude -c arduino -P $(PORT) -b 57600 -p atmega324p -U flash:w:$<:a

clean:
	rm -rf lab2.elf lab2.hex lab2.lss

.PHONY: all clean program upload
