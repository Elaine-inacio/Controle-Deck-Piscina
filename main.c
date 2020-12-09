#include "config.h"  
#include "bits.h"
#include "lcd.h"
#include "pwm.h"
#include "keypad.h"
#include <pic18f4520.h>

#define CLR 0x01

void main(void) {

    //declarando as variaveis
    unsigned int tecla = 16;
    int i;
    char p;
    volatile unsigned char j, k;

    //mensagens que aparecerao no lcd
    char msg1[11] = "Abrir Tudo";
    char msg2[13] = "Abrir Metade";
    char msg3[11] = "Fechar Tudo";
    char msg4[16] = "Fechar Metade";

    lcdInit(); //inicializa lcd
    kpInit(); //inicializa teclado
    pwmInit(); //inicializa a ventoinha


    //configurando entrada e saida dos leds 
    TRISD = 0x00;
    TRISB = 0x00;
    PORTD = 0x00;


    for (;;) {
        kpDebounce();
        if (kpRead() != tecla) {
            tecla = kpRead();



            if (bitTst(tecla, 3)) {//Realiza leitura da tecla 1
                lcdCommand(CLR);
                for (i = 0; i < 11; i++) {
                    lcdData(msg1[i]); //Mostra mensagem no lcd
                }
                for (i = 0; i < 8; i++) {//Liga os respectivos leds
                    bitSet(PORTD, i);
                }

                pwmFrequency(1000); //Supondo que com f=1000 a ventoinha que simboliza o motor ira rodar pra "frente"
                pwmSet(100);

                for (i = 0; i < 3000; i++) {
                    for (j = 0; j < 41; j++) {
                        for (k = 0; k < 3; k++); //Delay de tempo
                    }
                }

                pwmSet(0);
                lcdCommand(CLR);
            }



            if (bitTst(tecla, 7)) {//Realiza leitura da tecla 2
                lcdCommand(CLR);
                for (i = 0; i < 13; i++) {
                    lcdData(msg2[i]);
                }
                PORTD = 0xF0;

                pwmFrequency(1000); //Supondo que com f=1000 ele rode pra "frente"
                pwmSet(100);

                for (i = 0; i < 1500; i++) {
                    for (j = 0; j < 41; j++) {
                        for (k = 0; k < 3; k++); //Delay de tempo
                    }
                }

                pwmSet(0);
                lcdCommand(CLR);
            }


            if (bitTst(tecla, 6)) {//Realiza leitura da tecla 5
                lcdCommand(CLR);
                for (i = 0; i < 11; i++) {
                    lcdData(msg3[i]);
                }
                for (i = 0; i < 8; i++) {
                    bitClr(PORTD, i);

                    pwmFrequency(1500); //Supondo que com f=1500 ele rode pra "tras"
                    pwmSet(100);

                    for (i = 0; i < 3000; i++) {
                        for (j = 0; j < 41; j++) {
                            for (k = 0; k < 3; k++); //Delay de tempo
                        }
                    }

                    pwmSet(0);
                    lcdCommand(CLR);

                }
            }

            if (bitTst(tecla, 2)) {//Realiza leitura da tecla 4
                lcdCommand(CLR);
                for (i = 0; i < 13; i++) {
                    lcdData(msg4[i]);
                }
                for (i = 0; i < 13; i++) {
                    bitSet(PORTD, i);
                }

                pwmFrequency(1500); //Supondo que com f=1500 ele rode pra "tras"
                pwmSet(100);

                for (i = 0; i < 1500; i++) {
                    for (j = 0; j < 41; j++) {
                        for (k = 0; k < 3; k++); //Delay de tempo
                    }
                }

                pwmSet(0);
                lcdCommand(CLR);

            }
        }
    }
}