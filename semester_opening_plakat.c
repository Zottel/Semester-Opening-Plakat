#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

int channels[] = {0x10,
                  0x30,
                  0xf0,
                  0x30,
                  0x90,
                  0x30,
                  0x50,
                  0x30,
                  0xc0,
                  0xd0,
                  0x30,
                  0x10};
int main() {
	PORTB = 0;
	DDRB = (1 << PB5)|(1 << PB6)|(1 << PB7);
	
	while(1) {
		asm volatile ("nop");
		for(int i = 0; i < 12; i++) {
			channels[i] = (channels[i] + 1) % 512;
		}
		for(int i = 0; i < 12; i++) {
			char derp = abs(channels[i] - 256);
		}
	}
}
