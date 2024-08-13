#include  "lcd.h"
//delay
void delay_ms(unsigned long int i){
	unsigned int j;
	while(i-- >0)
		for(j=0;j<5000;j++);
}

// send camand
void LCD_CMD(LCD *lcd,unsigned char cmd){
	IO1CLR |=lcd->RS;
	delay_ms(1);
	(((cmd>>4)&1)==1)?(IO0SET |=lcd->D4):(IO0CLR |=lcd->D4);
	(((cmd>>5)&1)==1)?(IO0SET |=lcd->D5):(IO0CLR |=lcd->D5);
	(((cmd>>6)&1)==1)?(IO0SET |=lcd->D6):(IO0CLR |=lcd->D6);
	(((cmd>>7)&1)==1)?(IO0SET |=lcd->D7):(IO0CLR |=lcd->D7);
	IO1SET |=lcd->EN;
	delay_ms(2);
	IO1CLR |=lcd->EN;
	(((cmd)&1)==1)?(IO0SET |=lcd->D4):(IO0CLR |=lcd->D4);
	(((cmd>>1)&1)==1)?(IO0SET |=lcd->D5):(IO0CLR |=lcd->D5);
	(((cmd>>2)&1)==1)?(IO0SET |=lcd->D6):(IO0CLR |=lcd->D6);
	(((cmd>>3)&1)==1)?(IO0SET |=lcd->D7):(IO0CLR |=lcd->D7);
	IO1SET |=lcd->EN;
	delay_ms(2);
	IO1CLR |=lcd->EN;
}
// initialise lcd
void LCD_INIT(LCD *lcd,unsigned int RS,unsigned int EN,unsigned int D4,unsigned int D5,unsigned int D6,unsigned int D7){
	IO0DIR |= ( D4 | D5 | D6 | D7 ); // Set port pins as out put
    IO1DIR |= (RS | EN);
    lcd->RS = RS;
    lcd->EN = EN;
    lcd->D4 = D4;
    lcd->D5 = D5;
    lcd->D6 = D6;
    lcd->D7 = D7;
	LCD_CMD(lcd,0x02); // Initialize in 4-bit mode
  LCD_CMD(lcd,0x28); // 2 lines, 5x8 matrix
	LCD_CMD(lcd,0x0C); // Display ON, cursor OFF
	LCD_CMD(lcd,0x06); // Auto-increment cursor
	LCD_CMD(lcd,0x01); // Clear display
	delay_ms(2);
}
//send data to display
void LCD_DATA(LCD *lcd,unsigned char data){
	IO1SET |=lcd->RS;
	delay_ms(1);
	(((data>>4)&1)==1)?(IO0SET |=lcd->D4):(IO0CLR |=lcd->D4);
	(((data>>5)&1)==1)?(IO0SET |=lcd->D5):(IO0CLR |=lcd->D5);
	(((data>>6)&1)==1)?(IO0SET |=lcd->D6):(IO0CLR |=lcd->D6);
	(((data>>7)&1)==1)?(IO0SET |=lcd->D7):(IO0CLR |=lcd->D7);
	IO1SET |=lcd->EN;
	delay_ms(2);
	IO1CLR |=lcd->EN;
	(((data)&1)==1)?(IO0SET |=lcd->D4):(IO0CLR |=lcd->D4);
	(((data>>1)&1)==1)?(IO0SET |=lcd->D5):(IO0CLR |=lcd->D5);
	(((data>>2)&1)==1)?(IO0SET |=lcd->D6):(IO0CLR |=lcd->D6);
	(((data>>3)&1)==1)?(IO0SET |=lcd->D7):(IO0CLR |=lcd->D7);
	IO1SET |=lcd->EN;
	delay_ms(2);
	IO1CLR |=lcd->EN;
}
// print a string in display
void LCD_Print(LCD *lcd,const char *str) {
    while (*str)
        LCD_DATA(lcd,*str++);
}
// set cursor
void LCD_SetCursor(LCD *lcd,short int row, short int column) {

    short int position;
    if (row == 1)
        position = 0x80 + column; // Address of the first line
    else if (row == 2)
        position = 0xC0 + column; // Address of the second line

    LCD_CMD(lcd,position); // Set cursor position
}
// clear display
void LCD_Clear(LCD *lcd) {
    LCD_CMD(lcd,0x01);
    delay_ms(2);
}
// Print Intiger value
void LCD_Print_Int(LCD *lcd,long int x) {
    short int i = 0;
    char str[10];
    do {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }while (x);
    while(i)
        LCD_DATA(lcd,str[--i]);
}
