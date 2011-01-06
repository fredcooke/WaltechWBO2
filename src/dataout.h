#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include "stdint.h"
#define LINESIZE 50
char serialout[LINESIZE];

void uart_putch(uint8_t c);
void uart_putst(const char* s);
void uart_put16dec(uint16_t d);
uint8_t spitout(uint8_t place);
uint8_t put_in_string(int16_t number, char letter, uint8_t place); 


