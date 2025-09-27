#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>

// === ADC Setup ===
void adc_init() {
    ADMUX = (1 << REFS0);                       // AVcc as reference
    ADCSRA = (1 << ADEN) |                      // Enable ADC
             (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler 128
}

// Read ADC channel (0-7)
uint16_t adc_read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // Select ADC channel
    ADCSRA |= (1 << ADSC);                      // Start conversion
    while (ADCSRA & (1 << ADSC));               // Wait until done
    return ADC;
}

// === PWM Setup on PD6 (OC0A) ===
void pwm_init() {
    DDRD |= (1 << PD6);                         // Set PD6 as output
    TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00); // Fast PWM, non-inverting
    TCCR0B |= (1 << CS01);                      // Prescaler = 8
}

int main(void) {
    adc_init();
    pwm_init();

    while (1) {
        uint16_t adc_val = adc_read(0);        // Read potentiometer on A0
        uint8_t pwm_value = adc_val / 4;       // Scale 10-bit ADC (0-1023) to 8-bit PWM (0-255)
        OCR0A = pwm_value;                     // Set PWM duty cycle
        _delay_ms(5);                          // Small delay for smooth response
    }
}
