#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN     PB5
#define ENC_A_PIN   PD2
#define ENC_B_PIN   PD3

void gpio_init(void) {
    // LED output
    DDRB |= (1 << LED_PIN);

    // Encoder A/B inputs
    DDRD &= ~((1 << ENC_A_PIN) | (1 << ENC_B_PIN));
    PORTD |= (1 << ENC_A_PIN) | (1 << ENC_B_PIN); // enable pull-ups
}

uint8_t read_encoder_A() {
    return (PIND & (1 << ENC_A_PIN)) ? 1 : 0;
}

uint8_t read_encoder_B() {
    return (PIND & (1 << ENC_B_PIN)) ? 1 : 0;
}

int main(void) {
    gpio_init();

    uint8_t last_A = read_encoder_A();
    int step_count = 0;

    while (1) {
        uint8_t A = read_encoder_A();
        uint8_t B = read_encoder_B();

        // detect transition A: HIGH -> LOW (falling edge)
        if (last_A == 1 && A == 0) {
            if (B == 0) {
                // Clockwise
                step_count++;
            } else {
                // Counter-clockwise
                step_count--;
            }

            // Apply actions
            if (step_count >= 3) {
                PORTB |= (1 << LED_PIN);   // LED ON
                step_count = 0;            // reset count
            } else if (step_count <= -6) {
                PORTB &= ~(1 << LED_PIN);  // LED OFF
                step_count = 0;            // reset count
            }
        }

        last_A = A;

        _delay_ms(2); // debounce (adjust as needed)
    }
}
