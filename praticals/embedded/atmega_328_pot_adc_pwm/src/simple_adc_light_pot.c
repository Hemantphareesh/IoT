#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PD6     
#define ADC_CHANNEL 0     // A0

int main(void) {
    // Configure LED as output
    DDRD |= (1 << LED_PIN);

    // === ADC Setup ===
    ADMUX = (1 << REFS0);                    // AVcc as reference, input channel ADC0
    ADCSRA = (1 << ADEN) |                   // Enable ADC
             (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler 128

    while (1) {
        // Select ADC channel
        ADMUX = (ADMUX & 0xF0) | (ADC_CHANNEL & 0x0F);

        // Start ADC conversion
        ADCSRA |= (1 << ADSC);
        while (ADCSRA & (1 << ADSC));        // Wait for conversion to complete

        uint16_t adc_value = ADC;            // 10-bit result (0–1023)

        // Check if ADC is above 50% (1023 * 0.5 ≈ 512)
        if (adc_value > 512) {
            PORTD |= (1 << LED_PIN);         // Turn ON LED
        } else {
            PORTD &= ~(1 << LED_PIN);        // Turn OFF LED
        }

        _delay_ms(50); // Small delay for stability
    }
}
