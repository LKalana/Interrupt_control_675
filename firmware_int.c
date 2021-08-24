/*
 * File:   firmware_int.c
 * Author: liyanage kalana perera
 *
 * Created on August 24, 2021, 11:59 AM
 */

// PIC12F675 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
//#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High speed crystal/resonator on GP4/OSC2/CLKOUT and GP5/OSC1/CLKIN)
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = ON          // Code Protection bit (Program Memory code protection is enabled)
#pragma config CPD = ON         // Data Code Protection bit (Data memory code protection is enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 4000000
/*
 * 
 */
void main()
{
// OSCCALbits.CAL = 0xFF;// Set Maximum Oscillator frequency.
 ANSEL = 0x00;
 CMCONbits.CM = 0x07;
 TRISIO = 0x04;
 GPIO = 0x00;
 INTCON = 0x90;
 OPTION_REG = 0x40;
 IOCbits.IOCB2 = 1;// Interrupt change enabled.
 while(1)
   {
 START:    
     GPIObits.GPIO0 = 0;
     GPIObits.GPIO1 = 1;
     __delay_ms(100);
     GPIObits.GPIO1 = 0;
     __delay_ms(100);
   if(GPIObits.GPIO2 == 1 && INTCONbits.GPIF == 0)
   {
       while(GPIObits.GPIO2 == 1)
       {
           GPIObits.GPIO0 = 1;
           GPIObits.GPIO1 = 0;
       }
   }
   if(GPIObits.GPIO2 == 1 && INTCONbits.GPIF == 1)
   {
       INTCONbits.GPIF = 0;
       goto START;
   }
  }
}
