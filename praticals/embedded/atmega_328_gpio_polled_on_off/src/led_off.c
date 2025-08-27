#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRB |= (1 << PB7);        // Set pin 13 (PB5) as output, PB7 for Simulator
    PORTB &= ~(1 << PB7);      // Turn LED off

    while (1) {
        // Do nothing
    }
}