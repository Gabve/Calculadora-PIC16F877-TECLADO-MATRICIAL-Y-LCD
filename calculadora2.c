#include <16F877.h>
#FUSES HS,NOWDT
#USE DELAY (CLOCK = 20M)
#DEFINE LCD_DATAPORT GETENV("SFR:PORTD")
#DEFINE LCD_ENABLE_PIN PIN_D0
#DEFINE LCD_RS_PIN PIN_D1
#DEFINE LCD_RW_PIN PIN_D2
#DEFINE USE_PORTB_KBD TRUE
#INCLUDE <LCD.C>
#INCLUDE <kbd4X4_1.C>
#use standard_io(a)
#include <stdlib.h>

VOID main()
{while(1)
{  
CHAR k='0';int ON=0;
kbd_init();
port_b_pullups(true);
k=kbd_getc();
if(k=='*'){ON++;}//encendido


while(ON>0){

{ double resultado=0,resultado2=0;
   int screenclear=0,div=0;
   int operacion=0;
   int a=0;
   
   inicio:
   if(operacion==1){div=1;operacion=0;}
   if (resultado==0){
   lcd_init();
   printf(lcd_putc,"Calculadora PLUS");
   lcd_gotoxy(1,2);
   printf(lcd_putc,"By C&M");}
   else {resultado2=resultado;resultado=0;screenclear=1;}
   char k='0',k2='0',k4='0',k3='0';
   double numero=0,numero1=0;
   int i=0,h=0,c=0,clear=0;
   int16 bug=0;

 
   while (clear==0)//botón clear
{
      k=kbd_getc();
      if(resultado!=0){
      goto inicio;}
  
    if((h==0)&&(k=='C')&&(resultado2==0)&&(operacion!=3))
         {
       lcd_gotoxy(11,2);
         printf(lcd_putc,"-");
         a=1;
         }     
         
         
      //Ingreasar número
      if(((k=='0')||(k=='1')||(k=='2')||(k=='3')||(k=='4')||(k=='5')||(k=='6')||(k=='7')||(k=='8')||(k=='9')||(k=='*')))
      { 
         if((screenclear==1)&&(c==0)){printf(lcd_putc,"\f");screenclear=0;resultado2=0;div=0;}
         if(k=='*'){clear=1;}
      
      if((i==0)&&(k!='0'))
         {
       lcd_gotoxy(15,2);
         printf(lcd_putc,"%c",k);
         h=1;   
       numero=(k-48);}
       
        if((i<4)&&(i>0)){
         numero=0;
         k2=lcd_getc(15,2);
         k3=lcd_getc(14,2);
         k4=lcd_getc(13,2);
         lcd_gotoxy(12,2);
         printf(lcd_putc,"%c%c%c%c",k4,k3,k2,k);
         
        //Cifras del número
         if(i==1){
       numero=((k2-48)*10+(k-48));}
       
         if(i==2){bug=(k3-48);bug=bug*100;     
       numero=(bug+(k2-48)*10+(k-48));}
       
         if(i==3){bug=0;
         bug=(k3-48);bug=bug*100;
       numero=((k4-48)*1000+bug+(k2-48)*10+(k-48));}
       //
       }
     
       if(h==1){i++;}
                             }
                             
                             //operacion
if((((k=='A')||(k=='B')||(k=='C')||(k=='D')||(k=='*'))&&(h==1)&&(c==0))||(((k=='A')||(k=='B')||(k=='C')||(k=='D')||(k=='*'))&&(resultado2!=0)&&(c==0)))
    //h para solo poder operar luego de introducir un primer número, o si resultado>0 se puede operar como ANS
                  {
                 if(resultado2!=0){
                 numero=resultado2;
                 resultado2=0;}
                 if((a==1)&&(k!='C')){numero=numero*-1;a=0;}
                 
               if(k=='*'){clear=1;}//clear
               
               if(div==1){
      if(k=='A'){operacion=1;
               printf(lcd_putc,"\f %4.6f   /",numero);}//division
      if(k=='B'){operacion=2;
               printf(lcd_putc,"\f %4.6f   *",numero);}//multiplicacion
      if(k=='C'){operacion=3;
               printf(lcd_putc,"\f %4.6f   -",numero);}//resta
      if(k=='D'){operacion=4;
               printf(lcd_putc,"\f %4.6f   +",numero);}//suma
      
                  h=0;i=0;c=1;
                  numero1=numero;
                  numero=0;}
                  
                  else{
      if(k=='A'){operacion=1;
               printf(lcd_putc,"\f %4.0f   /",numero);}//division
      if(k=='B'){operacion=2;
               printf(lcd_putc,"\f %4.0f   *",numero);}//multiplicacion
      if(k=='C'){operacion=3;
               printf(lcd_putc,"\f %4.0f   -",numero);}//resta
      if(k=='D'){operacion=4;
               printf(lcd_putc,"\f %4.0f   +",numero);}//suma
      
                  h=0;i=0;c=1;
                  numero1=numero;
                  numero=0;
                  }}
      if((k=='#')&&(h==1)&&(c==1))
      {
         
            if(a==1){numero1=numero1*-1;a=0;}
           if(div==1){
            switch(operacion){
      case 1: 
      resultado=(numero1)/(numero);
         printf(lcd_putc,"\f %.6f/%.0f",numero1,numero);
         lcd_gotoxy(1,2);
         printf(lcd_putc,"%4.6g",resultado);
         break;
       
       case 2: 
      resultado=numero1*numero;
         printf(lcd_putc,"\f %.6f*%.0f",numero1,numero);
         lcd_gotoxy(1,2);
         printf(lcd_putc,"%9.6g",resultado);
         break;
      
       case 3: 
      resultado=numero1-numero;
         printf(lcd_putc,"\f %.6f-%.0f",numero1,numero);
         lcd_gotoxy(1,2);
         printf(lcd_putc," %.6g",resultado);
         break;
      
      case 4: 
      resultado=numero1+numero;
         printf(lcd_putc,"\f %.6f+%.0f",numero1,numero);
         lcd_gotoxy(1,2);
         printf(lcd_putc," %.6g",resultado);
         break;
            }
                  }
            else{
      switch(operacion){
      case 1: 
      resultado=(numero1)/(numero);
         printf(lcd_putc,"\f %.0f/%.0f",numero1,numero);
         lcd_gotoxy(1,2);
         printf(lcd_putc,"%4.6g",resultado);
         break;
       
       case 2: 
      resultado=numero1*numero;
         printf(lcd_putc,"\f %.0f*%.0f",numero1,numero);
         lcd_gotoxy(1,2);
         printf(lcd_putc,"%9.0g",resultado);
         break;
      
       case 3: 
      resultado=numero1-numero;
         printf(lcd_putc,"\f %.0f-%.0f",numero1,numero);
         lcd_gotoxy(1,2);
         printf(lcd_putc," %.0g",resultado);
         break;
      
      case 4: 
      resultado=numero1+numero;
         printf(lcd_putc,"\f %.0f+%.0f",numero1,numero);
         lcd_gotoxy(1,2);
         printf(lcd_putc," %.0g",resultado);
         break;
      }
            }}
      } 
}}}}

