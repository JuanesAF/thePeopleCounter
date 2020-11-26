/*
/////////////////// DATOS DEL PROGRAMA ////////////////////

//  TTITULO: Contador
//  MICRO:PIC16F15244
//  ESTUDIANTES: Sara Cuy y Juan Acosta
//  Profesor: Harold F MURCIA
//  FECHA: 10 de noviembre de 2020

///////////// CONFIGURACIï¿½N del MCU ////////////////// */

#include <xc.h>

#include <stdint.h>

#include <stdbool.h>

#include <conio.h>

#include <stdlib.h>

#include <stdio.h>

#include "flex_lcd.h"


#pragma config FEXTOSC = OFF // External Oscillator Mode Selection bits->Oscillator not enabled
#pragma config RSTOSC = HFINTOSC_1MHZ // Power-up Default Value for COSC bits->HFINTOSC (1 MHz)
#pragma config CLKOUTEN = OFF // Clock Out Enable bit->CLKOUT function is disabled; I/O function on RA4
#pragma config VDDAR = HI // VDD Range Analog Calibration Selection bit->Internal analog systems are calibrated for operation between VDD = 2.3V - 5.5V

// CONFIG2
#pragma config MCLRE = EXTMCLR // Master Clear Enable bit->If LVP = 0, MCLR pin is MCLR; If LVP = 1, RA3 pin function is MCLR
#pragma config PWRTS = PWRT_OFF // Power-up Timer Selection bits->PWRT is disabled
#pragma config WDTE = OFF // WDT Operating Mode bits->WDT disabled; SEN is ignored
#pragma config BOREN = ON // Brown-out Reset Enable bits->Brown-out Reset Enabled, SBOREN bit is ignored
#pragma config BORV = LO // Brown-out Reset Voltage Selection bit->Brown-out Reset Voltage (VBOR) set to 1.9V
#pragma config PPS1WAY = ON // PPSLOCKED One-Way Set Enable bit->The PPSLOCKED bit can be cleared and set only once in software
#pragma config STVREN = ON // Stack Overflow/Underflow Reset Enable bit->Stack Overflow or Underflow will cause a reset

// CONFIG4
#pragma config BBSIZE = BB512 // Boot Block Size Selection bits->512 words boot block size
#pragma config BBEN = OFF // Boot Block Enable bit->Boot Block is disabled
#pragma config SAFEN = OFF // SAF Enable bit->SAF is disabled
#pragma config WRTAPP = OFF // Application Block Write Protection bit->Application Block is not write-protected
#pragma config WRTB = OFF // Boot Block Write Protection bit->Boot Block is not write-protected
#pragma config WRTC = OFF // Configuration Registers Write Protection bit->Configuration Registers are not write-protected
#pragma config WRTSAF = OFF // Storage Area Flash (SAF) Write Protection bit->SAF is not write-protected
#pragma config LVP = ON // Low Voltage Programming Enable bit->Low Voltage programming enabled. MCLR/Vpp pin function is MCLR. MCLRE Configuration bit is ignored.

// CONFIG5
#pragma config CP = OFF // User Program Flash Memory Code Protection bit->User Program Flash Memory code protection is disabled

///////////// DEFINICIONES  //////////////////

#define _XTAL_FREQ 1000000
#define S1 PORTBbits.RB7 //Sensor 1
#define S2 PORTBbits.RB5 //Sensor 2
#define SW PORTAbits.RA4 //config
#define ACQ_US_DELAY 10

void PIN_MANAGER_Initialize(void) {
  // LATx registers
  LATA = 0x00;
  LATB = 0x00;
  LATC = 0x00;

  // TRISx registers
  TRISA = 0b00010000;
  TRISB = 0b10100000;
  TRISC = 0b00000100;

  // ANSELx registers
  ANSELC = 0;
  ANSELB = 0;
  ANSELA = 0;

  // WPUx registers/
 
  WPUC = 0x04;

  // ODx registers
  ODCONA = 0x04;
  ODCONB = 0x00;
  ODCONC = 0x00;

  // SLRCONx registers
  SLRCONA = 0x37;
  SLRCONB = 0xFF;
  SLRCONC = 0xFF;

  // INLVLx registers
  INLVLA = 0x3F;
  INLVLB = 0xFF;
  INLVLC = 0xFF;

}

//////////////VARIBLES GLOBALES////////////////////
uint8_t contador = 0;
uint8_t maximo = 100;
char s[20];


