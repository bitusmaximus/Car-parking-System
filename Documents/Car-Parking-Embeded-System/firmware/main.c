#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

/* LCD */
#define RS PC0
#define EN PC1

void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_print(char *str);
void lcd_init(void);

/* ===== SERVO (OC1A = PD5) ===== */
void servo_init(void) {
	DDRD |= (1 << PD5);

	TCCR1A = (1 << COM1A1) | (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
	ICR1 = 39999;               // 20ms
}

void servo_open(void)  { OCR1A = 1000; } // 1ms
void servo_close(void) { OCR1A = 3000; } // 2ms

/* ===== MAIN ===== */
int main(void) {

	uint8_t freeSlots = 5;

	uint8_t entryPrev = 1;
	uint8_t exitPrev  = 1;

	/* Buttons with pull-ups */
	DDRD &= ~((1 << PD0) | (1 << PD1));
	PORTD |= (1 << PD0) | (1 << PD1);

	lcd_init();
	servo_init();
	servo_close();

	lcd_cmd(0x01);
	lcd_print("Car Parking");
	lcd_cmd(0xC0);
	lcd_print("System");
	_delay_ms(1500);
	lcd_cmd(0x01);

	while (1) {

		uint8_t entryNow = (PIND & (1 << PD0));
		uint8_t exitNow  = (PIND & (1 << PD1));

		/* ===== ENTRY (press detected on HIGH -> LOW) ===== */
		if (entryPrev && !entryNow) {
			lcd_cmd(0x01);

			if (freeSlots > 0) {
				freeSlots--;
				lcd_print("Gate Opening");
				servo_open();
				_delay_ms(1000);
				servo_close();
				} else {
				lcd_print("Parking Full");
				lcd_cmd(0xC0);
				lcd_print("No Entry");
				_delay_ms(1000);
			}
		}

		/* ===== EXIT ===== */
		if (exitPrev && !exitNow) {
			lcd_cmd(0x01);

			if (freeSlots < 5) {
				freeSlots++;
				lcd_print("Exit Gate");
				servo_open();
				_delay_ms(1000);
				servo_close();
				} else {
				lcd_print("No Car Inside");
				lcd_cmd(0xC0);
				lcd_print("Exit Invalid");
				_delay_ms(1000);
			}
		}

		entryPrev = entryNow;
		exitPrev  = exitNow;

		/* ===== STATUS DISPLAY ===== */
		lcd_cmd(0x80);
		lcd_print("Total: 5    ");
		lcd_cmd(0xC0);
		lcd_print("Free: ");
		lcd_data(freeSlots + '0');
		lcd_print("     ");

		_delay_ms(150);
	}
}

/* ===== LCD FUNCTIONS ===== */
void lcd_cmd(unsigned char cmd) {
	PORTC = (PORTC & 0x0F) | (cmd & 0xF0);
	PORTC &= ~(1 << RS);
	PORTC |= (1 << EN);
	_delay_us(1);
	PORTC &= ~(1 << EN);

	PORTC = (PORTC & 0x0F) | (cmd << 4);
	PORTC |= (1 << EN);
	_delay_us(1);
	PORTC &= ~(1 << EN);
	_delay_ms(2);
}

void lcd_data(unsigned char data) {
	PORTC = (PORTC & 0x0F) | (data & 0xF0);
	PORTC |= (1 << RS);
	PORTC |= (1 << EN);
	_delay_us(1);
	PORTC &= ~(1 << EN);

	PORTC = (PORTC & 0x0F) | (data << 4);
	PORTC |= (1 << EN);
	_delay_us(1);
	PORTC &= ~(1 << EN);
	_delay_ms(2);
}

void lcd_print(char *str) {
	while (*str) lcd_data(*str++);
}

void lcd_init(void) {
	DDRC = 0xFF;
	_delay_ms(20);
	lcd_cmd(0x02);
	lcd_cmd(0x28);
	lcd_cmd(0x0C);
	lcd_cmd(0x06);
	lcd_cmd(0x01);
}
