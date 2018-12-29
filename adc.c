
/*
 *  Valdemar Duk
 * 
 *  This contains the necessary functions to operate the onboard
 *  SAR ADC of the PIC24FJ128GA010.
 * 
 * 
 * 
 */
#include "libpic30.h"
#include "adc.h"

void __attribute__((__interrupt__, no_auto_psv)) _ADC1Interrupt(void){
    IFS0bits.AD1IF = 0;
    _SAMP = 0;
}

void ADC_Initialize(void){
    _TRISB3 = 1;
    _TRISB4 = 1;
    _TRISB5 = 1;
    _VCFG   =   0;          // Set Vref+ to AVdd and Vref- AVss
    _ADCS   =   1;          // Conversion Clock select bit = Tcy
                            // EXPLANATION clk is TCY of 62.5 ns or <75ns
                            // it must exceed 75 ns, therefore the TCY*2 option
                            // is appropriate
    _SSRC   =   0b111;
    _ASAM   =   0;          // auto-sampling off
    _BUFM   =   0;          // 16 Word Buffer
    _CSCNA  =   1;          // scan inputs
    _FORM   =   00;         // Integer form
    _SMPI   =   2;          // interrupt after 3 conversions
    _ALTS   =   0;          // Utilize MUX A & B
    //AD1CHSbits.CH0SA = 5;
    //AD1CHSbits.CH0SB = 4;
    AD1PCFG =   0xFFC7;
    AD1CSSL =   0x0038;     // select channels for scanning
    _ADRC   =   1;          // clock derived for RC Clock
    _SAMC   =   0b11111;    // 31 tad
    _AD1IF  =   0;          // Interrupt flag off
    _AD1IP  =   1;          // Interrupt priority 1
    _AD1IE  =   1;
    _ADON   =   1;          // Enable ADC
}

/*
unsigned int ADC_ReadBuf0(void){
    int buf0, buf1;
    _SAMP = 1;
    if
    buf 0 = ADC1BUF0;
}

unsigned int ADC_ReadBuf1(void){
    _SAMP = 1;
    while(!_DONE);
    _SAMP = 0;
    return ADC1BUF1; 
}
*/
