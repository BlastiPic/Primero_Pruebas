#include "chequeo4x4.h"

unsigned char stecla(void)
{
unsigned char Tecla_Up = 0, Tecla_Low = 0,Tecla_P = 0;
    NOP();
    Tecla_Up = PORTB &= 0b11110000;
    NOP();
    TRISB = 0b00001111;
    NOP();;
    LATB = 0b00001111;
    __delay_ms(2);     // retraso de 1ms para estabilizar el cambio
    Tecla_Low = PORTB &= 0b00001111;
    Tecla_P = Tecla_Up + Tecla_Low;
    switch (Tecla_P)
        {
            case 0b11101110:
                tecla = '1'; 
                break;
            case 0b11101101:
                tecla = '2'; 
                break;
            case 0b11101011:
                tecla = '3'; 
                break;
            case 0b11100111:
                tecla = 'A'; 
                break;
            case 0b11011110:
                tecla = '4';
                break;
            case 0b11011101:
                tecla = '5';
                break;
			case 0b11011011:
                tecla = '6';
                break;
            case 0b11010111:
                tecla = 'B';
                break;
            case 0b10111110:
                tecla = '7'; 
                break;
            case 0b10111101:
                tecla = '8'; 
                break;
            case 0b10111011:
                tecla = '9'; 
                break;
            case 0b10110111:
                tecla = 'C'; 
                break;
            case 0b01111110:
                tecla = '*'; 
                break;
            case 0b01111101:
                tecla = '0'; 
                break;
            case 0b01111011:
                tecla = '#'; 
                break;
            case 0b01110111:
                tecla = 'D'; 
                break;
        }
    TRISB = 0b11110000;     // Rb 7,6,5 entradas el resto salidas
    LATB = 0b11110000;      // Rb 3,2 a 1 el resto a 0
//    while (PORTB != 0b11110000);
    __delay_ms(1);
    return tecla ;
}