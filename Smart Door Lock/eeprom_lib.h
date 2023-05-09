

#ifndef EEPROM_LIB_H
#define	EEPROM_LIB_H
#include "config.h"



void EEPROM_write(unsigned char data, char address);
char EEPROM_read(char address);

#endif	/* EEPROM_LIB_H */

