/**

*/

#include "mcc_generated_files/mcc.h"

#define A DOT, DASH, SPACE
#define B DASH, DOT, DOT, DOT, SPACE
#define C DASH, DOT, DASH, DOT, SPACE
#define D DASH, DOT, DOT, SPACE
#define E DOT, SPACE
#define F DOT, DOT, DASH, DOT, SPACE
#define G DASH, DASH, DOT, SPACE
#define H DOT, DOT, DOT, DOT, SPACE
#define I DOT, DOT, SPACE
#define J DOT, DASH, DASH, DASH, SPACE
#define K DASH, DOT, DASH, SPACE
#define L DOT, DASH, DOT, DOT, SPACE
#define M DASH, DASH, SPACE
#define N DASH, DOT, SPACE
#define O DASH, DASH, DASH, SPACE
#define P DOT, DASH, DASH, DOT, SPACE
#define Q DASH, DASH, DOT, DASH, SPACE
#define R DOT, DASH, DOT, SPACE
#define S DOT, DOT, DOT, SPACE
#define T DASH, SPACE
#define U DOT, DOT, DASH, SPACE
#define V DOT, DOT, DOT, DASH, SPACE
#define W DOT, DASH, DASH, SPACE
#define X DASH, DOT, DOT, DASH, SPACE
#define Y DASH, DOT, DASH, DASH, SPACE
#define Z DASH, DASH, DOT, DOT, SPACE



typedef enum MorseChar {SPACE, DOT, DASH} MorseChar_t;
static const MorseChar_t message[] = {
    H, I, M, E, G, A, N
};
static uint8_t message_len = sizeof(message);

void WaitTimeout(void);

void main(void)
{
    SYSTEM_Initialize();
    while (1)
    {
        /*int i = 0;
        while(i < message_len) {
            switch(message[i]){
                case DOT:
                    OOK_OUT_SetHigh();
                    WaitTimeout();
                    OOK_OUT_SetLow();
                    WaitTimeout();
                    WaitTimeout();
                    break;
                case DASH:
                    OOK_OUT_SetHigh();
                    WaitTimeout();
                    WaitTimeout();
                    OOK_OUT_SetLow();
                    WaitTimeout();
                    break;
                case SPACE:
                    WaitTimeout();
                    WaitTimeout();
                    WaitTimeout();
                    break;
            }
            i++;
        }
        for(i=0; i < 10; i++) {
            WaitTimeout();
        }*/
        
        for(int i=0; i<100; i++){
            OOK_OUT_SetHigh();
            WaitTimeout();
            OOK_OUT_SetLow();
            WaitTimeout();
        }
        for(int i=0; i<100; i++){
            OOK_OUT_SetHigh();
            for(int j=0; j<100; j++)
                WaitTimeout();
            OOK_OUT_SetLow();
            for(int j=0; j<100; j++)
                WaitTimeout();
        }
    }
}

void WaitTimeout(void){
    TMR0_Reload();
    INTCONbits.TMR0IF = 0;
    while(!TMR0_HasOverflowOccured());
}