

#ifndef __BITARRAY_H__
#define __BITARRAY_H__

#include <stdbool.h>

#define TEST

#define kBitArrayLen 256 // Must be a power of two because of how read/write index wrapping works


typedef enum {kErrOk=0, kErrFull, kErrEmpty} BitErrCode_t;

typedef uint8_t bit_t;
typedef uint16_t BitArrayLen_t;
typedef struct {
	BitArrayLen_t read;
	BitArrayLen_t write;
	char buff[kBitArrayLen/8];
} BitArray_t;

BitErrCode_t BitArrayPush(BitArray_t* a_p, bit_t b);
BitErrCode_t BitArrayPop(BitArray_t* a_p, bit_t* b_p);
BitErrCode_t BitArrayPeek(BitArray_t* a_p, bit_t* b, uint8_t offset=0);
bool BitArrayIsEmpty(BitArray_t* a_p);
bool BitArrayIsFull(BitArray_t* a_p);
BitArrayLen_t BitArraySize(BitArray_t* a_p);


#ifdef TEST
void TestBitArray(void);
#endif

#endif //__BITARRAY_H__