/* PIC18 XLCD peripheral routines.
 * VALIDO PARA PIC16   OJO IMPORTANTE COLOCAR MANUALMENTE 
 *                     A 0 LOS REGISTROS ANSELA ANSELB ANSELC
 *   Notes:
 *      - These libraries routines are written to support the
 *        Hitachi HD44780 LCD controller.
 *      - The user must define the following items:
 *          - The LCD interface type (4- or 8-bits)
 *          - If 4-bit mode
 *              - whether using the upper or lower nibble
 *          - The data port
 *              - The tris register for data port
 *              - The control signal ports and pins
 *              - The control signal port tris and pins
 *          - The user must provide three delay routines:
 *              - DelayFor18TCY() provides a 18 Tcy delay
 *              - DelayPORXLCD() provides at least 15ms delay
 *              - DelayXLCD() provides at least 5ms delay
 */

/* Interface type 8-bit or 4-bit
 * For 8-bit operation uncomment the #define BIT8
 */
/* #define BIT8 */

/* When in 4-bit interface define if the data is in the upper
 * or lower nibble.  For lower nibble, comment the #define UPPER
 */

#include "mcc.h"

#define UPPER 

/* DATA_PORT defines the port to which the LCD data lines are connected */
#define DATA_PORT      PORTA
#define TRIS_DATA_PORT TRISA

/* CTRL_PORT defines the port where the control lines are connected.
 * These are just samples, change to match your application.
 */
#define RW_PIN   PORTAbits.RA1   /* PORT for RW */
#define TRIS_RW  TRISAbits.TRISA1    /* TRIS for RW */
#define RS_PIN   PORTAbits.RA0   /* PORT for RS */
#define TRIS_RS  TRISAbits.TRISA0    /* TRIS for RS */
#define E_PIN    PORTAbits.RA2   /* PORT for E  */
#define TRIS_E   TRISAbits.TRISA2    /* TRIS for E  */

/* Display ON/OFF Control defines */
#define DON         0b00001111  /* Display on      */
#define DOFF        0b00001011  /* Display off     */
#define CURSOR_ON   0b00001111  /* Cursor on       */
#define CURSOR_OFF  0b00001101  /* Cursor off      */
#define BLINK_ON    0b00001111  /* Cursor Blink    */
#define BLINK_OFF   0b00001110  /* Cursor No Blink */
#define	LINEA_1		0b10000000		
#define LINEA_2		0b11000000
#define LINEA_3		0b10010100
#define LINEA_4		0b11010100
#define BORRA		0b00000001
#define BLINK_CURSOR_OFF   0b00001100
/* Cursor or Display Shift defines */
#define SHIFT_CUR_LEFT    0b00010011  /* Cursor shifts to the left   */
#define SHIFT_CUR_RIGHT   0b00010111  /* Cursor shifts to the right  */
#define SHIFT_DISP_LEFT   0b00011011  /* Display shifts to the left  */
#define SHIFT_DISP_RIGHT  0b00011111  /* Display shifts to the right */

/* Function Set defines */
#define FOUR_BIT   0b00101111  /* 4-bit Interface               */
#define EIGHT_BIT  0b00111111  /* 8-bit Interface               */
#define LINE_5X7   0b00110011  /* 5x7 characters, single line   */
#define LINE_5X10  0b00110111  /* 5x10 characters               */
#define LINES_5X7  0b00111011  /* 5x7 characters, multiple line */

#define PARAM_SCLASS auto
#define MEM_MODEL far  /* Change this to near for small memory model */

/* OpenXLCD
 * Configures I/O pins for external LCD
 */
void OpenXLCD(unsigned char lcdtype);

/* SetCGRamAddr
 * Sets the character generator address
 */
void SetCGRamAddr(unsigned char CGaddr);

/* SetDDRamAddr
 * Sets the display data address
 */
void SetDDRamAddr(unsigned char DDaddr);

/* BusyXLCD
 * Returns the busy status of the LCD
 */
unsigned char BusyXLCD(void);

/* ReadAddrXLCD
 * Reads the current address
 */
unsigned char ReadAddrXLCD(void);

/* ReadDataXLCD
 * Reads a byte of data
 */
char ReadDataXLCD(void);

/* WriteCmdXLCD
 * Writes a command to the LCD
 */
void WriteCmdXLCD(unsigned char cmd);

/* WriteDataXLCD
 * Writes a data byte to the LCD
 */
void WriteDataXLCD(char data);

/* putcXLCD
 * A putc is a write
 */
#define putcXLCD WriteDataXLCD

/* putsXLCD
 * Writes a string of characters to the LCD
 */
void putsXLCD(char *buffer);

/* putrsXLCD
 * Writes a string of characters in ROM to the LCD
 */


/* User defines these routines according to the oscillator frequency */
void DelayFor18TCY(void);
void DelayPORXLCD(void);
void DelayXLCD(void);