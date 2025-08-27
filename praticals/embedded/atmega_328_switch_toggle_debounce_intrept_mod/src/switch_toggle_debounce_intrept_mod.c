#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define LED_PIN PD6    // LED output
#define SW_PIN PD2     // Switch input (INT0)

volatile uint8_t led_state = 0;       // Stores LED state
volatile uint8_t toggle_request = 0;  // Flag set by ISR

// ISR: triggered when switch is pressed (falling edge)
ISR(INT0_vect) {
    toggle_request = 1; // request toggle
}

int main(void) {
    // Configure pins
    DDRD |= (1 << LED_PIN);   // LED as output
    DDRD &= ~(1 << SW_PIN);   // Switch as input
    PORTD |= (1 << SW_PIN);   // Enable internal pull-up

    // Configure INT0 for falling edge
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);
    EIMSK |= (1 << INT0);     // Enable INT0

    sei(); // Enable global interrupts

    while (1) {
        if (toggle_request) {
            _delay_ms(50);                 // debounce
            if (!(PIND & (1 << SW_PIN))) { // still pressed
                led_state ^= 1;            // toggle LED state
                if (led_state) PORTD |= (1 << LED_PIN);
                else PORTD &= ~(1 << LED_PIN);
            }
            toggle_request = 0;            // clear flag
        }
    }
}
