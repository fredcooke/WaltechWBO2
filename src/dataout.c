
#include "dataout.h"

uint8_t put_in_string(int16_t number, char letter, uint8_t place)//place is 4 digit spotplus 2 for something else, count from right
{
	//
	//'place' is the target place for the next character
	//
	//
	char temps[5] = "\0\0\0\0\0";//temporary spot for the number to add to the big string 

	if (number <= 9999 || number<= -9999)
	{
		//ultoa
		itoa(number, temps, 10); // integer number --> string temps base 10
	}
	else
	{
		strcpy(temps,"over");// only 4 digits plus sign allowed
	}
	uint8_t datalen = strlen(temps);//actual legnth of ADC data
	if (letter != '\0')//dont put in the letter and the colon if '\0'
		{
		serialout[place] = letter;
		place++;
		serialout[place] = ':';
		}
	else 
	{
	place--;
	}
	for (uint8_t i=0; i<datalen; i++) 
	{
		place++;
		serialout[place] = temps[i];
		
	}
	place++;
	serialout[place] = ','; 
	return  (place+1);
	
}

void uart_putch(uint8_t c)
{
    //if(c == '\n')
     //   uart_putc('\r');

    /* wait until transmit buffer is empty */
    while(!(UCSRA & (1 << UDRE)));
    /* send next byte */
    UDR = c;
}

void uart_putst(const char* s)
{
    while(*s)
        uart_putch(*s++);
}

void uart_put16dec(uint16_t d)
{
    uint16_t num = 10000;
    uint8_t started = 0;

    while(num > 0)
    {
        uint8_t b = d / num;
        if(b > 0 || started || num == 1)
        {
            uart_putch('0' + b);
            started = 1;
        }
        d -= b * num;

        num /= 10;
    }
}

uint8_t spitout(uint8_t place)
{

serialout[place-1] = '\n';
//uint8_t datalen = strlen(serialout);
//serialout[datalen] = '\n';//replace last char (,) with return
uart_putst(serialout);
for (uint8_t i= 0; i<LINESIZE ;i++)//blank serialout
{
	serialout[i] = '\0';
}
return 0;//reset place
}
