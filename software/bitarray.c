#include <stdlib.h>
#include "bitarray.h"

#ifdef TEST
#include <assert.h>
#include <string.h>
#include <stdio.h>
#endif

BitArrayLen_t wrap_(BitArrayLen_t ind) {
	return ind & (kBitArrayLen - 1);
}

BitErrCode_t BitArrayPush(BitArray_t* a_p, bit_t b) {
	if(BitArrayIsFull(a_p)){
		return kErrFull;
	}
	BitArrayLen_t ind = wrap_(a_p->write++);
	if(b) {
		a_p->buff[ind/8] |= 1 << (ind%8); // Don't have to modify write pointer as it'll just rollover eventually
	} else {
		a_p->buff[ind/8] &= ~(1 << (ind%8));
	}

	return kErrOk;
}

BitErrCode_t BitArrayPop(BitArray_t* a_p, bit_t* b_p) {
	BitErrCode_t ret = BitArrayPeek(a_p, b_p, 0);
	if(ret == kErrOk) {
		a_p->read++;	
	} else {
		return ret;
	}
	return kErrOk;
}

BitErrCode_t BitArrayPeek(BitArray_t* a_p, bit_t* b_p, BitArrayLen_t offset){
	if(BitArrayIsEmpty(a_p)){
		return kErrEmpty;
	}
	if(offset >= BitArraySize(a_p)){
		return kErrOutOfRange;
	}
	BitArrayLen_t ind = wrap_(a_p->read + offset);
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
	assert(BitArraySize(&ba)==(kBitArrayLen-1)); // Should be full
	assert(BitArrayIsFull(&ba));
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
	assert(BitArraySize(&ba)==0); // Should be empty
	assert(BitArrayIsEmpty(&ba));
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
	
			assert(BitArraySize(&ba)==1); // Should be exactly one bit in array

			ret = BitArrayPeek(&ba, &b_read1, 0);
			assert(ret == kErrOk);
			BitArrayPop(&ba, &b_read2);
			assert(ret == kErrOk);

			assert(BitArraySize(&ba)==0); // Array should be empty
			assert(BitArrayIsEmpty(&ba));

			assert(b_set == b_read2); // Set and read values are the same.
			assert(b_read1 == b_read2); // Peeked and popped values are the same.
			assert(b_read3 != b_read2); // Previous value is opposite of current value.

			b_set = !b_set;
			b_read3 = b_read2;
		}
	}

	printf("**** Testing Peek in Wraparound Situation ****\r\n");
	// Create a fresh buffer
	BitArray_t ba2 = {0};
	// Write and read zeroes until halfway through buffer
	for(BitArrayLen_t i=0; i<kBitArrayLen/2; i++) {
		ret = BitArrayPush(&ba2, 0);		
		assert(ret == kErrOk);
		assert(BitArraySize(&ba2) == 1);
		ret = BitArrayPop(&ba2, &b_read1);
		assert(ret == kErrOk);
		assert(b_read1 == 0);
		assert(BitArraySize(&ba2) == 0);
	}
	// Now just write, and fill up buffer, causing wraparound, and keeping track of how many bits we wrote
	BitArrayLen_t bits_written = 0;
	while(!BitArrayIsFull(&ba2)) {
		ret = BitArrayPush(&ba2, 1);
		assert(ret == kErrOk);
		bits_written++;
		assert(BitArraySize(&ba2) == bits_written);
	}
	// Peek through all the bits we wrote, and verify they're all ones
	for(BitArrayLen_t i=0; i<bits_written; i++){
		ret = BitArrayPeek(&ba2, &b_read1, i);
		assert(ret == kErrOk);
		assert(b_read1 == 1);
	}
	// Try reading one more, verify it's reported as out-of-range
	ret = BitArrayPeek(&ba2, &b_read1, bits_written);
	assert(ret == kErrOutOfRange);

	printf("Done Testing\r\n");
}
#endif // TEST
