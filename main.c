
#include <stdio.h>
#include "uart2.h"
#include "mcc_generated_files/mcc.h"
#include "string.h"
#include "libpic30.h"
#include "adc.h"


/*
                         Main application
 */

#define BUFSIZE 200



char  sz_1[BUFSIZE+1];
/****************************************************************
 * Valdemar Duk
 * swapString() function intakes a given string, and outputs it to a 
 * second string buffer with its halves inverted.
 * 
 * Ex.
 *             "Hello World!"   ->    "World!Hello "
 *               ^*psz_s1^              ^*psz_s2^
 * 
 * 
****************************************************************/


/*
	main
 */
int main(void) {
    
    SYSTEM_Initialize();
    ADC_Initialize();
    UART2_Initialize();
    outString("ADC initalized");
    double voltPot, voltTemp, voltPress;
    unsigned int ADC_codePot, ADC_codeTemp, ADC_codePress;
    _TRISB5 = 1;
    _TRISA7 = 0;
    while (1){
    //outString("loop entered");           //For debugging purposes
        _SAMP = 1;
        __delay32(FCY*0.03); 
        ADC_codePot = ADC1BUF2;
       
        voltPot = ADC1BUF2*(3.3/1024);
        
        ADC_codeTemp = ADC1BUF1;
        voltTemp = ADC1BUF1*(3.3/1024);
        
        ADC_codePress = ADC1BUF0;
        voltPress = ADC1BUF0*(3.3/1024);
        
        if (ADC_codePress >= 0x0200) _LATA7 = 1;
        else _LATA7 = 0;
        
        
        
        sprintf(sz_1, "POT: Voltage: %f V       ADC Code: 0x%04X          TEMP:"
                    " Voltage: %f V       ADC Code: 0x%04X         Temp: %.02f         PRESSURE: Voltage: %f V       ADC Code: 0x%04X           "
                    ,voltPot, ADC_codePot, voltTemp, ADC_codeTemp, (float)(voltTemp-0.5)*100, voltPress, ADC_codePress);
        outString(sz_1);
                          // delay 100 ms (0.1s)
    //outString("loop done");              //For debugging purposes
    }
}
/**
 End of File
 */