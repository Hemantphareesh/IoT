// One switch → LED changes state (ON ↔ OFF) each time switch is pressed.
// Polled mode, so no interrupts.
// Debounce handled in software.

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PD6   // LED on PD6 (Arduino pin 6)
#define SW_PIN PD2    // Switch on PD2

#define DEBOUNCE_DELAY 50 // ms

int main(void) {
    // Configure pins
    DDRD |= (1 << LED_PIN);   // LED as output
    DDRD &= ~(1 << SW_PIN);   // Switch as input
    PORTD |= (1 << SW_PIN);   // Enable internal pull-up

    uint8_t last_sw_state = 1; // Pull-up → default HIGH
    uint8_t led_state = 0;     // LED initially OFF
    uint8_t sw_state;

    while (1) {
        sw_state = (PIND & (1 << SW_PIN)) ? 1 : 0; // Read switch

        // Detect falling edge (button pressed)
        if (last_sw_state == 1 && sw_state == 0) {
            _delay_ms(DEBOUNCE_DELAY); // debounce
            // Confirm still pressed
            if ((PIND & (1 << SW_PIN)) == 0) {
                led_state ^= 1;              // Toggle LED
                if (led_state) PORTD |= (1 << LED_PIN);
                else PORTD &= ~(1 << LED_PIN);
            }
        }

        last_sw_state = sw_state; // Update last switch state
    }
}
