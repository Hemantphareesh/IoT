#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define LED_PIN PB5   // Onboard LED on Arduino Uno

volatile int8_t encoder_dir = 0;     // +1 for CW, -1 for CCW
volatile uint16_t cw_count = 0;      // CW step counter
volatile uint16_t ccw_count = 0;     // CCW step counter

// Debounce delay in microseconds
#define DEBOUNCE_DELAY_US 2000

// Store last stable state
volatile uint8_t last_A = 0;
volatile uint8_t last_B = 0;

// Read encoder pins (A=PD2, B=PD3)
static inline uint8_t readA() { return (PIND & (1 << PD2)) != 0; }
static inline uint8_t readB() { return (PIND & (1 << PD3)) != 0; }

// External interrupt for A (INT0)
ISR(INT0_vect) {
    _delay_us(DEBOUNCE_DELAY_US); // debounce
    uint8_t A = readA();
    uint8_t B = readB();

    if (A != last_A) {   // A changed
        if (A == B) {
            encoder_dir = -1; // CCW
            ccw_count++;
        } else {
            encoder_dir = +1; // CW
            cw_count++;
        }
        last_A = A;
    }
}

// External interrupt for B (INT1)
ISR(INT1_vect) {
    _delay_us(DEBOUNCE_DELAY_US); // debounce
    uint8_t A = readA();
    uint8_t B = readB();

    if (B != last_B) {   // B changed
        if (A == B) {
            encoder_dir = +1; // CW
            cw_count++;
        } else {
            encoder_dir = -1; // CCW
            ccw_count++;
        }
        last_B = B;
    }
}

int main(void) {
    // Configure LED pin as output
    DDRB |= (1 << LED_PIN);
    PORTB &= ~(1 << LED_PIN); // LED OFF initially

    // Configure PD2 (INT0) and PD3 (INT1) as input with pullups
    DDRD &= ~((1 << PD2) | (1 << PD3));
    PORTD |= (1 << PD2) | (1 << PD3);

    // Save initial encoder state
    last_A = readA();
    last_B = readB();

    // Enable external interrupts on both INT0 and INT1 (any logical change)
    EICRA |= (1 << ISC00) | (1 << ISC10); // Any change on INT0, INT1
    EIMSK |= (1 << INT0) | (1 << INT1);

    sei(); // Enable global interrupts

    while (1) {
        // Check conditions
        if (cw_count >= 3) {
            PORTB |= (1 << LED_PIN);   // LED ON
            cw_count = 0;              // reset CW counter
        }
        if (ccw_count >= 6) {
            PORTB &= ~(1 << LED_PIN);  // LED OFF
            ccw_count = 0;             // reset CCW counter
        }
    }
}
