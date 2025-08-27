#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// === UART Initialization ===
void uart_init(unsigned int baud) {
    unsigned int ubrr = F_CPU/16/baud - 1;  
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    UCSR0B = (1 << TXEN0); // Enable transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data, 1 stop bit
}

// === UART Send One Character ===
void uart_transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0))); // Wait for empty buffer
    UDR0 = data;
}

// === UART Send String ===
void uart_send_string(const char *str) {
    while (*str) {
        uart_transmit(*str++);
    }
}

int main(void) {
    uart_init(115200);// Init UART with 9600 baud

    while (1) {
        uart_send_string("Hello, World!\r\n");
        _delay_ms(1000); // Delay 1 second
    }
}
