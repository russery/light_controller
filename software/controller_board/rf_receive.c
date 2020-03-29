#include "controller_board.X/mcc_generated_files/mcc.h"
#include "bsp.h"
#include "rf_receive.h"

// Raw bit buffer
uint64_t raw_buffer_ = 0;
uint8_t raw_buffer_tail_ = 0;
#define kBitAverageCnt 5
#define kBitAverageThreshold 3
#define kBitAverageMask 0b11111

#define kMessageLen 13
uint8_t message_buffer[kMessageLen];

#define kPacketLen kMessageLen + 3
#define kDataBufferLen kPacketLen + 4
const uint16_t kPreamblePattern = 0x00AA;
uint8_t data_buffer_[kDataBufferLen];
uint8_t data_buffer_tail_byte_ = 0;
uint8_t data_buffer_tail_bit_ = 0;
uint8_t data_buffer_head_byte_ = 0;


//extern uint8_t BspGetRfPinState(void);
void RfIsr(void);
bool PeekDataBuffer(uint8_t* data_byte, uint8_t offset);
uint8_t DataBufferByteCount(void);
bool PopDataBuffer(uint8_t* data_byte);


bool PeekDataBuffer(uint8_t* data_byte, uint8_t offset){
    offset += data_buffer_head_byte_;
    offset = offset % kDataBufferLen;
    *data_byte = data_buffer_[offset];
    return (data_buffer_head_byte_ == data_buffer_tail_byte_);
}

uint8_t DataBufferByteCount(void){
    return (data_buffer_tail_byte_ + kDataBufferLen - data_buffer_head_byte_) 
            % kDataBufferLen;
}
        
bool PopDataBuffer(uint8_t* data_byte){
    if(PeekDataBuffer(data_byte, 0)) {
        data_buffer_head_byte_++;
        data_buffer_head_byte_ = data_buffer_head_byte_ % kDataBufferLen;
        return true;
    }
    return false;
}


void InitializeRf(void){
    BspSetRFTimerISR(&RfIsr);
}


void DoRfReceive(void){
    enum {
        kSyncToBitstream,
        kCheckSum
    } receive_state = 0;
    // Process raw bits we've received and push into data buffer
    while(raw_buffer_tail_ > kBitAverageCnt) {
        const uint8_t kNumSetBits[32] = {
            0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
            1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5
        };
        // INTERRUPT_PeripheralInterruptDisable(); // Critical section
        uint8_t bits = raw_buffer_ & kBitAverageMask;
        raw_buffer_ = raw_buffer_ >> kBitAverageCnt;
        raw_buffer_tail_ -= kBitAverageCnt;
        // INTERRUPT_PeripheralInterruptEnable(); // Critical section end
        // Average bits and push into data buffer
        data_buffer_[data_buffer_tail_byte_] +=
                kNumSetBits[bits] > kBitAverageThreshold ?
                    1<<data_buffer_tail_bit_ : 0;
        // Increment bit and byte counts on data buffer
        if(++data_buffer_tail_bit_ >= 8){
            data_buffer_tail_bit_ = 0;
            data_buffer_tail_byte_++;
            data_buffer_tail_byte_ = data_buffer_tail_byte_ % kDataBufferLen;
        }
    }
    
    uint32_t buffer_bytes;
    uint16_t check_pattern;
    uint8_t data_offset;
    while(DataBufferByteCount() >= kPacketLen){
        switch(receive_state) {
            case kSyncToBitstream:
                PopDataBuffer((uint8_t*)(&buffer_bytes+2)); // Dequeue the first byte
                PeekDataBuffer((uint8_t*)(&buffer_bytes+1), 1); // Keep the second and third bytes in queue
                PeekDataBuffer((uint8_t*)(&buffer_bytes), 2);
                for(int i=0; i<8; i++){
                    check_pattern = (uint16_t)(buffer_bytes >> (16-i));
                    if(check_pattern == kPreamblePattern) {
                        receive_state = kCheckSum;
                        data_offset = i;
                        break;
                    }                        
                }
                break;
            case kCheckSum:
                // Apply offset to all data in buffer
                // Read data into 
                // Check checksum
                // Process message if true
                break;
        }
    }
}

void RfIsr(void){
    raw_buffer_ = (raw_buffer_ << 1) + BspGetRfPinState();
    raw_buffer_tail_++;
}

const uint8_t kTestSequence[84] = {
    0x1F, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x01, 0xF0, 0x7C, 0x1F, 0x07, 0xC0, 0x00, 0x03, 0xE0, 0x07, 0xC0, 0x00,
    0x7F, 0xE0, 0xF8, 0x00, 0x0F, 0x83, 0xE0, 0xFF, 0xC0, 0x0F, 0xFF, 0xFF,
    0x00, 0x01, 0xF0, 0x03, 0xFF, 0x07, 0xC1, 0xF0, 0x7F, 0xFF, 0xF8, 0x01,
    0xFF, 0x83, 0xFF, 0xFF, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x03,
    0xE0, 0x07, 0xC0, 0x00, 0x7F, 0xE0, 0xF8, 0x00, 0x0F, 0x83, 0xE0, 0xFF,
    0xC0, 0x0F, 0xFF, 0xFF, 0x00, 0x01, 0xF0, 0x03, 0xFF, 0x07, 0xC1, 0xF0,
};
void TestRfReceive(void){
    static enum {
            kBufferTest,
            kTestStateMax,
    } test_state = 0;
    
    int test_byte_counter = 0;
    switch(test_state){
        case kBufferTest:
            INTERRUPT_GlobalInterruptDisable();
            while(test_byte_counter < sizeof(kTestSequence)){
                // Stuff the bit buffer in place of the ISR
                raw_buffer_ = 0;
                for(int i=0; i<sizeof(raw_buffer_); i++){
                    raw_buffer_ += (uint64_t)(kTestSequence[test_byte_counter]) << i*8;
                    test_byte_counter++;
                    raw_buffer_tail_ += 8;
                }
                // Process the bytes
                DoRfReceive();
            }
            uint8_t buff_byte;
            while(PopDataBuffer(&buff_byte)) {
                BspWriteDebugByteAndWait(buff_byte);
            }
            test_state++; 
            INTERRUPT_GlobalInterruptEnable();
            break;
        case kTestStateMax:
            // intentional fallthrough
        default:
            return;
    }
}