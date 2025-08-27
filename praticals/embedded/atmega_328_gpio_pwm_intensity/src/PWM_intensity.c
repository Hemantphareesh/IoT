#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// Initialize PWM on PD6 (OC0A)
void pwm_init() {
    DDRD |= (1 << PD6);  // Set PD6 as output
    TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00); // Fast PWM, non-inverting
    TCCR0B |= (1 << CS01); // Prescaler = 8
}

int main(void) {
    pwm_init();
    
    uint8_t brightness = 0;
    int8_t direction = 1; // 1 = increasing, -1 = decreasing

    while (1) {
        OCR0A = brightness;    // Set PWM duty cycle
        _delay_ms(10);         // Adjust speed of fading

        brightness += direction;
        if (brightness == 255) direction = -1;   // Start decreasing
        if (brightness == 0) direction = 1;      // Start increasing
    }
}
