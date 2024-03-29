//------------------------------------------------------------------------------
//
//  Michael Barilla
//  FEB 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//
//   Description: This function initalizes the timersB0-0,1,2, and overflow
//      Timer B0-0      Time_Sequence Setting, LCD Flash, LCD Update
//      Timer B0-1      SW1 and SW2 debounce
//      
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "macros.h"
#include  "functions.h"


void Init_Timers(void){
  Init_Timer_B0();
  Init_Timer_B3();
}


//-----------------------------------------------------------------------------
// Timer B0 initialization sets up both B0_0, B0_1-B0_2 and overflow
//-----------------------------------------------------------------------------
void Init_Timer_B0(void){

  TB0CTL = RESET;               // Clear TB0 Control Register
  TB0EX0 = RESET;               // Clear TBIDEX Register
  TB0CTL |= TBSSEL__SMCLK;      // SMCLK source
  TB0CTL |= MC__CONTINOUS;      // Continuous up to 0xFFFF and overflow
  TB0CTL |= ID__2;              // Divide clock by 2
  TB0EX0 |= TBIDEX__8;          // Divide clock by an additional 8
  TB0CTL |= TBCLR;              // Resets TB0R,
  
  // Capture Compare 0
  // #pragma vector = TIMER0_B0_VECTOR
  
  // Capture Compare 0 - LCD Flash
  TB0CCR0 = TB0CCR0_INTERVAL;   // CCR0
  TB0CCTL0 |= CCIE;             // CCR0 enable interrupt
  
  // Capture Compare 1,2, Overflow
  // #pragma vector = TIMER0_B1_VECTOR
  
  // Capture compare 1 - Switch Debounce
  TB0CCR1 = TB0CCR1_INTERVAL;// CCR1
  TB0CCTL1 &= ~CCIFG; // CCR1 clear interrupt flag
  TB0CCTL1 &= ~CCIE; // CCR1 disable interrupt
  
  // Capture compare 2 - LCD Update
 TB0CCR2 = TB0CCR2_INTERVAL;// CCR2
 TB0CCTL2 &= ~CCIFG; //CCR2 clear interrupt flag
 TB0CCTL2 &= ~CCIE; // CCR2 enable interrupt
  

  
  // Overflow
  TB0CTL &= ~TBIE; // Disable Overflow Interrupt
  TB0CTL &= ~TBIFG; // Clear Overflow Interrupt flag
}

void Init_Timer_B3(void){
  TB3CTL = TBSSEL__SMCLK;                 //Source = SMCLK
  TB3CTL |= MC__UP;                       //Up Mode
  TB3CTL |= TBCLR;                        //Clear TAR

  TB3CCR0 = WHEEL_PERIOD;                 //PWM Period

  TB3CCTL1 = OUTMOD_7;                    //CCR1 reset/set
  RIGHT_FORWARD_SPEED = WHEEL_OFF;        //P6.0 Right Forward PWM duty cycle

  TB3CCTL2 = OUTMOD_7;                    //CCR2 reset/set
  LEFT_FORWARD_SPEED = WHEEL_OFF;         //P6.1 Left Forward PWM duty cycle

  TB3CCTL3 = OUTMOD_7;                     //CCR3 reset/set
  RIGHT_REVERSE_SPEED = WHEEL_OFF;       //P6.2 Right Reverse PWM duty cycle

  TB3CCTL4 = OUTMOD_7;                    //CCR4 reset/set
  LEFT_REVERSE_SPEED = WHEEL_OFF;          //P6.3 Left Reverse PWM duty cycle
}






