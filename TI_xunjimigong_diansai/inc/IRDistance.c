// IRDistance.c
// Runs on MSP432
// Provide mid-level functions that convert raw ADC
// values from the GP2Y0A21YK0F infrared distance sensors to
// distances in mm.
// Jonathan Valvano
// May 25, 2017

/* This example accompanies the books
   "Embedded Systems: Introduction to the MSP432 Microcontroller",
       ISBN: 978-1512185676, Jonathan Valvano, copyright (c) 2017
   "Embedded Systems: Real-Time Interfacing to the MSP432 Microcontroller",
       ISBN: 978-1514676585, Jonathan Valvano, copyright (c) 2017
   "Embedded Systems: Real-Time Operating Systems for ARM Cortex-M Microcontrollers",
       ISBN: 978-1466468863, , Jonathan Valvano, copyright (c) 2017
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/

Simplified BSD License (FreeBSD License)
Copyright (c) 2017, Jonathan Valvano, All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are
those of the authors and should not be interpreted as representing official
policies, either expressed or implied, of the FreeBSD Project.
*/

// Pololu #3543 Vreg (5V regulator output) connected to all three Pololu #136 GP2Y0A21YK0F Vcc's (+5V) and MSP432 +5V (J3.21)
// Pololu #3543 Vreg (5V regulator output) connected to positive side of three 10 uF capacitors physically near the sensors
// Pololu ground connected to all three Pololu #136 GP2Y0A21YK0F grounds and MSP432 ground (J3.22)
// Pololu ground connected to negative side of all three 10 uF capacitors
// MSP432 P9.0 (J5) (analog input to MSP432) connected to right GP2Y0A21YK0F Vout
// MSP432 P4.1 (J1.5) (analog input to MSP432) connected to center GP2Y0A21YK0F Vout
// MSP432 P9.1 (J5) (analog input to MSP432) connected to left GP2Y0A21YK0F Vout

#include <stdint.h>
#include "../inc/ADC14.h"
#include "msp.h"


int32_t LeftConvert(int32_t nl){        // returns left distance in mm
  // write this for Lab 15
  int32_t distance;
  if(nl>=8500 && nl<=8800)
      distance = 50;
  else if(nl>8800 && nl<=11000)
     distance = 100;
  else if(nl>8900 && nl<=10300)
     distance = 150;
  else if(nl>10300 && nl<=11300)
     distance = 150;
  else if(nl>=6400 && nl<=9000)
      distance = 200;
  else if(nl>9000 && nl<=12800)
      distance = 250;
  else if(nl>12800 && nl<=14000)
      distance = 300;
  else if(nl>14000 && nl<=15000)
      distance = 350;
  else if(nl>15000 && nl<=15900)
      distance = 400;
  else if(nl>15900 && nl<=116100)
      distance = 450;
  else
      distance = 0;

  return distance; // replace this line
}

int32_t CenterConvert(int32_t nc){   // returns center distance in mm
  // write this for Lab 15
    int32_t distance;
    if(nc>=8500 && nc<=8800)
        distance = 50;
    else if(nc>=11200 && nc<=11300)
       distance = 150;
    else if(nc>=6400 && nc<=6600)
        distance = 200;
    else if(nc>=900 && nc<=950)
        distance = 250;
    else if(nc>=12900 && nc<=13010)
        distance = 300;
    else if(nc>=14800 && nc<=15000)
        distance = 350;
    else if(nc>=15600 && nc<=15900)
        distance = 400;
    else if(nc>=15901 && nc<=116100)
        distance = 450;
    else
        distance = 0;
  return distance; // replace this line
}

int32_t RightConvert(int32_t nr){      // returns right distance in mm
  // write this for Lab 15
    int32_t distance;
    if(nr>=8500 && nr<=8800)
        distance = 50;
    else if(nr>=11200 && nr<=11300)
       distance = 150;
    else if(nr>=6400 && nr<=6600)
        distance = 200;
    else if(nr>=900 && nr<=950)
        distance = 250;
    else if(nr>=12900 && nr<=13010)
        distance = 300;
    else if(nr>=14800 && nr<=15000)
        distance = 350;
    else if(nr>=15600 && nr<=15900)
        distance = 400;
    else if(nr>=15901 && nr<=116100)
        distance = 450;
    else
        distance = 0;
  return distance; // replace this line
}
