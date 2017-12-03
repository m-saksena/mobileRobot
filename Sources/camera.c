#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "adc.h"
#define clock PTM_PTM3      //clock   (BOOLEAN, 0 or 1)
#define SI PTM_PTM2        //SI       (BOOLEAN, 0 or 1)
#include "delay.h"

void init_camera(void) 
{
     DDRM = 0b00001100;             // set port M to be an output 
                               //Bit 2 = signal SI, bit 3 = clock signal
                               
     init_ADC();
     
     

}




//----------------------READ FUNCTION------------------
//output (global variable)
unsigned char cameraVector[64];

void read(void)         
{
   
char x;
 
 //generating clock

clock = 0;
SI = 1;
clock = 1;
SI = 0;
clock = 0;

 for(x = 0; x < 64; x++) 
 {

    start_conv(0);
    cameraVector[x] =  readADC();
    
    clock = 1; 
    clock = 0;       
 }

}
 


//--------------------------------------------------------------
 

unsigned short maxOutput(void) 

{
   // find max of cameraVector[x]
  
  unsigned short max = 0;
  unsigned char i;
  
  for (i = 0; i < 64; i++) 
  {
      if (cameraVector[i] > max) 
      {
           max = cameraVector[i];
      }
  
  }
  
  return max;
}

//------------TIME DELAY CALCULATION----------------
long Tdelay(long T_delay, unsigned short max)
 
 {
 
 //setting the delay time

unsigned short u;
unsigned short b;
//saturation level = 180
  
  
  max = maxOutput();
  u = 160;   //set empirically
  b = 150;
  
  if (max > u) 
  {
     T_delay = T_delay*9/10;
     
     if (T_delay == 0) 
     {
         T_delay = 1;
     }
  }
  
  
 if (max < b) 
 {
  T_delay = T_delay*11/10;
    
      if (T_delay < 10) 
      {
        T_delay++  ;
      }
  
 }
  
  
  
  
  return T_delay;
  
  
 }
 
   

 void camera(long T_delay) 
 
 {
  
          //------------DUMMY READ
      unsigned char dummyread[64];


         
      char x;
      
       //generating clock

      clock = 0;
      SI = 1;
      clock = 1;
      SI = 0;
      clock = 0;

             for(x = 0; x < 64; x++) 
             {

                start_conv(0);
                dummyread[x] =  readADC();
                
                clock = 1; 
                clock = 0;       
             }
    
       // ----------- TIME DELAY ------------------
         
          delay(T_delay);
           
     //--------------- TRUE READ-------------
          read();
 
 
 }

// --------------------------black ---------------------
char thresh = 85;             //threshold balue for black



// function that returns 1 if a pixel is black, 0 if it is white
char isBlack(char j) 

{ 
  char BW;
 
    
  if ( cameraVector[j] > thresh) // threshold value for black
  {
   BW = 0; // it is white 
  } 
  
  else 
  {
   BW = 1;  // it is black
  }
  
  return BW;
}

char black[64];     //global variable

void blackVector(void)

{
    
    char x;
    

    for(x = 0; x < 64; x++) 
    {
      black[x] = isBlack(x);
    }

    
}  


//--------------------left vs right--------------------------

char sumBlack(char a, char b)
// calculates the number of black pixels from pixel a to b
{
  char i;
  char sum_black;
  sum_black = 0; // total no. of black pixels from a to b
  for (i = a; i < b; i++) 
  {
    sum_black = sum_black + black[i];
  }
  
  return sum_black;
}
 
 
 
 
 



  
  
 
  
  
  
  
  
  
                   
