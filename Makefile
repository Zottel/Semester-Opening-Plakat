FORMAT = ihex
MCU = attiny2313
CC = avr-gcc
CFLAGS += -Wall -g -Os -mmcu=$(MCU) -std=gnu99 -pedantic-errors
#-Werror -Wno-unused
LDFLAGS +=
OBJCOPY = avr-objcopy
# 8Mhz - without clock devider
FUSES = -U lfuse:w:0xe4:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m
FUSES = -U lfuse:w:0xe4:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m


TARGET = semester_opening_plakat
OBJS = semester_opening_plakat.o


all: $(TARGET).hex


program: $(TARGET).hex
#	avrdude -p $(MCU) -c usbasp -b 19200 -U flash:w:$(TARGET).hex
	avrdude -p $(MCU) -c stk500v2 -P /dev/ttyUSB0 -U flash:w:$(TARGET).hex

fuses:
#	avrdude -p $(MCU) -c usbasp -b 19200 $(FUSES)
	avrdude -p $(MCU) -c stk500v2 -P /dev/ttyUSB0 $(FUSES)


$(TARGET).elf: $(OBJS)
	$(CC) -mmcu=$(MCU) -o $@ $<

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm $(TARGET).hex $(TARGET).elf $(OBJS)
