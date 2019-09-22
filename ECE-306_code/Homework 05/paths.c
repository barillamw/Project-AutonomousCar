//------------------------------------------------------------------------------
//
//  Description: This file contains the functions to drive the car on a pre-designed 
//  path.
//
//  Michael Barilla
//  Feb 2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include "macros.h"

extern unsigned int cycle_time;
extern unsigned int time_change;
extern unsigned char event;
extern unsigned char state;
extern unsigned char shape;
extern volatile unsigned int Time_Sequence;
unsigned int delay_start;
unsigned int left_motor_count;
unsigned int right_motor_count;
unsigned int segment_count;
unsigned int count;
unsigned int myTime;
void paths(void){
        
    switch (event) {
      case STRAIGHT:
        Straight();
        break;
      case CIRCLE:
        Circle();
        break;
      case TRIANGLE:
        Triangle();
        break;
      case FIG_EIGHT:
        Fig_Eight();
        break;
      default: break;
    }
}

void Straight (){
  switch(state){
    case WAIT:
      wait_case();
      break;
    case START:
      start_case();
      break;
    case RUN:
      run_case_straight();
      break;
    case END:
      end_case();
      break;
    default: break;  
  }
}

void Circle (){
  switch(state){
    case WAIT:
      wait_case();
      break;
    case START:
      start_case();
      break;
    case RUN:
      run_case_circle();
      break;
    case END:
      end_case();
      break;
    default: break;  
  }
}

void Fig_Eight(){
  switch(state){
    case WAIT:
      wait_case();
      break;
    case START:
      start_case();
      break;
    case RUN:
      run_case_eight();
      break;
    case END:
      end_case();
      break;
    default: break;  
  }
}

void Triangle () {
  switch(state){
    case WAIT:
      wait_case();
      break;
    case START:
      start_case();
      break;
    case RUN:
      run_case_triangle();
      break;
    case END:
      end_case();
      break;
    default: break;  
  }
}


void wait_case(){
  if(time_change){
    time_change = 0;
    if(delay_start++ >= WAITING2START){
      delay_start = 0;
      state = START;
    }
  }
}

void start_case(void){
  cycle_time = 0;
  right_motor_count = 0;
  left_motor_count = 0;
  Forward_On();
  segment_count = 0;
  state = RUN;
}

void run_case_straight(void){
  if(time_change){
    time_change = 0;
    cycle_time++;
    if (segment_count <= TRAVEL_DISTANCE){
      if(right_motor_count++ >= RIGHT_COUNT_TIME){
        P6OUT &= ~R_FORWARD;
      }
      if(left_motor_count++ >= LEFT_COUNT_TIME){
        P6OUT &= ~L_FORWARD;
      }
      if(cycle_time >= 10){
        cycle_time = 0;
        right_motor_count = 0;
        left_motor_count = 0;
        segment_count++;
        Forward_Move();
      }
    }else{
      state = END;
    }
  }
}

void run_case_circle (void){
  if(time_change){
      time_change = RESET;
      if (myTime > STAGEONE){
        P6OUT |= L_FORWARD;
        P6OUT &= ~R_FORWARD;
      }
      else{
        P6OUT |= L_FORWARD;
        P6OUT |= R_FORWARD;
      }
      myTime ++;
      
      if (myTime == STAGETWO){
        myTime = RESET_STATE;
        count ++;
      }
      
      if (count == TWOLOOP){
        state = END;
      }
  }
}

void run_case_eight (void){
  if(time_change){
    time_change = 0;
    cycle_time++;
    if (segment_count <= TRAVEL_DISTANCE){
      if(right_motor_count++ >= RIGHT_COUNT_TIME){
        P6OUT &= ~R_FORWARD;
      }
      if(left_motor_count++ >= LEFT_COUNT_TIME){
        P6OUT &= ~L_FORWARD;
      }
      if(cycle_time >= 10){
        cycle_time = 0;
        right_motor_count = 0;
        left_motor_count = 0;
        segment_count++;
        Forward_Move();
      }
    }else{
      state = END;
    }
  }
}

void run_case_triangle (void){
  if(time_change){
    time_change = 0;
    cycle_time++;
    if (segment_count <= 3){
      if(right_motor_count++ >= 88){
        P6OUT &= ~R_FORWARD;
      }
      if(left_motor_count++ >= 88){
        P6OUT &= ~L_FORWARD;
      }
      if(cycle_time >= 100){
        cycle_time = 0;
        right_motor_count = 0;
        left_motor_count = 0;
        segment_count++;
        CCW_Turn(30);
        Forward_Move();
      }
      
    }else{
      state = END;
    }
  }
  
}


void end_case(void){
  Forward_Off();
  state = WAIT;
  event = NONE;
}

void Forward_On(){
  P6OUT |= R_FORWARD;
  P6OUT |= L_FORWARD;
}

void Forward_Move(){
  P6OUT |= R_FORWARD;
  P6OUT |= L_FORWARD;
}

void Forward_Off(){
  P6OUT &= ~R_FORWARD;
  P6OUT &= ~L_FORWARD;
}

void CCW_Turn(int angle){
  int count=0;
  while(count < angle){
      P6OUT &= ~R_FORWARD;
      P6OUT |= L_FORWARD;
      count ++;
  }
}