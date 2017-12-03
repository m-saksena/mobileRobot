#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "adc.h"
#define clock PTM_PTM3      //clock   (BOOLEAN, 0 or 1)
#define SI PTM_PTM2        //SI       (BOOLEAN, 0 or 1)
#include "delay.h"

char signal_left, signal_right, V_left, V_right;

void init_sensor(void)
{
   init_ADC();
}

char sensor_left(void)    //left sensor is channel 2
{
  start_conv(2);
  signal_left = readADC(); // from 0 to 255
//  V_left = signal_left * (5/2)/255; // from 0 to 2.5V
  return signal_left;
  
}

char sensor_right(void)   //right sensor is channel 1 
{
  start_conv(1);
  signal_right = readADC(); // from 0 to 255
//  V_right = signal_right * (5/2)/255;// from 0 to 2.5V
  return signal_right;
}