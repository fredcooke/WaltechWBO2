#include <avr/interrupt.h>
#include <stdlib.h>
#include "initilize_hardware.h"

void timer0init(void)    /* initializes the timer and enables interrupts. *///
{
TIMSK |= (_BV(TOIE0));// overflow capture enable
//TCCR0 |= (_BV(CS00));// timer started with /8 prescaler  fills up @1953 hz (4mhz clock)
//TCCR0 |= (_BV(CS00)|_BV(CS01));// timer started with /64 prescaler  fills up @245 hz
TCCR0 |= (_BV(CS02));// timer started with /256 prescaler  fills up @60 hz
//TCCR0 |= (_BV(CS00)|_BV(CS02));// timer started with /1024 prescaler  fills up @15 hz
}

void adc_init(void)
{
    //ADCSRA |= ( (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0) );// adc prescale bits 111= div by 128 (8mhz)62.5khz
	//ADCSRA |= (1<<ADPS2);// adc prescale bits 100= div by 16 (1mhz crystal)  62.5khz
	ADCSRA |= (1<<ADPS0)|(1<<ADPS2);// adc prescale bits  div by 32 (4mhz crystal ==> 125khz)
	//ADCSRA |= ((1<<ADPS2)|(1<<ADPS1));// adc prescale bits div by 64 (4mhz crystal)62.5khz
	
	//below not needed if you set mux in when sampling:
	//ADMUX =  (1<<REFS0);//sets to Avcc as ref voltage
    ADMUX =  ( (1<<REFS0)|(1<<REFS1) );// sets to 2.5v internal ref.
	//default admux 0000 = adc0
	
	ADCSRA |= (1<<ADEN); // enable the ADC
    ADCSRA |= (1<<ADIE); // enable ADC conversion complete interrupt
    //ADCSRA |= (1<<ADFR);// starts  free running mode
	ADCSRA |= (1<<ADSC);// starts  conversion
}	

void setup_timer1(void)// pump control current dac on OC1A
{

TCCR1A |= (1<<COM1A1); // COM1a1 =0, com1a0 =1 clear occ1a on compair match counting up 
//TCCR1A |=    ; //wgm11,10 = 0 PWM pahse and freq correct icr1 is top see page 99
TCCR1B |= (1<<WGM13);//wgm13 set see above
//TCCR1B |= ((1<<CS10)|(1<<CS12));// cs12,11,10 clock prescaler = 1/1024 see page 100
TCCR1B |=(1<<CS10); // timer on, no scaler
ICR1=PWMPUMP_FREQ;// this ts the "top" value of the timer, sets the frequency. 330 gives about 6khz
DDRB |= _BV(1);//Set PORTB1 pin as output (OC1A)
OCR1A = 116;// Set PWM value to 116. 0 current. 1.7v. max is ICR1 (330 as of now)

}

void setup_timer2(void)//output 0-5v on OC2 
{
DDRB |=(1<<3);//Set PORTB3 pin as output (OC2)
TCCR2 |= (1<<WGM20)|(1<<WGM21); // fast pwm
TCCR2 |= (1<<COM21); // clear oc2 on compair, set at bottom. Pg.118
TCCR2 |=(1<<CS10); // timer on, no scaler  gives about 15khz 
OCR2= 0;// Set PWM value to 0.
}