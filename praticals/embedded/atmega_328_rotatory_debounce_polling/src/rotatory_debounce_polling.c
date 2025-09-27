#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PD6
#define ENC_A_PIN PD2
#define ENC_B_PIN PD3

void gpio_init(void) {
    DDRD |= (1 << LED_PIN);                 // LED output
    DDRD &= ~((1 << ENC_A_PIN) | (1 << ENC_B_PIN)); // Encoder inputs
    PORTD |= (1 << ENC_A_PIN) | (1 << ENC_B_PIN);   // Enable pull-ups
}

// Read combined A+B as 2-bit number
uint8_t read_encoder() {
    return ((PIND & (1 << ENC_A_PIN)) ? 1 : 0) |
           ((PIND & (1 << ENC_B_PIN)) ? 2 : 0);
}

int main(void) {
    gpio_init();

    uint8_t last_state = read_encoder();
    int8_t step_count = 0;

    while (1) {
        uint8_t curr_state = read_encoder();

        if (curr_state != last_state) {
            // Clockwise sequence
            if ((last_state == 0 && curr_state == 1) ||
                (last_state == 1 && curr_state == 3) ||
                (last_state == 3 && curr_state == 2) ||
                (last_state == 2 && curr_state == 0)) {
                step_count++; // Clockwise
            } 
            // Counter-clockwise sequence
            else if ((last_state == 0 && curr_state == 2) ||
                     (last_state == 2 && curr_state == 3) ||
                     (last_state == 3 && curr_state == 1) ||
                     (last_state == 1 && curr_state == 0)) {
                step_count--; // Counter-clockwise
            }

            // LED control
            if (step_count >= 1) {          // 1 CW step → ON
                PORTD |= (1 << LED_PIN);
                step_count = 0;
            } else if (step_count <= -1) {  // 1 CCW step → OFF
                PORTD &= ~(1 << LED_PIN);
                step_count = 0;
            }

            last_state = curr_state;
        }

        _delay_ms(2); // debounce
    }
}
