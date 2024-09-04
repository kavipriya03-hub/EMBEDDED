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

#define _XTAL_FREQ 2000000

void  __interrupt()ISR(){
    if(INTF){
        INTF=0;
         Lcd_cmd(0x01);
         Lcd_cmd(0x80);
       Lcd_string("EMERGENCY");
        __delay_ms(1000);
    }
}





void main()
{
  char buffer [16];
    TRISB=0X00;
    TRISD=0X00;
    TRISC=0X00;
    PORTB=0X00;
    PORTD=0X00;
    PORTC=0X00;
     TRISB0=1;
    GIE=1;
    PEIE=1;
    INTE=1;
    Lcd_Init();
    unsigned int temperature,heart,bp;
    unsigned  int a,b,c;;
     init();
      Lcd_cmd(0X80);
     
        Lcd_string("HEALTH  CARE");
         __delay_ms(1000);
    while(1)
    {
       
         a = ADC_read(0);
        temperature = (a * 5.0 / 1023.0) * 100;
           b= ADC_read(1);
        heart = (b * 5.0 / 1023.0) * 100;
          c= ADC_read(2);
        bp = (b * 5.0 / 1023.0) * 100;
       
        sprintf(buffer,"T:%dC",temperature);
         Lcd_cmd(0x01);
        Lcd_cmd(0x80);  // Move cursor to the beginning of the first line
        Lcd_string(buffer);
       
        sprintf(buffer,"HB:%d",heart);
        Lcd_cmd(0x87);  // Move cursor to the beginning of the first line
        Lcd_string(buffer);
       
          sprintf(buffer,"BP:%d",bp);
        Lcd_cmd(0xc0);  // Move cursor to the beginning of the first line
        Lcd_string(buffer);
       
       __delay_ms(1000);
               
       if( temperature>100){
           RB6=1;
           RB7=0;
           Lcd_cmd(0x01);
            Lcd_cmd(0x80);
           Lcd_string("T.HIGH");
           __delay_ms(10);
       }else{
           RB7=1;
           RB6=0;
           Lcd_cmd(0x01);
             Lcd_cmd(0x80);
            Lcd_string("T.LOW");
            __delay_ms(10);
       }
       
        if(( heart>60)&&(heart<=72)){
            Lcd_cmd(0x87);
           Lcd_string("HB.LOW");
           __delay_ms(100);
       }else{
             Lcd_cmd(0x87);
            Lcd_string("HB.HIGH");
            __delay_ms(100);
       }
       
     if(( bp>80)&&(bp<=100)){
            Lcd_cmd(0xC0);
           Lcd_string("BP.LOW");
           __delay_ms(1000);
       }else{
             Lcd_cmd(0xC0);
            Lcd_string("BP.HIGH");
            __delay_ms(1000);
       }
       
    }
}
