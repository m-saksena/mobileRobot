#include <hidef.h>
#include "derivative.h"
#include "delay.h"

// function to initialize the ADC
// this function will be called once, at the start of the program to set up ADC
void init_ADC(void)

{

      
     ATD0CTL2_ADPU = 1;       // ADT Control Reigster 2, bit 7
                               // Normal ATD functionality
                               // remaining values set to default
      
     ATD0CTL3 = 0b00001000;   // ADT Control Register 3
                               //set to 1 conversion per seq (fastest)
                              // only one channel is read
                              
     ATD0CTL4 = 0b10000000;    // ADT Control Register 4    
                                // 8 bit resolution
                                // divide bus clock by the least number
                                //maximize ADTclock  

      
      
                                
       
}


 // function to start the analogue to digital conversion process
 // this function will  be called every time we want to read from the ADC
 void start_conv(char channel)
 {

  if (channel == 0) 
  {
     //channel 0
        ATD0CTL5 = 0b10000000 ;
        ATD0CTL5 = 0b10000000 ;    
                                    // ADT Control Register 5                  
                                    // start a new conversion sequence
                                   //8-bit / right justified / unsigned - bits 0-7
                                // only one conversion per channel: AN0
  }
  
  //PROBLEM!!!!
  
  if (channel == 1) 
  {
       ATD0CTL5 = 0b10000001 ;
       ATD0CTL5 = 0b10000001 ;
  }
  
  if (channel == 2) 
  {
       ATD0CTL5 = 0b10000010 ;
       ATD0CTL5 = 0b10000010 ;
  }  

   //PROBLEM!!!!    

   
 }
 
 
 // function to read the result of the ADC.
 // If the conversion has not completed, it should wait until it has finished
 // before returning values 
 char readADC(void) 
 {
 
  char x;
  //long T_delay = 200000;
    
  while (ATD0STAT0_SCF == 0) 
  
  {
  }
  
  
   x = ATD0DR0L;           // ADT status register 0 lower bits
   
   return x;
  
 }