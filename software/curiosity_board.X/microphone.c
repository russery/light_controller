
#include "mcc_generated_files/mcc.h"
#include "bsp.h"
#include "microphone.h"

#define kMicBufferLen 16
struct mic_buffer_{
    uint8_t data_[kMicBufferLen] = 0;
    uint8_t index = 0;
};

void TestMicrophone(void){
    
}