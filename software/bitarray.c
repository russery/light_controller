#include <stdlib.h>
#include "bitarray.h"

#ifdef TEST
#include <assert.h>
#include <string.h>
#include <stdio.h>
#endif

BitArrayLen_t wrap(BitArrayLen_t ind) {
	return ind & (kBitArrayLen - 1);
}

BitErrCode_t BitArrayPush(BitArray_t* a_p, bit_t b) {
	if(BitArrayIsFull(a_p)){
		return kErrFull;
	}
	BitArrayLen_t ind = wrap(a_p->write++);
	if(b) {
		a_p->buff[ind/8] |= 1 << (ind%8); // Don't have to modify write pointer as it'll just rollover eventually
	} else {
		a_p->buff[ind/8] &= ~(1 << (ind%8));
	}

	return kErrOk;
}

BitErrCode_t BitArrayPop(BitArray_t* a_p, bit_t* b_p) {
	BitErrCode_t ret = BitArrayPeek(a_p, b_p);
	if(ret == kErrOk) {
		a_p->read++;	
	} else {
		return ret;
	}
	return kErrOk;
}

BitErrCode_t BitArrayPeek(BitArray_t* a_p, bit_t* b_p){
	if(BitArrayIsEmpty(a_p)){
		return kErrEmpty;
	}
	BitArrayLen_t ind = wrap(a_p->read);
	*b_p = ((a_p->buff[ind/8] & (1 << (ind%8) )) != 0 );
	return kErrOk;
}

bool BitArrayIsEmpty(BitArray_t* a_p) {
	return a_p->read == a_p->write;
}

bool BitArrayIsFull(BitArray_t* a_p) {
	return BitArraySize(a_p) == kBitArrayLen-1;
}

BitArrayLen_t BitArraySize(BitArray_t* a_p) {
	return a_p->write - a_p->read;
}

#ifdef TEST
void TestBitArray(void) {
	BitArray_t ba = {0};
	BitErrCode_t ret;

	printf("**** Testing Pushing to Full Array ****\r\n");
	for(BitArrayLen_t i=0; i<kBitArrayLen-1; i++) {
		ret = BitArrayPush(&ba, (bit_t)1);
		assert(ret == kErrOk);
	}
	ret = BitArrayPush(&ba, (bit_t)1);
	assert(ret == kErrFull);


	printf("**** Testing Reading from Empty Array ****\r\n");
	bit_t b = 0;
	for(BitArrayLen_t i=0; i<kBitArrayLen-1; i++) {
		ret = BitArrayPop(&ba, &b);	
		assert(ret == kErrOk);
		assert(b == 1);
		b = 0;
	}
	ret = BitArrayPop(&ba, &b);
	assert(ret == kErrEmpty);

	printf("**** Testing Array Wraparound Write and Read ****\r\n");
	memset(&ba, 0, sizeof(ba)); // Reset struct
	bit_t b_set, b_read1, b_read2, b_read3;
	b_set = 0;
	b_read3 = 1;
	for(int i=0; i<100; i++){ // Loop through at least this many times length of buffer.
		for(BitArrayLen_t j=0; j<kBitArrayLen-1; j++) {
			ret = BitArrayPush(&ba, b_set);
			assert(ret == kErrOk);
	
			ret = BitArrayPeek(&ba, &b_read1);
			assert(ret == kErrOk);
			BitArrayPop(&ba, &b_read2);
			assert(ret == kErrOk);

			assert(b_set == b_read2); // Set and read values are the same.
			assert(b_read1 == b_read2); // Peeked and popped values are the same.
			assert(b_read3 != b_read2); // Previous value is opposite of current value.

			b_set = !b_set;
			b_read3 = b_read2;
		}
	}

	printf("Done Testing\r\n");
}
#endif // TEST
