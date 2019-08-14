#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitarray.h"

#define kInputFile "generated_packet.csv"
#define kSampleTime_us 10

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

void DoRfReceive(void){

}

int main (void){
	FILE* stream = fopen(kInputFile, "r");
	uint32_t time_us = 0;
	int8_t bit = 0;

	#ifdef TEST
	TestBitArray();
	#endif

	/*
	while (bit != -1){
		bit = test_sample_rf(time_us, stream);
		printf("Wall Time: %d\r\n", time_us);
		time_us += kSampleTime_us;

		DoRfReceive();
	}
	*/
	fclose(stream);
}

