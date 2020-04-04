#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitarray.h"

#define kBspLoopDuration_us 1

#define kInputFile "generated_packet.csv"
#define kSampleTime_us 10
#define kMinBitDuration_us 40
#define kMaxBitDuration_us 60
#define kPreambleCorrelationLen 6


// Bit buffer:
static BitArray_t ReceiveBits;


const char* getfield(char* line, int num){
    const char* tok;
    char* tmp = strdup(line);
    for (tok = strtok(tmp, ",");
            tok && *tok;
            tok = strtok(NULL, ",\n")){
        if (!--num) {
        	free(tmp);
            return tok;
        }
    }
    free(tmp);
    return NULL;
}

int8_t test_sample_rf(uint32_t time_us, FILE* stream){
	char line[64];
    uint32_t edge_time_us, last_edge_time_us = 0;
    int8_t bit = -1;
    rewind(stream);
    while (fgets(line, 64, stream)){
        last_edge_time_us = edge_time_us;
        edge_time_us = (uint32_t)(atof(getfield(line, 1)) * (double)(1e6));
        if(time_us < edge_time_us) {
    		bit = atoi(getfield(line, 2));
        	break;
        }
    }
    printf("Edge Time: %d   Bit:  %d\n", last_edge_time_us, bit);
    return bit;
}

uint8_t CheckBitCorrelation(BitArray_t *p_bits, uint8_t *p_offset, uint8_t *p_phase){
    // Find bit phase offset and duration that maximizes correlation with header
    uint8_t best_offset, best_phase, best_correlation
    uint8_t expected_bit, correlation = 0;
    for (uint8_t offset = 0; offset < 2*kMaxBitDuration_us; offset++) { // Offsets from 0 up to 2 bit periods
        for (uint8_t duration = kMinBitDuration_us/kBspLoopDuration_us;
            duration < kMaxBitDuration_us/kBspLoopDuration_us;
            duration++) { // Bit duration within valid range
            correlation = 0;
            expected_bit = 0;
            for (uint8_t bit_cnt = 0; bit_cnt < kPreambleCorrelationLen; bit_cnt++) {
                

                // If correlation is best yet, update best phase and offsets:
                if (correlation > best_correlation) {
                    best_offset = offset;
                    best_phase = phase;
                }
            }
        }
    }
}

// if sb.is_full(): 
            // # Find bit offset and duration that maximizes correlation with [1,0]
            // bit_correlation = 0
            // bit_offset = 0
            // bit_dur = 1
            // for o in range(0,(int(kMaxBitDuration_us/kLoopDuration_us)*2)+1): # Offsets from 0 up to two bit periods
            //     for d in range(int(kMinBitDuration_us/kLoopDuration_us), int(kMaxBitDuration_us/kLoopDuration_us)+1): # Allow durations within valid range
            //         correlation = 0
            //         for b in range(0,kPreambleCorrelationLen):
            //             correlation += CheckBitCorrelation(sb.vals[o+(d*b):o+(d*(b+1))], (b+1)%2)
            //         #print('Correlation {} for offset {} and duration {}'.format(correlation, o, d))
            //         if correlation >= bit_correlation: # Better than last best
            //             bit_correlation = correlation
            //             bit_offset = o
            //             bit_dur = d




// def CheckBitCorrelation(samples, expected_bit):
//     # TODO: find a better correlation algorithm. This rewards longer bits. Normalize to bit duration?
//     c = 0
//     for i in samples:
//         if i == expected_bit:
//             c += 1
//     return c

void DoRfReceive(void){
    static enum {kSync, kAlign, kFinishPreamble, kLength, kData} state_ = kSync;
    uint8_t correlation = 0;

    switch (state_){
        case kSync:
            while ((ReceiveBits.peek()) == 0)
                ReceiveBits.pop() // wait for a rising edge

            if(ReceiveBits.is_full())
                // Find best correlation for the bits we've received
                uint8_t offset, phase;
                correlation = CheckBitCorrelation(&ReceiveBits, &offset, &phase);
            

            // if bit_correlation > (kMinCorrelation * kPreambleCorrelationLen):
            //     print('Found preamble sequence with best offset {} and duration {} and correlation {}'.format(bit_offset, bit_dur, bit_correlation))
            //     samples_remaining_ = bit_dur - ((kMaxSampleCnt - bit_offset) % bit_dur) - 1
            //     sb.flush() # Discard samples in buffer, as we assume we've found a preamble
            //     state_ = 'kAlign'
            // else:
            //     sb.pop() # drop edge and keep trying





            break;
        case kAlign:
            break;
        case kFinishPreamble:
            break;
        case kLength:
            break;
        case kData:
            break;
    }

}

int main (void){
	FILE* stream = fopen(kInputFile, "r");
	uint32_t time_us = 0;
	int8_t bit = 0;

	#ifdef TEST
	TestBitArray();
	#endif

	
	while (bit != -1){
		// Get bit from CSV file at sample rate
        bit = test_sample_rf(time_us, stream);
		printf("Wall Time: %d\r\n", time_us);
		time_us += kSampleTime_us;

        // Put bit into buffer (ISR would normally do this)
        BitArrayPush(&ReceiveBits, bit);

		DoRfReceive();
	}
	
	fclose(stream);
}

