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
#include <string.h>

extern char display_line[FOURTH][COUNT_ELEVEN];
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
unsigned int loop;

void paths(void){
        
    switch (event) {
      case STRAIGHT:
        Straight();
        strcpy(display_line[THIRD_LINE], " STRAIGHT  ");

        break;
      case CIRCLE:
        Circle();
        strcpy(display_line[THIRD_LINE], " CIRCLE  ");

        break;
      case TRIANGLE:
        Triangle();
        strcpy(display_line[THIRD_LINE], " TRIANGLE  ");
        break;
      case FIG_EIGHT:
        Fig_Eight();
        strcpy(display_line[THIRD_LINE], " FIGURE 8  ");
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
    time_change = RESET_STATE;
    if(delay_start++ >= WAITING2START){
      delay_start = RESET_STATE;
      state = START;
    }
  }
}

void start_case(void){
  cycle_time = RESET_STATE;
  right_motor_count = RESET_STATE;
  left_motor_count = RESET_STATE;
  Forward_On();
  segment_count = RESET_STATE;
  count = RESET_STATE;
  myTime = RESET_STATE;
  loop = RESET_STATE;
  state = RUN;
}

void run_case_straight(void){
  if(time_change){
    time_change = RESET_STATE;
    cycle_time++;
    if (segment_count <= TRAVEL_DISTANCE){
      if(right_motor_count++ >= RIGHT_COUNT_TIME){
        P6OUT &= ~R_FORWARD;
      }
      if(left_motor_count++ >= LEFT_COUNT_TIME){
        P6OUT &= ~L_FORWARD;
      }
      if(cycle_time >= COUNT_TEN){
        cycle_time = RESET_STATE;
        right_motor_count = RESET_STATE;
        left_motor_count = RESET_STATE;
        segment_count++;
        Forward_On();
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
        CW_Turn();
      }
      else{
        Forward_On();
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
    time_change = RESET_STATE;
    if (myTime > STAGEONE){
      switch (loop){
      case LOOPONE:
        CW_Turn();
        break;
      case LOOPTWO:
        CCW_Turn();
        break;
      default: break;
      }
    }
    else{
        Forward_On();
    }
    myTime ++;
    
    if(myTime == STAGETWO){
      myTime = RESET_STATE;
      count ++;
    
    if(count % LOOP == RESET){
      switch(loop){
        case LOOPONE:
          loop = LOOPTWO;
          break;
        case LOOPTWO:
          loop = LOOPONE;
          break;
      default: break;
      }
    }
    }
    
    if(count == FOURLOOP){
      state = END;
    }
   
  }
}
      

void run_case_triangle (void){
  if(time_change){
    time_change = RESET_STATE;
    if(myTime > STAGETWOTRI){
      Forward_On();
    }
    else if(myTime > STAGEONETRI){
      CCW_Turn();
    }
    else{
      Forward_On();
    }
    myTime++;
    if(myTime == STAGETHREETRI){
      myTime = RESET_STATE;
      count++;
    }
    if (count >= TRI){
      state = END;
    }
  }
}
    

void end_case(void){
  Forward_Off();
  state = WAIT;
  event = NONE;
}




