#define F_CPU 16000000UL  // 16 MHz Arduino clock
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // Set pin 13 (PB5) as output (PB7 for Simulator)
    DDRB |= (1 << PB7);

    while (1) {
        // Turn LED ON
        PORTB |= (1 << PB7);
        _delay_ms(5000);  // Wait 5 seconds

        // Turn LED OFF
        PORTB &= ~(1 << PB7);
        _delay_ms(5000);  // Wait 5 seconds
    }
}

