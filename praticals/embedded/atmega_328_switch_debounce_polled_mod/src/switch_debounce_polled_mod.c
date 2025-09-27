// switch debounce, polled mode code.(led on only when switch is on) 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PD6       // LED connected to PD6 (Arduino pin 6)
#define SW_PIN PD2        // Switch connected to PD2

#define DEBOUNCE_DELAY 50 // milliseconds

int main(void) {
    // Configure pins
    DDRD |= (1 << LED_PIN);   // LED as output
    DDRD &= ~(1 << SW_PIN);   // Switch as input
    PORTD |= (1 << SW_PIN);   // Enable internal pull-up resistor

    uint8_t last_sw_state = 1; // Pull-up, so default HIGH
    uint8_t sw_state;

    while (1) {
        sw_state = (PIND & (1 << SW_PIN)) ? 1 : 0; // Read switch

        // Check if switch state changed
        if (sw_state != last_sw_state) {
            _delay_ms(DEBOUNCE_DELAY); // debounce delay
            sw_state = (PIND & (1 << SW_PIN)) ? 1 : 0;

            if (sw_state == 0) { // Switch pressed (active LOW)
                PORTD |= (1 << LED_PIN);  // Turn ON LED
            } else {
                PORTD &= ~(1 << LED_PIN); // Turn OFF LED
            }

            last_sw_state = sw_state; // Update last state
        }
    }
}
