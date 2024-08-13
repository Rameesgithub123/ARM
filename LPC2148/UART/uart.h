#ifndef UART_H
#define UART_H

#include <lpc214x.h>
#define PCLK 15000000

void UART0_Init(unsigned int BaurdRate);
void UART0_InitAuto();
unsigned int UART0_GetdBaudRate(void);
void UART0_Write(char DATA);
char UART0_Read();
void UART0_Print(char *str);
unsigned UART0_RecieveUntil(char c, char *str, unsigned length);
char UART0_IsAvailable();
void UART1_Init(unsigned int BaurdRate);
void UART1_InitAuto();
unsigned int UART1_GetdBaudRate(void);
void UART1_Write(char DATA);
char UART1_Read();
void UART1_Print(char *str);
unsigned UART1_RecieveUntil(char c, char *str, unsigned length);
char UART1_IsAvailable();

#endif /* UART_H */
