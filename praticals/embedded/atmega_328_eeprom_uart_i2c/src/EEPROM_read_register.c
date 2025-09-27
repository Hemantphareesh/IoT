#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// ---------- UART 115200 U2X ----------
static void uart_init(void){
    UBRR0H = 0;
    UBRR0L = 16;                // 115200 with U2X
    UCSR0A = (1<<U2X0);
    UCSR0B = (1<<TXEN0);
    UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
}
static void uart_tx(uint8_t c){ while(!(UCSR0A & (1<<UDRE0))); UDR0 = c; }
static void uart_print(const char *s){ while(*s) uart_tx(*s++); }

// print a byte in hex (2 characters)
static void uart_print_hex8(uint8_t v){
    const char hex[] = "0123456789ABCDEF";
    uart_tx(hex[v >> 4]);
    uart_tx(hex[v & 0x0F]);
}
// print 16-bit address in hex (4 characters)
static void uart_print_hex16(uint16_t v){
    uart_print("0x");
    uart_print_hex8(v >> 8);
    uart_print_hex8(v & 0xFF);
}
// print single byte as hex
static void uart_print_hex_byte(uint8_t v){
    uart_print("0x");
    uart_print_hex8(v);
}

// ---------- TWI @ ~100k ----------
#define F_SCL 100000UL
#define TWBR_VAL (((F_CPU/F_SCL)-16)/2)
#define EEPROM_ADDR 0x50

static void i2c_init(void){ TWSR=0; TWBR=(uint8_t)TWBR_VAL; }
static void i2c_start(void){ TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN); while(!(TWCR&(1<<TWINT))); }
static void i2c_stop(void){ TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN); _delay_us(10); }
static void i2c_write(uint8_t d){ TWDR=d; TWCR=(1<<TWINT)|(1<<TWEN); while(!(TWCR&(1<<TWINT))); }
static uint8_t i2c_read_nack(void){ TWCR=(1<<TWINT)|(1<<TWEN); while(!(TWCR&(1<<TWINT))); return TWDR; }

// ---------- 24C32 byte write/read ----------
static void eeprom_write(uint16_t addr, uint8_t data){
    i2c_start();
    i2c_write((EEPROM_ADDR<<1)|0);         // W
    i2c_write((addr>>8)&0xFF);
    i2c_write(addr&0xFF);
    i2c_write(data);
    i2c_stop();
    _delay_ms(5); // write cycle
}
static uint8_t eeprom_read(uint16_t addr){
    i2c_start();
    i2c_write((EEPROM_ADDR<<1)|0);         // W
    i2c_write((addr>>8)&0xFF);
    i2c_write(addr&0xFF);
    i2c_start();
    i2c_write((EEPROM_ADDR<<1)|1);         // R
    uint8_t d = i2c_read_nack();
    i2c_stop();
    return d;
}

int main(void){
    uart_init();
    i2c_init();

    uart_print("EEPROM Test (AT24C32, 0x50)\r\n");

    // Step 1: Write 0x55 to all 4096 bytes
    for(uint16_t addr=0; addr<4096; addr++){
        eeprom_write(addr, 0x55);
    }
    uart_print("Write complete.\r\n");

    // Step 2: Read back and print
    uart_print("Reading EEPROM contents:\r\n");

    // for(uint16_t i=0; i<10; i++) {
    //     eeprom_write(i, 0xAA);
    // }
    for(uint16_t addr=0; addr<4096; addr++){
        uint8_t val = eeprom_read(addr);
        uart_print_hex16(addr);  // print address
        uart_print(" : ");
        uart_print_hex_byte(val); // print data
        uart_print("\r\n");
        _delay_ms(1); // Slow down output for readability
    }

    while(1);
}
