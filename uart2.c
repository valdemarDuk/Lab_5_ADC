/*
  @File Name
    uart2.c

  @Description
 * This basic code perform all the necessary operation for UART2, including
 * initialization and transmit single character via async serial I/O
 * 
 * Lab 2 - Introduction to UART
 * Advanced Microprocessor Concepts
 * DY Fong
 *  
 * 
 *    Updates: 
 *              Valdemar Duk      -     Added outString() function, enabled 
 *                                      interrupt triggered UART reciever with 
 *                                      extended software FIFO stack.
 */


/**
  Section: Included Files
 */

#include "uart2.h"
#include <xc.h>
#define ISR_NO_PSV __attribute__((__interrupt__, no_auto_psv))
#define LIMIT 16
/*
	Initialize UART2 of PIC24 on Exp16 board
*/


char sFifo[LIMIT];
int head = 0, tail = 0;


 
void ISR_NO_PSV _U2RXInterrupt(void){
    while(!U2STAbits.URXDA);
    checkRxErrorUART2();
    sFifo[head] = U2RXREG;
    if (++head >=LIMIT) head = 0;
    if (head == tail) outString("Error");
    _U2RXIF = 0;
}


void UART2_Initialize(void) 
{
    // Complete the setup and initialization of the following 2 SFRs for UART2
	// Add in neccesary brief comments to explain your settings
    U2MODE = 0x8800;
    
    U2STA = 0x0000;
 
	// Set up your BRG register for Baud Rate = 19200
    U2BRG = 0x33;
    
	// clear transmit buffer 
    U2TXREG = 0x0000;
	// Enable UART2 transmission 
    
            
    U2STAbits.UTXEN = 1;
    _U2RXIF = 0;
    _U2RXIP = 1;
    _U2RXIE = 1;
    
}

/*
	Ouuput a single character (byte) via UART2
*/
void outChar(unsigned char c)
{    while (U2STAbits.UTXBF);
    U2TXREG = c;
    
}

void outString(const char* psz_s) 

{
	// implement function to transmit a string via UART2
    while(*psz_s != '\0'){
        outChar(*psz_s);
        psz_s++;
    }
    //outChar('\n');
    outChar('\r');
}

unsigned int inString(char *psz_buff, unsigned int u16_maxCount) {
    unsigned char u8_c;
    unsigned int u16_i;
    //outString("instring executing");
    if (!u16_maxCount) 
        return 0;

    for (u16_i = 0; u16_i < u16_maxCount; u16_i++) {
        u8_c = inChar();

        if (u8_c == '\n' ||u8_c == '\r' || u8_c == '\0') break; //terminate loop

        *psz_buff = u8_c; //save character
        psz_buff++;
    }
    //stop reading, terminate, return characters read.
    *psz_buff = 0;

    return(u16_i);
}


unsigned char inChar(void)
{
    char c = 'z';
    while(tail == head);
    if (tail != head){
        c = sFifo[tail];
        if (++tail >=LIMIT) tail = 0;
    }
    return c;
    
    
    // Implement return of received data to caller
}

void checkRxErrorUART2(void) 
{
	// Implement error checking on receive buffer overrun
    if (U2STAbits.OERR) 
    {
        //clear error flag
        outString("UART2 receive buffer overrun error\n");
    }
    U2STAbits.OERR = 0;
}

