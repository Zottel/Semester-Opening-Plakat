#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

int channels[] = {0x000,
                  0x060,
                  0x0c0,
                  0x100,
                  0x160,
                  0x1c0,
                  0x200,
                  0x260,
                  0x2c0,
                  0x300,
                  0x360,
                  0x3c0};

void setupChannels() {
	DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
	DDRA |= (1 << PA0) | (1 << PA1);
	DDRD |= (1 << PD0) | (1 << PD1) | (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6);
}

//__attribute__((always_inline)) static void setChannel(int channel, int value) {
static void setChannel(int channel, int value) {
	switch(channel) {
		case 0:
			PORTD &= ~(1 << PD0);
			PORTD |= (value << PD0);
			break;
		case 1:
			PORTD &= ~(1 << PD1);
			PORTD |= (value << PD1);
			break;
		case 2:
			PORTA &= ~(1 << PA1);
			PORTA |= (value << PA1);
			break;
		case 3:
			PORTA &= ~(1 << PA0);
			PORTA |= (value << PA0);
			break;
		case 4:
			PORTD &= ~(1 << PD2);
			PORTD |= (value << PD2);
			break;
		case 5:
			PORTD &= ~(1 << PD3);
			PORTD |= (value << PD3);
			break;
		case 6:
			PORTD &= ~(1 << PD4);
			PORTD |= (value << PD4);
			break;
		case 7:
			PORTD &= ~(1 << PD5);
			PORTD |= (value << PD5);
			break;
		case 8:
			PORTD &= ~(1 << PD6);
			PORTD |= (value << PD6);
			break;
		case 9:
			PORTB &= ~(1 << PB0);
			PORTB |= (value << PB0);
			break;
		case 10:
			PORTB &= ~(1 << PB1);
			PORTB |= (value << PB1);
			break;
		case 11:
			PORTB &= ~(1 << PB2);
			PORTB |= (value << PB2);
			break;
	}
}

int main() {
	PORTA = 0; PORTB = 0; PORTD = 0;
	DDRA = 0; DDRB = 0; DDRD = 0;
	setupChannels();
	
	while(1) {
		asm volatile ("nop");
		for(int i = 0; i < 12; i++) {
			channels[i] = (channels[i] + 1) % 1024;
		}
		for(int n = 0; n < 12; n++) {
			setChannel(n, 0);
		}
		for(int i = 0; i < 256; i++)
			for(int n = 0; n < 12; n++) {
				if(i < abs(channels[n] - 256)) {
					asm volatile ("nop");
				} else {
					setChannel(n, 1);
				}
			}
	}
}
