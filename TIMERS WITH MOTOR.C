#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#pragma config FOSC = HS        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 20000000

unsigned int hours0 = 0;
unsigned int minutes0 = 0;
unsigned int seconds0 = 0;
unsigned int hours1 = 0;
unsigned int minutes1 = 0;
unsigned int seconds1 = 0;
unsigned int counter0 = 0;
unsigned int counter1 = 0;
void __interrupt() ISR() {
    if (TMR0IF) { 
      TMR0IF= 0; 
      TMR0=0;
        counter0++;
        if(counter0 >=76 ) {
            counter0 = 0;
            seconds0++;


            if (seconds0 >= 60) {
                seconds0 = 0;
                minutes0++;

                if (minutes0 >= 60) {
                    minutes0 = 0;
                    hours0++;

                    if (hours0 >= 24) {
                        hours0 = 0;
                    }
                }
            }

        }
    }




if (TMR1IF) { 
      TMR1IF= 0; 
      if(seconds0>10){
        counter1++;
        if(counter1 >=9 ) {
            counter1 = 0;
            seconds1++;

            if (seconds1 >= 60) {
                seconds1 = 0;
                minutes1++;

                if (minutes1 >= 60) {
                    minutes1 = 0;
                    hours1++;

                    if (hours1 >= 24) {
                        hours1 = 0;
                    }
                }
            }

        }
    }
}}

void main() {
    char buffer0 [16];
    char buffer1 [16];
    TRISB = 0X00;
    TRISC = 0x00;  
    TRISD = 0x00; 
    PORTB=0X00;
   Lcd_Init();
   OPTION_REG = 0b00000111;

    TMR0IE = 1; 

    GIE=1;
    PEIE=1;
    T1CON=0X31;
    TMR1IF=0;
    TMR1IE=1;

    while (1) {
        Lcd_cmd(0x80); 
        sprintf(buffer0, "T0: %02u:%02u:%02u", hours0, minutes0, seconds0);
        Lcd_string(buffer0);

        Lcd_cmd(0xC0);
        sprintf(buffer1, "T1: %02u:%02u:%02u", hours1, minutes1, seconds1);
        Lcd_string(buffer1);

        if((seconds0>0)&&(seconds0<10)){


           RB0=1;
           RB1=0;

        }
        else if((seconds0>10)&&(seconds0<20)){

           RB0=0;
           RB1=1;

        }
        else{
            RB0=0;
           RB1=0;
        }}}
