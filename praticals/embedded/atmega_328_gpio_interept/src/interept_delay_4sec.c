#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_PIN PD6 // Connect LED to PD6

volatile uint8_t toggle_flag = 0;

ISR(TIMER1_COMPA_vect) {
    toggle_flag = 1; // Signal main loop to toggle LED
}

void timer1_init(void) {
    // CTC mode (Clear Timer on Compare Match)
    TCCR1B |= (1 << WGM12);

    // Compare value for 4 seconds
    OCR1A = 62500 - 1;

    // Enable compare interrupt
    TIMSK1 |= (1 << OCIE1A);

    // Start timer with prescaler 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);
}

int main(void) {
    // Set LED pin as output
    DDRD |= (1 << LED_PIN);

    timer1_init();
    sei(); // Enable global interrupts

    while (1) {
        if (toggle_flag) {
            PORTD ^= (1 << LED_PIN); // Toggle LED
            toggle_flag = 0;
        }
    }
}

