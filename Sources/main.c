#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "camera.h"
#include "adc.h"
#include "pwm.h"
#include "delay.h"
#include "sensor.h"

//CAMERA VARIABLES
long T_delay = 1000;
unsigned short max;


//MOTOR VARIABLES
short L_straight;       // left side motor - going straight
short R_straight;       // right side motor - going straight
//short L_turn  = 128;       // right side motor - turning
//short R_turn = -128;        // right side motor - turning
//unsigned long T_straight = 20000;   // time spent going in straightl ine
unsigned long T_turn = 90000;       // time spent turning
//unsigned long diff;         // difference between two speeds

//CAMERA VARIABLES
char leftBlack ;
char rightBlack;
char centreBlack;
char LLblack, RRblack;
char error = 0; //leftblack - rightblack
char K = 13;     // gain 1
char turn;
// total gain = error * K



//SENSOR VARIABLES
char right_sensor;
char left_sensor;
char sensor_thresh = 60;
long delay_reverse = 20000;



void straight(char error); 


void main(void) 
{
    init_camera();
    pwm_init();
   
     
   
    while(1) 
    {
    
      
    
      //camera saturation
      T_delay = Tdelay(T_delay, max);
      camera(T_delay);
      blackVector();
      
      L_straight = 255;
      R_straight = 255;
      
      leftBlack = sumBlack(0,32);
      rightBlack = sumBlack(32,64);
      centreBlack = sumBlack(5,59);
      LLblack = sumBlack(0,5);
      RRblack = sumBlack(59,64);
      
     
      
      error = leftBlack - rightBlack;
      
      if (centreBlack > 0) //i.e. the line is in front of the robot, roughly in the centre
      {
      
      
              if (LLblack == 0 && RRblack == 0) 
              {
                 
                 straight(error);
              
              } 
              
              if (LLblack > 0) 
              {
                straight(error);
                turn = 1;
              }
              
              
              else if (RRblack > 0) 
              {
                straight(error);
                turn = 2;
              }
      
      }
      
      
  
      
      else if (centreBlack == 0) 
      {
          
          if (turn == 1) 
          {
          L_straight = 255;
          R_straight = -255;
          }
          
          if (turn == 2) 
          {
          L_straight = -255;
          R_straight = 255; 
          }
          
          
      }
      
    
    
    
        //-----------------------sensor------------------------------------------  
    left_sensor = sensor_left();
    right_sensor = sensor_right();

    
  if (left_sensor > sensor_thresh || right_sensor > sensor_thresh) 
    {
       L_straight = -255;
       R_straight = -255;
       motor(L_straight, R_straight);
       delay(delay_reverse);
       
       
       turn = 2;
       
       L_straight = -255;
       R_straight = 255;
       motor(L_straight, R_straight);
       delay(T_turn); //turns approx 90 degrees     #
      
      /* 
       if (centreBlack > 0) //i.e. the line is in front of the robot, roughly in the centre
      {
      
      
              if (LLblack == 0 && RRblack == 0) 
              {
                 
                 straight(error);
              
              } 
              
              if (LLblack > 0) 
              {
                straight(error);
                turn = 1;
              }
              
              
              else if (RRblack > 0) 
              {
                straight(error);
                turn = 2;
              }
      
      }    */
      
      
  
      
     if (centreBlack == 0) 
      {
          
          if (turn == 1) 
          {
          L_straight = 255;
          R_straight = -255;
          }
          
          if (turn == 2) 
          {
          L_straight = -255;
          R_straight = 255; 
          }
          
          
      }
      
     
       
       
       
     
     
  
    } 
    
    
    
    
    
      
 
    motor(L_straight, R_straight); 
    
    }







}



void straight(char error) 
{
        if (error < 0) 
      {
       
        L_straight =  255 - K * (-1) * error;
        //L_straight =  L_straight + K * (-1) * error;
        R_straight = 255;
      } 
      
      else if (error > 0) 
      {
        
        R_straight = 255 - K * error;
        //R_straight = R_straight + K * error;
        L_straight = 255;
           
      } 
}

