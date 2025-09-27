#define F_CPU 16000000UL  // 16 MHz Arduino clock
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // Set pin 6 (PD6) as output ()
    DDRD |= (1 << PD6);

    while (1) {
        // Turn LED ON
        PORTD |= (1 << PD6);
        _delay_ms(5000);  // Wait 5 seconds

        // Turn LED OFF
        PORTD &= ~(1 << PD6);
        _delay_ms(5000);  // Wait 5 seconds
    }
}

