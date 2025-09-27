#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // === LED Setup ===
    DDRD |= (1 << PD6);    // PD6 (Arduino UNO Pin 6) as output

    // === Button Setup ===
    DDRD &= ~(1 << PD2);   // PD2 (Arduino UNO Pin 2) as input
    PORTD |= (1 << PD2);   // Enable pull-up resistor on PD2

    while (1) {
        if (!(PIND & (1 << PD2))) {
            // Switch pressed (active LOW)
            PORTD |= (1 << PD6);   // LED ON
        } else {
            // Switch released
            PORTD &= ~(1 << PD6);  // LED OFF
        }
    }
}
