

#define PWMPUMP_FREQ 330 //value for TOP of pump PWM timer, sets frequency

void timer0init(void); //timer for heater pwm control
void adc_init(void);//adc 
void setup_timer1(void);// pump control current dac on OC1A 
void setup_timer2(void);//output 0-5v on OC2  