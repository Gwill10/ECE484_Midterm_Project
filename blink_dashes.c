#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL  // Clock Speed
#define SCL_CLOCK  100000L  // SCL clock frequency
#define LCD_ADDRESS 0x27  // LCD I2C address

void i2c_init(void) {
    TWSR = 0;
    TWBR = ((F_CPU/SCL_CLOCK)-16)/2;
}

void i2c_start(void) {
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}

void i2c_stop(void) {
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void i2c_write(uint8_t data) {
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}

void lcd_send(uint8_t data, uint8_t mode) {
    i2c_start();
    i2c_write(LCD_ADDRESS << 1 | 0);  // Write command
    i2c_write((data & 0xF0) | mode | 0x08);  // send high nibble
    i2c_write(((data & 0xF0) | mode | 0x08) | 0x04);  // enable pulse
    i2c_write((data & 0xF0) | mode | 0x08);
    i2c_write((data << 4) | mode | 0x08);  // send low nibble
    i2c_write(((data << 4) | mode | 0x08) | 0x04);  // enable pulse
    i2c_write((data << 4) | mode | 0x08);
    i2c_stop();
}

void lcd_write_char(char c) {
    lcd_send(c, 1);
}

void lcd_command(uint8_t cmd) {
    lcd_send(cmd, 0);
    _delay_ms(2);
}

void lcd_init(void) {
    _delay_ms(50);
    lcd_command(0x03);
    lcd_command(0x03);
    lcd_command(0x03);
    lcd_command(0x02);  // 4-bit mode
    lcd_command(0x28);  // 2 line, 5x8 matrix
    lcd_command(0x0C);  // display on, cursor off
    lcd_command(0x06);  // increment cursor
    lcd_command(0x01);  // clear display
    _delay_ms(2);
}

void lcd_print(const char *str) {
    while (*str) {
        lcd_write_char(*str++);
    }
}
int main(void) {
    i2c_init();
    lcd_init();

    char dashes[] = "----------------";
    char spaces[] = "                ";

    while (1) {
        lcd_command(0x80);  // Move cursor to the beginning of the first line
        lcd_print(dashes);
        _delay_ms(1000);  // Wait for 1 second

        lcd_command(0x80);  // Move cursor to the beginning of the first line
        lcd_print(spaces);
        _delay_ms(1000);  // Wait for 1 second
    }

    return 0;
}
