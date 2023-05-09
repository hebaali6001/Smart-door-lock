#include "uart_liberary.h"
#include <string.h>
#include <stdio.h>
#include "lcd.h"

void UART_initi(int BR) {

    SPEN = 1;
    TX9 = 0;
    SYNC = 0;
    BRG16 = 1;
    BRGH = 1;

    //_XTAL_FREQ / 16 * 
    switch (BR) {
        case 300:
        {
            SPBRG = 6665;
            break;
        } 
        case 1200:
        {
            SPBRG = 1665;
            break;
        }
        case 2400:
        {
            SPBRG = 832;
            break;
        }
        case 9600:
        {
            SPBRG = 207;
            break;
        }
        case 19200:
        {
            SPBRG = 103;
            break;
        }
        case 57600:
        {
            SPBRG = 34;
            break;
        }
    }
}

void UART_write_ch(char ch) {
    TXEN = 1;
    while (!TRMT);
    TXREG = ch;

}

void UART_write_str(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        UART_write_ch(str[i]);
        i++;
    }
}

char UART_read_ch(void) {
  
    CREN = 1;
    while (!RCIF);
    return RCREG;

}

void UART_read_str(char str[]) {/////////// s77thaaaa
    int i = 0;
     str[i] = UART_read_ch();
    while (str[i] != '\0') {
        i++;
        str[i] = UART_read_ch();
    }
}

void UART_RCIF_INTERRUPT(void) {
    GIE = 1;
    PEIE = 1;
    IPEN = 0;
    RCIE = 1;
    RCIF = 0;
}

void UART_TXIF_INTERRUPT(void) {
    GIE = 1;
    PEIE = 1;
    IPEN = 0;
    TXIE = 1;
    TXIF = 0;
}