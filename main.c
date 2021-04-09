#include "msp.h"
#define TIMER_PERIOD 15000000  //produces a 5 second count interval

/**
 * This program is designed to reduce power consumption of street lights
 * by using I/O motion sensors, timers, and interrupts to detect when a
 * car is in the area and then turn off the street light after a
 * five second interval and when the sensor is outputting a low voltage
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	P1->DIR |= BIT0;   //set pin P1.0 as output
	P1->DIR &= ~BIT5;  //set pin P1.5 as input
	P1->OUT &= ~BIT0;  //turn pin P1.0 off
	P2->DIR |= BIT2;   //set up pin P2.2 as output
	P2->OUT &= ~BIT2;  //turn pin P2.2 off

	TIMER32_1->LOAD = TIMER_PERIOD;  //set the timer32 count value to cause an
	                                 //interrupt five seconds after the sensor
	                                 //produces a low zero from no traffic
	TIMER32_1->CONTROL = 0XE2;     //turn on the timer and set up other specs
	//ENABLE: 1 start the timer
	//MODE: 1 periodic mode
	//IE: 1 enable interrupts
	//PRESCALE: 000 no clock divider
	//SIZE: 1 for 32-bit timer
	//ONESHOT: 0 wrapping mode

	P1->IE |= BIT5;      //enable the interrupt for pin P1.5
	P1->IFG &= ~BIT5;    //clear the interrupt flag for pin P1.5
	NVIC->ISER[0] = 0x02000000; //enable Timer32_1 interrupts
	NVIC->ISER[1] |= 0x8;   //enable port 1 interrupts
	_enable_interrupts();


	while (1);  //wait for an interrupt

}

/***************************************
 * Interrupt handler for port 1. When
 * the PIR sensor detects car traffic/motion
 * an interrupt is triggered to turn on
 * the street light or in our case the led
 * at pin P1.0. This interrupt resets the five
 * second interval
 **************************************/
void PORT1_IRQHandler(void)
{
   uint32_t status;
   status = P1->IFG;    //get the interrupt status for port 1
   P1->IFG &= ~BIT5;    //clear the interrupt for port 1, pin 5
   if(status & BIT5)  //there is traffic on the street
   {
      P1->OUT |= BIT0;  //turn on the street light
      TIMER32_1->CONTROL = 0X00; //stop the timer
      TIMER32_1->CONTROL = 0XE2; //restart it
   }
}

/***************************************
 * Interrupt handler for the timer32 module.
 * When the five second time interval has been
 * reached this interrupt will be triggered
 * and if the PIR sensor is outputting a low
 * voltage then the street light will be turned
 * off
 **************************************/
void T32_INT1_IRQHandler(void)
{
    TIMER32_1->INTCLR = 0;  //clear the timer interrupt flag
    if ((P1->IN & BIT5) == 0x00) //There traffic on the street
    {
        P1->OUT &= ~BIT0;  //turn off the street light
        //P2->OUT |= BIT2;  used for debugging purposes
    }

}





