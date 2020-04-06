#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crc.h"
#include "bitarray.h"

//#define TEST

#define INTERRUPT_PeripheralInterruptEnable() while(0)
#define INTERRUPT_PeripheralInterruptDisable() while(0)

#define kInputFile "generated_packet.csv"

#define kMinSymbolDuration 4
#define kMaxSymbolDuration 6
#define kPreambleCorrelationLen_symbols 20
#define kMinCorrelation (10 * (kPreambleCorrelationLen_symbols * 90 / 100)) // Need at least 90% of bits

// Protocol definitions
#define kMaxPreambleLen_bits 20
#define kLengthLen_bits 4
#define kMaxDataLen_bytes 16 

static BitArray_t sample_buffer_;

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
    int8_t sample = -1;
    rewind(stream);
    while (fgets(line, 64, stream)){
        last_edge_time_us = edge_time_us;
        edge_time_us = (uint32_t)(atof(getfield(line, 1)) * (double)(1e6));
        if(time_us < edge_time_us) {
    		sample = atoi(getfield(line, 2));
        	break;
        }
    }
    return sample;
}

uint16_t CheckPreambleCorrelation(BitArray_t *p_samples, uint8_t *p_duration, uint8_t *p_phase){
    // Find symbol phase offset and duration that maximizes correlation with header
    uint16_t best_correlation, correlation = 0;
    uint8_t expected_symbol  = 0;
    for (uint8_t duration = kMinSymbolDuration; duration <= kMaxSymbolDuration; duration++) { // Symbol duration within valid range
        for (uint8_t phase = 0; phase < kMaxSymbolDuration; phase++) { // phase offsets from 0 up to 2 expected symbol periods
            correlation = 0;
            expected_symbol = 0;
            bit_t sample;
            for (uint8_t symbol_cnt = 0; symbol_cnt < kPreambleCorrelationLen_symbols; symbol_cnt++) {
                // Cycle through sample array, using current offset and duration
                for (uint8_t i=0; i < duration; i++) {
                    BitArrayPeek(p_samples, &sample, phase+i+(duration*symbol_cnt));
                    if(sample == expected_symbol) {
                        correlation++;
                    }
                }
                // Switch symbols (header is alternating 01010101 because of manchester encoding)
                expected_symbol = (expected_symbol + 1) % 2; // TODO - make this actually pull from the header definition
            }
            // Normalize to current duration, but multiply by 10 to minimize quantization error.
            // This is so that we don't award better correlation to longer symbols.
            correlation =  (10 * correlation) / duration;

            // If correlation is best yet, update best phase and offsets:
            if (correlation > best_correlation) {
                best_correlation = correlation;
                *p_phase = phase;
                *p_duration = duration;
            }
        }
    }
    return best_correlation;
}

uint8_t ManchesterDecodeBitFromSamples(BitArray_t *p_samples, uint8_t duration) {
    uint8_t symbols[2] = {0};
    bit_t sample;
    for (int i=0; i<2; i++){
        for (int j=0; j<duration; j++){
            BitArrayPop(p_samples, &sample);
            symbols[i] += sample;
        }
    }
    // If symbols are more than half 1, make symbol=1.
    symbols[0] = (symbols[0] > duration/2) ? 1 : 0;
    symbols[1] = (symbols[1] > duration/2) ? 1 : 0;

    // Decode manchester encoding (1 = 0->1 transition, 0 = 1->0 transition)
    if(symbols[0] < symbols[1]) {
        return 1;
    } else if (symbols[0] > symbols[1]) {
        return 0;
    } else {
        printf("Error decoding manchester, received sequence %d%d\r\n", symbols[0], symbols[1]);
        return 0;
    }
}

void debug_dump_buffer(void){
    uint8_t sample;
    printf("sample buffer:\r\n");
    for (int i=0; i<BitArraySize(&sample_buffer_); i++){
        BitArrayPeek(&sample_buffer_, &sample, i);
        printf("%d", sample);
    }
    printf("\r\n");
}

