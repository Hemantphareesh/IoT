// rotatory_switch LED 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // === LED Setup ===
    DDRB |= (1 << PB5);   // PB5 (Arduino UNO Pin 13) as output

    // === Button Setup ===
    DDRD &= ~(1 << PD2);  // PD2 as input
    PORTD |= (1 << PD2);  // Enable pull-up resistor

    while (1) {
        if (!(PIND & (1 << PD2))) {
            // Button pressed (active LOW)
            PORTB |= (1 << PB5);   // LED ON
        } else {
            // Button released
            PORTB &= ~(1 << PB5);  // LED OFF
        }
    }
}
