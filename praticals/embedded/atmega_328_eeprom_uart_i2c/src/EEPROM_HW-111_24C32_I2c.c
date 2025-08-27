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
static void uart_print_num(uint8_t v){
    char buf[4]; // enough for 0..255
    uint8_t i=0;
    if(v>=100) buf[i++]='0'+v/100, v%=100;
    if(i || v>=10) buf[i++]='0'+v/10, v%=10;
    buf[i++]='0'+v; buf[i]=0;
    uart_print(buf);
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

    uart_print("EEPROM Bare-metal (0x50)\r\nWriting 0..10\r\n");

    for(uint8_t i=0;i<=10;i++) eeprom_write(i,i);

    uart_print("Read back:\r\n");
    for(uint8_t i=0;i<=10;i++){
        uint8_t v = eeprom_read(i);
        uart_print("Addr "); uart_print_num(i);
        uart_print(" = ");   uart_print_num(v);
        uart_print("\r\n");
    }
    for(;;);
}
