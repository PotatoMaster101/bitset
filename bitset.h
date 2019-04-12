///////////////////////////////////////////////////////////////////////////////
// bitset.h
// Bit set implementation in C99. 
//
// Date:   12/04/2019
// Author: PotatoMaster101
///////////////////////////////////////////////////////////////////////////////

#ifndef BITSET_H
#define BITSET_H
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BITSET_GOOD 0
#define BITSET_NULL_ERR 1
#define BITSET_ALLOC_ERR 2
#define BITSET_LENGTH_ERR 3

// The bitset type. 
typedef struct bitset_t {
    _Bool *bits;    // internal bits
    size_t len;     // length
} bitset;

// Initialises the specified bitset. 
//
// PARAMS: 
// b - the bitset to initialise
// n - the length of the bitset
//
// RET: 
// Zero on success, non-zero on error. 
int bitset_init(bitset *b, size_t n);

// Initialises the specified bitset from a bit string. 
//
// PARAMS: 
// b   - the bitset to initialise
// str - the bit string to initialise
// n   - the length of the bit string
//
// RET: 
// Zero on success, non-zero on error. 
int bitset_init_bstr(bitset *b, const char *str, size_t n);

// Initialises the specified bitset from a string. Each character will take 
// 8 bits. 
//
// PARAMS: 
// b   - the bitset to initialise
// str - the string to initialise
// n   - the length of the string
//
// RET: 
// Zero on success, non-zero on error. 
int bitset_init_str(bitset *b, const char *str, size_t n);

// Returns the number of bits set to 1. 
//
// PARAMS: 
// b - the bitset to check
//
// RET: 
// The number of bits that is set to 1. 
size_t bitset_true_len(const bitset *b);

// Determines whether every bit in the bitset is set to 1. 
//
// PARAMS: 
// b - the bitset to test
//
// RET: 
// True or false depending on whether every bit is set to 1. 
_Bool bitset_all(const bitset *b);

// Determines whether any bit in the bitset is set to 1. 
//
// PARAMS: 
// b - the bitset to test
//
// RET: 
// True or false depending on whether any bit is set to 1. 
_Bool bitset_any(const bitset *b);

// Performs AND operation, storing output in the left operand. 
//
// PARAMS: 
// lhs - the left operand
// rhs - the right operand
//
// RET: 
// Zero on success, non-zero on error. 
int bitset_and(bitset *lhs, const bitset *rhs);

// Performs OR operation, storing output in the left operand. 
//
// PARAMS: 
// lhs - the left operand
// rhs - the right operand
//
// RET: 
// Zero on success, non-zero on error. 
int bitset_or(bitset *lhs, const bitset *rhs);

// Performs XOR operation, storing output in the left operand. 
//
// PARAMS: 
// lhs - the left operand
// rhs - the right operand
//
// RET: 
// Zero on success, non-zero on error. 
int bitset_xor(bitset *lhs, const bitset *rhs);

// Performs NOT operation. 
//
// PARAMS: 
// b - the bitset to perform NOT
//
// RET: 
// Zero on success, non-zero on error. 
int bitset_not(bitset *b);

// Performs left shift. 
//
// PARAMS: 
// b - the bitset to left shift
// n - the number of shifts
//
// RET: 
// Zero on success, non-zero on error. 
int bitset_lsh(bitset *b, size_t n);

// Performs right shift. 
//
// PARAMS: 
// b - the bitset to right shift
// n - the number of shifts
//
// RET: 
// Zero on success, non-zero on error. 
int bitset_rsh(bitset *b, size_t n);

// Performs left rotate. 
//
// PARAMS: 
// b - the bitset to left rotate
// n - the number of shifts
//
// RET: 
// Zero on success, non-zero on error. 
int bitset_lrot(bitset *b, size_t n);

// Performs right rotate. 
//
// PARAMS: 
// b - the bitset to right rotate
// n - the number of shifts
//
// RET: 
// Zero on success, non-zero on error. 
int bitset_rrot(bitset *b, size_t n);

// Resets the bitset, changing all bits to 0. 
//
// PARAMS: 
// b - the bitset to reset
void bitset_reset(bitset *b);

// Frees the internal storage of the given bitset. 
//
// PARAMS: 
// b - the bitset to free
void bitset_free(bitset *b);

#endif

