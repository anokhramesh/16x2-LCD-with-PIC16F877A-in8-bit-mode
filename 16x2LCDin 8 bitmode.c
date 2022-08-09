// INTERFACING 16X2 LCD WITH PIC16F877A MICROCONTROLLER IN 8 BIT MODE
// https://exploreembedded.com/wiki/Interfacing_LCD_with_PIC16F877A_8-bit_mode
#include <xc.h>

__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_OFF & LVP_ON & CPD_OFF & WRT_OFF & CP_OFF);//set configuration setting
#define _XTAL_FREQ 20000000//set crystal frequency
#define RS PORTDbits.RD0//define Pin RD0 as RS
#define RW PORTDbits.RD1//define Pin RD1 as RW
#define EN PORTDbits.RD2//define Pin RD2 as EN

void lcd_data(unsigned char data)
{
    PORTC = data;
    RS = 1;
    RW = 0;
    EN = 1;
    __delay_ms(5);
    EN = 0;
}

void lcd_command(unsigned char cmd)
{
    PORTC = cmd;
    RS = 0;
    RW = 0;
    EN = 1;
    __delay_ms(5);
    EN = 0;
}

void lcd_string(const unsigned char *str,unsigned char num)  
{
    unsigned char i;
    for(i=0;i<num;i++)
    {
      lcd_data(str[i]);  
        
    }
}

void lcd_initialise()
{
    lcd_command(0x38);//Function Set: 8-bit, 2 Line
    lcd_command(0x06);//Entry Mode
    lcd_command(0x0C);//Display on Cursor off
    lcd_command(0x01);//Clear Display (also clear DDRAM content)
}

void main(void) 
{
    TRISC = 0x00;//set Port C as output
    TRISD = 0x00;//set Port D as output
    lcd_initialise();
    while(1)
    {
        lcd_command(0x83);//placing the cursor on the 4th position
        //lcd_command(0x80);//placing the cursor on the 1st position
        lcd_string("SUBSCRIBE",9);//display 9 character
        lcd_command(0xC0);//Shift entire display right
        lcd_string("ANOKHAUTOMATION",15);//display 15 character
    }
    return;
}













