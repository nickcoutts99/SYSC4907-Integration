#include "LCD_4bit.h"
#include "delay.h"
#include <stdint.h>

uint8_t lcd_read_status(void)
{
  uint8_t status;

  SET_LCD_DATA_DIR_IN
  SET_LCD_RS(0)
  SET_LCD_RW(1)
  Delay(1);
  SET_LCD_E(1)
  Delay(1);
  status  = GET_LCD_DATA_IN << 4;
  SET_LCD_E(0);
  Delay(1);
  SET_LCD_E(1)
  Delay(1);
  status |= GET_LCD_DATA_IN;
  SET_LCD_E(0)
  SET_LCD_DATA_DIR_OUT
  return(status);
}

void wait_while_busy(void)
{
	for( ; lcd_read_status() & LCD_BUSY_FLAG_MASK; )
		;
}

void lcd_write_4bit(uint8_t c)
{
  SET_LCD_RW(0)	// Write data or instruction (depending on if RS was set to 1 or 0 previously, respectively)
  SET_LCD_E(1) // LCDEnable is set true
  SET_LCD_DATA_OUT(c&0x0F)
  Delay(1);
  SET_LCD_E(0)
  Delay(1);
}

void lcd_write_cmd(uint8_t c)
{
  wait_while_busy();

  SET_LCD_RS(0)
  lcd_write_4bit(c>>4);
  lcd_write_4bit(c);
}

static void lcd_write_data(uint8_t c)
{
  wait_while_busy();

  SET_LCD_RS(1)
  lcd_write_4bit(c>>4);	// Send first four bits of 8 bit int (and with 0x0F later in lcd_write_4bit function)
  lcd_write_4bit(c); // Send second four bits of 8 bit int
}

void lcd_putchar(char c)
{ 
  lcd_write_data(c);
}

void lcd_init_port(void) {
	/* Enable clocks for peripherals        */
  ENABLE_LCD_PORT_CLOCKS                          

	/* Set Pin Mux to GPIO */
	PIN_DATA_PORT->PCR[PIN_DATA_SHIFT] = PORT_PCR_MUX(1);		// Configure data ports PORT C pins 3-6
	PIN_DATA_PORT->PCR[PIN_DATA_SHIFT+1] = PORT_PCR_MUX(1);
	PIN_DATA_PORT->PCR[PIN_DATA_SHIFT+2] = PORT_PCR_MUX(1);
	PIN_DATA_PORT->PCR[PIN_DATA_SHIFT+3] = PORT_PCR_MUX(1);
	PIN_E_PORT->PCR[PIN_E_SHIFT] = PORT_PCR_MUX(1);			// PORT C bit 7 corresponds to LCDEnable (lab manual)
	PIN_RW_PORT->PCR[PIN_RW_SHIFT] = PORT_PCR_MUX(1); // PORT C bit 8
	PIN_RS_PORT->PCR[PIN_RS_SHIFT] = PORT_PCR_MUX(1); // PORT C bit 9
}

void Init_LCD(void)
{ 
	/* initialize port(s) for LCD */
	lcd_init_port();
	
  /* Set all pins for LCD as outputs */
  SET_LCD_ALL_DIR_OUT
  Delay(100);
  SET_LCD_RS(0)
  //lcd_write_4bit(0x3);              
  Delay(100);
  //lcd_write_4bit(0x3);
  //Delay(10);
  //lcd_write_4bit(0x3); //set to 8 bit bus mode? 3 times?
  lcd_write_4bit(0x2); //set to 4 bit bus mode (see LCD manual pg.11 6.Function Set) -> DB5 = 1 (see lab manual)
  lcd_write_cmd(0x28); //0010 1000 calling Function set 4 bit bus mode, 2 lines of display, 5x8 dots per char
  lcd_write_cmd(0x0C); //0000 1100      calling 'Display ON/OFF Control' with display on, cursor and blinking cursor off
  lcd_write_cmd(0x06); //0000 0110      calling 'Entry Mode Set', cursor moves right and DDRAM+1, dont shift display
  lcd_write_cmd(0x80); //1000 0000 calling 'Set DDRAM Address' to return DDRAM address to 0
}

void Set_Cursor(uint8_t column, uint8_t row)
{
  uint8_t address;

  address =(row * 0x40) + column;	// Moving to a specific position: Row0 = 00 -> 0F, Row1 = 40 -> 4F (Datasheet for lcd) 
	address |= 0x80;	// Adding 'Set DDRAM Address' function to the above data (the next unused bit is 0x80 or 128)
  lcd_write_cmd(address); //Moving address to the position for the lcd based on the above calculations
}

void Clear_LCD(void)
{
  lcd_write_cmd(0x01); // Clear display command
  Set_Cursor(0, 0); // Return cursor of lcd to (0, 0) i.e. top left
}

void Print_LCD(char *string)
{
  while(*string)  {
    lcd_putchar(*string++);	// Continue printing string until reaching end of string
  }
}
