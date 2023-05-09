

#include "eeprom_lib.h"

void EEPROM_write(unsigned char data, char address) {

    EEADRH = address >> 8;
    EEADR = address;
    EEDATA = data;
    EEPGD = 0;
    CFGS = 0;
    

    WREN = 1;
    GIE = 0;

    EECON2 = 0X55;
    EECON2 = 0XAA;

   EECON1bits.WR = 1;
   while(EECON1bits.WR);
    GIE = 0;
    WREN = 0;

}

char EEPROM_read(char address) {
   
    EEADRH = address >> 8;
    EEADR = address;
    EEPGD = 0;
    CFGS = 0;
    EECON1bits.RD= 1;
    while(EECON1bits.RD);
    return EEDATA;
}