void DoRfReceive(void){
    static enum {kSync, kFinishPreamble, kLength, kData} state = kSync;
    static uint8_t duration, phase;
    static uint8_t statebits_received;
    static uint8_t packet_len_bytes;
    static uint8_t message_buffer[kMaxDataLen_bytes+1] = {0}; // complete data packet + CRC byte
    bit_t sample;
    uint16_t correlation;
    uint8_t bit;

    switch (state){
        case kSync:
            // Detect phase and duration of the received signal clock
            // Wait for a rising edge
            BitArrayPeek(&sample_buffer_, &sample, 0);
            while (sample == 0)
                BitArrayPop(&sample_buffer_, &sample); 
            // Wait until we have at least a worst-case preamble's worth of samples
            if(BitArraySize(&sample_buffer_) > kPreambleCorrelationLen_symbols * kMaxSymbolDuration*2) {
                // Find best correlation for the samples we've received
                correlation = CheckPreambleCorrelation(&sample_buffer_, &duration, &phase);
                printf("correlation: %d\r\n", correlation);
                // See if it's good enough to treat as a real packet
                if (correlation > kMinCorrelation) {
                    printf("Found preamble with phase %d and duration %d\r\n",phase, duration);

                    // Determine how many samples we need to advance to align sample buffer to signal phase
                    printf("Align by receiving %d more samples\r\n", phase);
                    for (int i=0; i< phase; i++){
                        BitArrayPop(&sample_buffer_, &sample);
                    }
                    statebits_received = 0; // Initialize bit counter for preamble reception
                    state = kFinishPreamble;
                } else {
                    // Correlation not good enough, drop edge and try again
                    BitArrayPop(&sample_buffer_, &sample); 
                }
            }
            break;
        case kFinishPreamble:
            // Keep checking for start bit (manchester encoded 0), up to maximum length of preamble
            if(BitArraySize(&sample_buffer_) > duration*2){
                bit = ManchesterDecodeBitFromSamples(&sample_buffer_, duration);
                if (bit == 0){
                    printf("Found start bit after %d preamble bits\r\n", statebits_received);
                    statebits_received = 0;
                    state = kLength;
                }
                if (++statebits_received > kMaxPreambleLen_bits) {
                    printf("Error - received too many preamble bits (received %d), discarding packet\r\n",
                        statebits_received);
                    state = kSync;
                }
                // TODO Periodically re-sync on edges? Depending on how well aligned we are this might not be necessary. Might also accidentally sync to noise.
            }
            break;
        case kLength:
            // Receive length byte
            if (BitArraySize(&sample_buffer_) > duration*2*kLengthLen_bits) {
                packet_len_bytes = 0;
                for (int i=0; i<kLengthLen_bits; i++){
                    bit = ManchesterDecodeBitFromSamples(&sample_buffer_, duration);
                    packet_len_bytes = (packet_len_bytes<<1) + bit;
                }
                printf("Detected packet length %d\r\n", packet_len_bytes);
                statebits_received = 0;
                memset(message_buffer, 0, sizeof(message_buffer));
                state = kData;
            }
            break;
        case kData:
            // Read in data bytes
            if(BitArraySize(&sample_buffer_) > duration*2){
                bit = ManchesterDecodeBitFromSamples(&sample_buffer_, duration);
                uint8_t curr_byte = packet_len_bytes - (statebits_received/8);
                uint8_t curr_bit = 7-(statebits_received % 8);
                message_buffer[curr_byte] += bit<<(curr_bit);
                statebits_received++;
                if(statebits_received == packet_len_bytes*8 + 8){
                    printf("Packet: 0x");
                    for (int i=packet_len_bytes; i>=0; i--){
                        printf("%X", message_buffer[i]);
                    }
                    printf("\r\n");
                    uint8_t calc_crc = crc_init();
                    for (int i=kMaxDataLen_bytes; i>=1; i--){
                        calc_crc = crc_update(calc_crc, &message_buffer[i], 1);
                    }
                    calc_crc = crc_finalize(calc_crc);
                    printf("Caclulated CRC = 0x%X\r\n", calc_crc);                    
                    printf("Received CRC = 0x%X\r\n", message_buffer[0]);

                    if (calc_crc == message_buffer[0]){
                        printf("Received valid packet\r\n");
                    }
                    state = kSync;
                }
            }
            break;
    }
}

int main (void){
	FILE* stream = fopen(kInputFile, "r");
	uint32_t time_us = 0;
	int8_t sample = 0;

	#ifdef TEST
	TestBitArray();
	#endif
	
	while (sample != -1){
		// Get sample from CSV file at sample rate
        sample = test_sample_rf(time_us, stream);
		time_us += 10; // increment by 10us sample interval

        // Put sample into buffer (ISR would normally do this)
        BitArrayPush(&sample_buffer_, sample);

		DoRfReceive();
	}
	fclose(stream);
}

