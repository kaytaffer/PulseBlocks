/* stubs.c
 * This initially file written 2015 by Axel Isaksson
 * This copyright notice added 2015 by F Lundevall

 * For copyright and licensing, see file COPYING 

 * Code functionality written 2022 by V Andersson and K O'Flaherty */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "pulseblockheader.h"

/* Non-Maskable Interrupt; something bad likely happened, so hang */
void _nmi_handler() {
	for(;;);
}

/* This function is called upon reset, before .data and .bss is set up */
void _on_reset() {
	
}

/* This function is called before main() is called, you can do setup here */
void _on_bootstrap() {

    /*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */


		/* Set up SPI (Serial Peripheral Interface) as master */
	SPI2CON = 0;
	SPI2BRG = 4;  //Baud rate generator <2>
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */ //Clock polarity active falling
        SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */ //Master mode enable bit
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;
    
    /* Slut på lånad kod*/




    /* Configuration of initial I/O */


    AD1PCFG = 0xFFFF; //Output pins set to digital

    /* Sets up output LEDs */
    TRISE = TRISE | 0xFF00;           // 1111 1111 XXXX XXXX
    TRISECLR = 0xFF;                    //           0000 0000
    ODCE = 0x0;         //Turns off open drain mode for port E
	PORTE = 0x0;        //turns them all off


    /* Sets up output for OLED display signals */
	TRISFCLR = 0x70; 
	TRISGCLR = 0x200;
    ODCF = 0x0; //Turns off open drain mode for port F
	ODCG = 0x0; //Turns off open drain mode for port G
    PORTF = 0xFFFF;
	PORTG = /* TODO 0x0200; same as shift?*/ (1 << 9);


	/* OLED display initiation */
	initiateDisplay();

    /* Sets up input from switches and buttons */
    TRISD = TRISD | 0x0FE0;          //0000 1111 1110 0000 to set port D (specifically switches) to input
    TRISB = TRISB | 0xFFFF;          // Sets port B to input


    /* Configures initial timers and interrupt*/
	T2CON = 0x0070;       // set prescaler to 256:1
	TMR2 = 0x0;             // Clear timer register	
	PR2 = 0x7A12;   //0x7A12 = 31250 (the period)
    
	IFSCLR(0) = 0xfff; //Clears all interrupt flags
	IPCSET(2)= 0x0c + 0x01; //sets interrupt priority timer2 to 3, subpriority 1
	IPCSET(4)= 0x0c + 0x00; //sets interrupt priority Switches to 3, subpriority 0
	IECSET(0) = 0x00100; // Enable timer interrupts
	IECSET(0) = 0x88880; // Enables switch 4-1 interrupts

    T2CONSET = 0x8000;              //start timer
    	
	enableInterrupt(); //calls enableInterrupt in pulseblocks.S. Enables interrupt flags to trigger custom Interrupt Service Routine

	/*Sets upp game background*/
    gameSetUp();
	
}
