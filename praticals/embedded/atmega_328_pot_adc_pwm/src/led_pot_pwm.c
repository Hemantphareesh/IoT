#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void adc_init() {
    ADMUX = (1 << REFS0); // AVcc reference, ADC0 selected
    ADCSRA = (1 << ADEN)  // Enable ADC
           | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler = 128
}

uint16_t adc_read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // select ADC channel
    ADCSRA |= (1 << ADSC); // start conversion
    while (ADCSRA & (1 << ADSC)); // wait for conversion to finish
    return ADC;
}

void pwm_init() {
    // Set Fast PWM mode, non-inverting, prescaler = 64
    TCCR0A = (1 << COM0A1) | (1 << WGM01) | (1 << WGM00); // Fast PWM, clear OC0A on compare
    TCCR0B = (1 << CS01) | (1 << CS00); // prescaler = 64
    DDRD |= (1 << PB5); // Set OC0A (PB5) as output
}

int main(void) {
    adc_init();
    pwm_init();

    while (1) {
        uint16_t adc_val = adc_read(0); // Read from A0
        uint8_t pwm_val = adc_val / 4;  // Convert 10-bit ADC (0–1023) to 8-bit PWM (0–255)
        OCR0A = pwm_val;                // Set duty cycle
        _delay_ms(10);                  // Short delay
    }
}

