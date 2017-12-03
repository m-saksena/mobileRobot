#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */




void pwm_init(void)         // function will generate a pulse train

{
  
  PWMPRCLK_PCKA1 = 1;         // Set frequency of clock A to quarter bus clock
  PWMSCLA = 1;              // full scale value of PWMSCLA = 256
  
  PWMSCLA = 1 ;     // frequency of clock SA is half of clock A
  PWMCLK = 3;         // Clock SA source for PWM channel 0
  PWME = 3;                // Enable waveform output          `
  PWMCAE = 3;          // making signal centre aligned
  PWMPER0 = 255;            // period of pulse train is 510 times period of clock SA
  PWMPER1 = 255;            // period of pulse train is 510 times period of clock SA
  PWMPOL = 3;                // starting polarity is high

  
  
  
  DDRT = 0b11000000;             // set port T to be an output 
                               //(direction control signal of RH motor = bit 6; LH motor = bit 7)
                               
  DDRP = 0b00000011;             // set port P to be an output (PWM speed control)
                                 //LH motor = bit 1; RH motor = bit 0)
  
}


void motor(short L, short R) 

{

  short rR;//pulse width of right motor (0 to 255)
  short rL;// pulse width of left motor (0 to 255) 
  short rdR;// set bit 6 of port T = RH motor direction control signal (1= fwd or 0 = reverse)
  short rdL;// set bit 6 of port T = LH motor direction control signal (1= fwd or 0 = reverse)

 // L and R take range -32768 to + 32768
 
 // if L or R is > 0, set rDL or rDr = 1
 // if L or R is < 0, set rDL or rDr = 0 and make rR or rL positive
 
 
 //magnitude limiting
 // if L or R > 255, set L or R = 255



// LEFT MOTOR
// setting direction
if (L > 0) 
{
    rdL = 1;
    rL = L;
    
} 

else 
{
   rdL = 0;
   rL = -L;
}

// magnitude control

if (rL > 255) 
{
   rL = 255;
}


// RIGHT MOTOR
// setting direction
if (R > 0) 
{
    rdR = 1;
} 

else 
{
   rdR = 0;
   rR = -R;
}


// magnitude control
if (rR > 255) 
{
   rR = 255;
}




 // OUTPUTTING TO PIN


  PWMDTY0 = (unsigned char) rR;       //pulse width of right motor (0 to 255)        
  PWMDTY1 = (unsigned char) rL;       // width of left motor (0 to 255)       
  PTT_PTT6 = (unsigned char) rdR;     // set bit 6 of port T = RH motor direction control signal (1= fwd or 0 = reverse)
  PTT_PTT7 = (unsigned char) rdL;     // set bit 6 of port T = LH motor direction control signal (1= fwd or 0 = reverse)

}