void menu(void) {
 
  uint24_t variable = 0;
  bool operacion = false;
  int ok = 0;
  while (1) {
    
   //Modo seleccion de operacion
    if (SW == 0) {                // Presiono y espero a que deje de presionar
      __delay_ms(1000); 
      if (SW != 0) { 
        operacion = !operacion;   //cambio la operacion
        
        if (operacion) {          //Segun estado de operacion mostrar en LCD si es suma o resta
          Lcd_Cmd(LCD_CLEAR);
          sprintf(s, "Configuracion");
          Lcd_Out2(1, 0, s);
          sprintf(s, "Operacion: Suma");
          Lcd_Out2(2, 0, s);
        } 
        else {
          Lcd_Cmd(LCD_CLEAR);
          sprintf(s, "Configuracion");
          Lcd_Out2(1, 0, s);
          sprintf(s, "Operacion: Resta");
          Lcd_Out2(2, 0, s);
        }
      }
    }
    //Modo personas
    
    while (SW == 0) {             //Mientras presiono boton
      variable++;
      if (variable == 34723) {    //Durante 5 segundos y activo configuracion
        variable = 0;
        Lcd_Cmd(LCD_CLEAR);       //Mostrar en lcd que debe cambiar el aforo maximo
        sprintf(s, "Establezca el ");
        Lcd_Out2(1, 0, s);
        sprintf(s, "limite de aforo ");
        Lcd_Out2(2, 0, s);
       __delay_ms(2000);          //Delay para alcanzar a dejar de presionar el boton
        
        while (1) {
          
          if (SW == 0) {              // Presiono y espero a que deje de presionar
            __delay_ms(1000); 
            if (SW != 0) { 
              if (operacion == true) { //operacion(true)=suma
                  if(maximo==255){     //Si llego al numero maximo no se le puede sumar más
                      maximo=255;
                  }
                  else{
                      maximo=maximo+10; //Aumentar maximo de a 10
                  }
                
                Lcd_Cmd(LCD_CLEAR);
                sprintf(s, "Configuracion");
                Lcd_Out2(1, 0, s);
                sprintf(s, "Maximo: %d", maximo);
                Lcd_Out2(2, 0, s);
                
              } else {                  //operacion(false)=resta
                if (maximo == 0) {
                  maximo = 0;           //Si es el minimo no se le puede restar mas
                } else {
                  maximo = maximo - 10; //Restar maximo de a 10
                  
                }
               
                Lcd_Cmd(LCD_CLEAR);
                 sprintf(s, "Configuracion");
                Lcd_Out2(1, 0, s);
                sprintf(s, "Maximo: %d", maximo);
                Lcd_Out2(2, 0, s);
              }

            }
          }
          while (SW == 0) {          //Presiono boton y espero 5segundos consecutivos
            variable++;
            if (variable == 44643) {
             variable = 0;
             ok = 1;                 //Variable para salir de los loop
             Lcd_Cmd(LCD_CLEAR);
             break;
            }
          }
          variable=0;
          if (ok == 1) {             //Sale de while
            ok = 2;
            break;
          }
        }
      }
      if (ok == 2) {                 //Sale de while
        ok = 3;
        break;
      }
    }
    variable = 0;
    if (ok == 3) {                   //Sale de while
      ok = 4;
      Lcd_Cmd(LCD_CLEAR);
      sprintf(s, "Modo contador ");  //Vuelve al modo contador
      Lcd_Out2(1, 0, s);
      LATAbits.LATA2 = 1;           //Apaga led porque se cambio el maximo
      __delay_ms(1000);
      break;
     }

  }

}

void main(void) {
  PIN_MANAGER_Initialize();
  LATAbits.LATA2 = 1; // Apaga led porque por defecto está prendido
 
  Lcd_Init();
  Lcd_Cmd(LCD_CLEAR);
  Lcd_Cmd(LCD_CURSOR_OFF);
  int A1, A2, A3, A4 = 0;
  uint24_t aux = 0;

  while (1) {
      //Reset
    if(SW==0){                      // Presiono y espero a que deje de presionar
        __delay_ms(500);
        if (SW!=0){
        contador=0;                 //Reset el valor de contador
        Lcd_Cmd(LCD_CLEAR);
        sprintf(s, "contador %d",contador);
        Lcd_Out2(1, 0, s);
        sprintf(s, "maximo %d",maximo);
        Lcd_Out2(2, 0, s);
        }
    }

    if (contador > maximo) {       //Led indicador de contador con respecto a maximo
      LATAbits.LATA2 = 0;
    }
    else{
       LATAbits.LATA2 = 1; 
    }
    
    while (SW == 0) {            //Presiono durante 3segundos consecutivos
      aux++;
      if (aux == 30000) {
        aux = 0;
        Lcd_Cmd(LCD_CLEAR);
        sprintf(s, "Configuracion");
        Lcd_Out2(1, 0, s);
        __delay_ms(2000);
        menu();
      }    
    }
    aux=0;
    
    //Contador
    //SALIDA
    if (S2 == 0 && A3 == 0 && A4 == 0) {
      A3 = 1;
      A2 = 1;
    }
    if (S1 == 0 && A3 == 1) {
      A4 = 1;
    }
    if (S1 == 1 && S2 == 1 && A3 == 1 && A4 == 1) {
      if (contador == 0) {
        contador = 0;
      }
      else {
         contador--;
      }
      Lcd_Cmd(LCD_CLEAR);
      sprintf(s, "contador   %d", contador);
      Lcd_Out2(1, 0, s);
      sprintf(s, "maximo   %d", maximo);
      Lcd_Out2(2, 0, s);
      
      A3 = 0;
      A4 = 0;
      A2 = 0;
      A1 = 0;
    }
    //Entrada 
    
    if (S1 == 0 && A1 == 0 && A2 == 0) {
      A1 = 1;
      A4 = 1;
    }
    if (S2 == 0 && A1 == 1) {
      A2 = 1;
    }
    if (S1 == 1 && S2 == 1 && A1 == 1 && A2 == 1) {
        if(contador==255){
           contador=255;
        }
        else{
           contador++;
        }

      
      Lcd_Cmd(LCD_CLEAR);
      Lcd_Cmd(LCD_UNDERLINE_ON);
      sprintf(s, "contador    %d", contador);
      Lcd_Out2(1, 0, s);
      sprintf(s, "maximo   %d", maximo);
      Lcd_Out2(2, 0, s);
      
      A1 = 0;
      A2 = 0;
      A4 = 0;
      A3 = 0;
    }

  }
}