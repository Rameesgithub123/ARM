#include "uart.h"

// UART0 initialisation
void UART0_Init(unsigned int BaurdRate){
    int Divisor;
	PINSEL0 |=5;                       //Set P0.0 and P0.1 TX0 and RX0 pin
	Divisor=(PCLK/(16*BaurdRate));   //Calculate Divisor value
	U0LCR =0x83;                           //DLAB=1, 8bit, 1 Stopbit
	U0DLL	= Divisor & 0xFF;                      
	U0DLM	= (Divisor>>8) & 0xFF;
	U0LCR = 0x03;                          //DLAB=0, 8bit, 1 Stopbit
	U0FCR	=	7;                            //Enable and clear FIFO                              
}

void UART0_InitAuto(){
    PINSEL0 |=5;                       //Set P0.0 and P0.1 TX0 and RX0 pin	PINSEL0 |=1<<2;
    U0LCR = 0x83;          // DLAB = 0
    U0ACR = 0x01;  // Start auto-baud detection
	while(0x00 != (U0ACR & 0x01)){
        ;
    }
    U0LCR = 0x03;                          //DLAB=0, 8bit, 1 Stopbit
	U0FCR	=	7; 
}


unsigned int UART0_GetBaudRate(void) {
    return (PCLK / (16 * ((U0DLM << 8) + U0DLL)));
}

//UART0 send data
void UART0_Write(char DATA){
   while(!(U0LSR &(1<<5)));      //wait until previous transmistion complete
   U0THR = DATA;
}

//UART0 receive data
char UART0_Read(){
   while(!(U0LSR & 1));          //wait for reception complete
   return U0RBR;
}

//UART0 send string
void UART0_Print(char *str){
   while(*str )
      UART0_Write(*(str++));
}

unsigned UART0_RecieveUntil(char c, char *str, unsigned length){
   unsigned short count =0;
   for(;(*str = UART0_Read())!= c && count != length; count++,str++);
   *str='\0';
   return count;
}

char UART0_IsAvailable(){
   return U0LSR & 1;
}


//-----------------xxxxxx---------------xxxxxx-----------------------xxxx-----------------------xxxxxxx---------------------xxxxxxxx---------------



// UART1 initialisation
void UART1_Init(unsigned int BaurdRate){
    int Divisor;
	PINSEL0 |=(5<<16);                       //Set P0.8 and P0.9 TX1 and RX1 pin
	Divisor=(PCLK/(16*BaurdRate));   //Calculate Divisor value
	U1LCR =0x83;                           //DLAB=1, 8bit, 1 Stopbit
	U1DLL	= Divisor & 0xFF;                      
	U1DLM	= (Divisor>>8) & 0xFF;
	U1LCR = 0x03;                          //DLAB=0, 8bit, 1 Stopbit
	U1FCR	=	7;                            //Enable and clear FIFO                              
}

void UART1_InitAuto(){
	PINSEL0 |=(5<<16);                       //Set P0.8 and P0.9 TX1 and RX1 pin
	PINSEL0 |=1<<2;
    U1LCR = 0x83;          // DLAB = 0
    U1ACR = 0x01;  // Start auto-baud detection
	while(0x00 != (U1ACR & 0x01)){
        ;
    }
    U1LCR = 0x03;                          //DLAB=0, 8bit, 1 Stopbit
	U1FCR	=	7; 
}
unsigned int UART1_GetBaudRate(void) {
    return (PCLK / (16 * ((U1DLM << 8) + U1DLL)));
}

//UART1 send data
void UART1_Write(char DATA){
   while(!(U1LSR &(1<<5)));      //wait until previous transmistion complete
   U1THR = DATA;
}

//UART1 receive data
char UART1_Read(){
   while(!(U1LSR & 1));          //wait for reception complete
   return U1RBR;
}

//UART1 send string
void UART1_Print(char *str){
   while(*str )
      UART1_Write(*(str++));
}

unsigned UART1_RecieveUntil(char c, char *str, unsigned length){
   unsigned short count =0;
   for(;(*str = UART1_Read())!= c && count != length; count++,str++);
   *str='\0';
   return count;
}
      

char UART1_IsAvailable(){
   return U1LSR & 1;
}
