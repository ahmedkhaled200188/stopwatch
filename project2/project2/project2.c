#include<avr/interrupt.h>
#include<util/delay.h>
#include<avr/io.h>
void timer1_int(void);
char sec1=0,sec2=0,min1=0,min2=0,h1=0,h2=0;
int count ;

int main(void)
{
DDRB&=~(1<<PB2);
PORTB|=(1<<2);//activate internal pull up
DDRD&=~(1<<PD2);
PORTD|=(1<<2);//activate internal pull up
DDRD&=~(1<<PD3);
DDRC|=0x0f;//output pins of seven segment
DDRA|=0x3f;//output activate for seven segment
GICR|=(1<<INT0)|(1<<INT1)|(1<<INT2);
MCUCR|=(1<<ISC01)|(1<<ISC11)|(1<<ISC10);//INT 0 falling edge , 1 with rising edge , 1 with falling edge
SREG|=(1<<7);
timer1_int();
while(1)
{

	 PORTA = 0x01;
	 PORTC = sec1;
	 _delay_ms(1);
	 PORTA = 0x02;
	 PORTC = sec2;
	 _delay_ms(1);
	 PORTA = 0x04;
	 PORTC = min1;
	 _delay_ms(1);
	 PORTA = 0x08 ;
	 PORTC = min2;
	 _delay_ms(1);
	 PORTA = 0x10;
	 PORTC = h1;
	 _delay_ms(1);
	 PORTA = 0x20 ;
	 PORTC = h2;
	 _delay_ms(1);



}

}
void timer1_int(void)
{
    TCNT1 = 0;
    TCCR1A = 0;
    TCCR1B |= (1 << WGM12) | (1 << CS10) | (1 << CS12);
    OCR1A = 977;//1 MHz / (1024 * (977 + 1)) = 1 sec
    TIMSK |= (1 << OCIE1A);
    SREG|=(1<<7);
}
ISR(TIMER1_COMPA_vect)
{

	sec1++;
        if(sec1==10)
        {
        	sec2++;
        	sec1=0;
        }
        if(sec2==6)
           {
           	min1++;
           	sec2=0;
           }
        if(min1==10)
        {
        	min2++;
        	min1=0;
        }
        if(min2==6)
        {
        	h1++;
        	min2=0;
        }
        if(h1==10)
        {
        	h2++;
        	h1=0;
        }
        if(h1==4&&h2==2)
        {
        	sec1=0,sec2=0,min1=0,min2=0,h1=0,h2=0;
        }



}
ISR(INT0_vect)
{
	sec1=0,sec2=0,min1=0,min2=0,h1=0,h2=0;
	TCNT1 = 0;


}
ISR(INT1_vect)
{
	TCCR1B=0;

}
ISR(INT2_vect)
{
	TCCR1B |= (1 << WGM12) | (1 << CS10) | (1 << CS12);

}
