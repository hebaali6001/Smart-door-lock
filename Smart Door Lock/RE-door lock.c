/* 
 * File:   RE-door lock.c
 * Author: EL-YaMaMa
 *
 * Created on 16 may, 2022, 02:53 am
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"eeprom_lib.h"
#include"lcd.h"
#include"uart_liberary.h"

/*
 * 
 */

char out[16];

void main(void) {

    char x = 0, c = 0;
    char str[5];
    char pass[5];

    OSCCON = 0X76;

    LCD_Initialize();
    UART_initi(9600);

    TRISB0 = 0;
    LATB0 = 0;
    TRISB1 = 0;
    LATB1 = 0;
    TRISB2 = 0;
    LATB2 = 0;

    EEPROM_write('2', 0x01);
    EEPROM_write('3', 0x02);
    EEPROM_write('2', 0x03);
    EEPROM_write('3', 0x04);

    pass[0] = EEPROM_read(0x01);
    pass[1] = EEPROM_read(0x02);
    pass[2] = EEPROM_read(0x03);
    pass[3] = EEPROM_read(0x04);
    pass[4] = 0;

    LCDPutCmd(LCD_CLEAR);
    LCDGoto(3, 0);
    sprintf(out, "hello heba");
    LCDPutStr(out);
    for (int j = 0; j < 30; j++)
        __delay_ms(50);

    while (1) {
start:

        LCDPutCmd(LCD_CLEAR);
        LCDGoto(1, 0);
        sprintf(out, "ENTER PASSWORD");
        LCDPutStr(out);


        for (int i = 0; i < 5; i++) {
            str[i] = UART_read_ch();
            if (str[0] == 's') {

                LCDPutCmd(LCD_CLEAR);
                LCDGoto(0, 0);
                sprintf(out, "change pass    1");
                LCDPutStr(out);

                LCDGoto(0, 1);
                sprintf(out, "return         2");
                LCDPutStr(out);

                str[0] = UART_read_ch();
                if (str[0] == '1') {

                    LCDPutCmd(LCD_CLEAR);
                    LCDGoto(0, 0);
                    sprintf(out, "ENTER OLD PASS");
                    LCDPutStr(out);
                    for (int i = 0; i < 5; i++) {
                        str[i] = UART_read_ch();
                    }
                    str[4] = 0;

                    x = strcmp(str, pass);
                    if (!x) {

                        LCDPutCmd(LCD_CLEAR);
                        LCDGoto(0, 0);
                        sprintf(out, "ENTER NEW PASS");
                        LCDPutStr(out);

                        for (int i = 0; i < 5; i++) {
                            pass[i] = UART_read_ch();
                        }
                        pass[4] = 0;

                        EEPROM_write(pass[0], 0x01);
                        EEPROM_write(pass[1], 0x02);
                        EEPROM_write(pass[2], 0x03);
                        EEPROM_write(pass[3], 0x04);

                        LCDPutCmd(LCD_CLEAR);
                        LCDGoto(6, 0);
                        sprintf(out, "DONE");
                        LCDPutStr(out);
                        for (int j = 0; j < 20; j++)
                            __delay_ms(50);
                        goto start;
                    }else{
                          LCDPutCmd(LCD_CLEAR);
                        LCDGoto(6, 0);
                        sprintf(out, "wrong");
                        LCDPutStr(out);
                        goto start;
                    }
                    
                } else {
                    goto start;
                }
            }
        }
        str[4] = 0;

check:
        x = strcmp(str, pass);
        if (!x) {
            c = 0;
            LCDPutCmd(LCD_CLEAR);
            LCDGoto(2, 0);
            sprintf(out, "welcome,heba");
            LCDPutStr(out);
            LATB2 = 1;
            for (int j = 0; j < 20; j++)
                __delay_ms(50);
            LATB2 = 0;

        } else {
            c++;
            if (c == 3) {
                c = 0;
                LCDPutCmd(LCD_CLEAR);
                LCDGoto(5, 0);
                sprintf(out, "WRONG");
                LCDPutStr(out);
                LATB1 = 1;
                LATB0 = 1;
                for (int j = 0; j < 30; j++)
                    __delay_ms(50);
                LATB1 = 0;
                LATB0 = 0;
                goto start;
            }

            LCDPutCmd(LCD_CLEAR);
            LCDGoto(5, 0);
            sprintf(out, "WRONG");
            LCDPutStr(out);
            LATB1 = 1;
            for (int j = 0; j < 20; j++)
                __delay_ms(50);
            LATB1 = 0;

            LCDPutCmd(LCD_CLEAR);
            LCDGoto(2, 0);
            sprintf(out, "RE_ENTER PASS");
            LCDPutStr(out);

            for (int i = 0; i < 5; i++) {
                str[i] = UART_read_ch();
            }
            str[4] = 0;
            goto check;
        }
    }
}

