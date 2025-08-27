#define F_CPU 16000000UL  // 16 MHz CPU frequency

#include <avr/io.h>

int main(void) {
    // Set pin 13 (PB5) as output (PB7 for Simulator)
    DDRB |= (1 << PB7);

    // Set pin 13 HIGH (LED ON)
    PORTB |= (1 << PB7);

    // Infinite loop (do nothing, keep LED on)
    while (1) {
        // You can add power saving sleep here if needed
    }
}