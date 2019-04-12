///////////////////////////////////////////////////////////////////////////////
// bitset.c
// Bitset implementation in C99. 
//
// Date:   12/04/2019
// Author: PotatoMaster101
///////////////////////////////////////////////////////////////////////////////

#include "bitset.h"
#define CHAR_LEN 8

static _Bool *bits_from_char(unsigned char c);

// Initialises the specified bitset. 
//
// PARAMS: 
// b - the bitset to initialise
// n - the length of the bitset
//
// RET: 
// Zero on success, non-zero on error. 
int bitset_init(bitset *b, size_t n) {
    if (b == NULL || n == 0)
        return BITSET_NULL_ERR;

    int ret = BITSET_GOOD;
    b->len = n;
    b->bits = calloc(n, sizeof(_Bool));
    if (b->bits == NULL)
        ret = BITSET_ALLOC_ERR;
    return ret;
}

// Initialises the specified bitset from a bit string. 
//
// PARAMS: 
// b   - the bitset to initialise
// str - the bit string to initialise
// n   - the length of the bit string
//
// RET: 
// Zero on success, non-zero on error. 
int bitset_init_bstr(bitset *b, const char *str, size_t n) {
    if (b == NULL || str == NULL || n == 0)
        return BITSET_NULL_ERR;

    int ret = BITSET_ALLOC_ERR;
    b->len = n;
    b->bits = calloc(n, sizeof(_Bool));
    if (b->bits != NULL) {
        ret = BITSET_GOOD;
        for (size_t i = 0; i < n && str[i] != '\0'; i++)
            b->bits[i] = (str[i] == '1') ? true : false;
    }
    return ret;
}

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
int bitset_init_str(bitset *b, const char *str, size_t n) {
    if (b == NULL || str == NULL || n == 0)
        return BITSET_NULL_ERR;

    int ret = BITSET_ALLOC_ERR;
    b->len = n * CHAR_LEN;
    b->bits = calloc(b->len, sizeof(_Bool));
    if (b->bits != NULL) {
        ret = BITSET_GOOD;
        for (size_t i = 0; i < n && str[i] != '\0'; i++) {
            _Bool *bin = bits_from_char(str[i]);
            memcpy(b->bits + (i * CHAR_LEN), bin, CHAR_LEN * (sizeof *bin));
        }
    }
    return ret;
}

// Returns the number of bits set to 1. 
//
// PARAMS: 
// b - the bitset to check
//
// RET: 
// The number of bits that is set to 1. 
size_t bitset_true_len(const bitset *b) {
    if (b == NULL || b->bits == NULL)
        return 0;

    size_t ret = 0;
    for (size_t i = 0; i < b->len; i++)
        ret += (b->bits[i]) ? 1 : 0;
    return ret;
}

// Determines whether every bit in the bitset is set to 1. 
//
// PARAMS: 
// b - the bitset to test
//
// RET: 
// True or false depending on whether every bit is set to 1. 
_Bool bitset_all(const bitset *b) {
    if (b == NULL || b->bits == NULL)
        return false;
    
    for (size_t i = 0; i < b->len; i++)
        if (!b->bits[i])
            return false;
    return true;
}

// Determines whether any bit in the bitset is set to 1. 
//
// PARAMS: 
// b - the bitset to test
//
// RET: 
// True or false depending on whether any bit is set to 1. 
_Bool bitset_any(const bitset *b) {
    if (b == NULL || b->bits == NULL)
        return false;

    for (size_t i = 0; i < b->len; i++)
        if (b->bits[i])
            return true;
    return false;
}

// Performs AND operation, storing output in the left operand. 
//
// PARAMS: 
// lhs - the left operand
// rhs - the right operand
//
// RET: 
// Zero on success, non-zero on error. 
int bitset_and(bitset *lhs, const bitset *rhs) {
    if (lhs == NULL || rhs == NULL || lhs->bits == NULL || rhs->bits == NULL)
        return BITSET_NULL_ERR;
    if (lhs->len != rhs->len)
        return BITSET_LENGTH_ERR;

    for (size_t i = 0; i < lhs->len; i++)
        lhs->bits[i] &= rhs->bits[i];
    return BITSET_GOOD;
}

// Performs OR operation, storing output in the left operand. 
//
// PARAMS: 
// lhs - the left operand
// rhs - the right operand
//
// RET: 
// Zero on success, non-zero on error. 
int bitset_or(bitset *lhs, const bitset *rhs) {
    if (lhs == NULL || rhs == NULL || lhs->bits == NULL || rhs->bits == NULL)
        return BITSET_NULL_ERR;
    if (lhs->len != rhs->len)
        return BITSET_LENGTH_ERR;

    for (size_t i = 0; i < lhs->len; i++)
        lhs->bits[i] |= rhs->bits[i];
    return BITSET_GOOD;
}

// Performs XOR operation, storing output in the left operand. 
//
// PARAMS: 
// lhs - the left operand
// rhs - the right operand
//
// RET: 
// Zero on success, non-zero on error. 
int bitset_xor(bitset *lhs, const bitset *rhs) {
    if (lhs == NULL || rhs == NULL || lhs->bits == NULL || rhs->bits == NULL)
        return BITSET_NULL_ERR;
    if (lhs->len != rhs->len)
        return BITSET_LENGTH_ERR;

    for (size_t i = 0; i < lhs->len; i++)
        lhs->bits[i] ^= rhs->bits[i];
    return BITSET_GOOD;
}

// Performs NOT operation. 
//
// PARAMS: 
// b - the bitset to perform NOT
//
// RET: 
// Zero on success, non-zero on error. 
int bitset_not(bitset *b) {
    if (b == NULL || b->bits == NULL)
        return BITSET_NULL_ERR;

    for (size_t i = 0; i < b->len; i++)
        b->bits[i] = (b->bits[i]) ? false : true;
    return BITSET_GOOD;
}

// Performs left shift. 
//
// PARAMS: 
// b - the bitset to left shift
// n - the number of shifts
//
// RET: 
// Zero on success, non-zero on error. 
int bitset_lsh(bitset *b, size_t n) {
    if (b == NULL || b->bits == NULL)
        return BITSET_NULL_ERR;
    if (n == 0)
        return BITSET_GOOD;     // no shifts needed

    if (n >= b->len) {
        memset(b->bits, 0, b->len * sizeof(_Bool));
    } else {
        size_t sh = b->len - n; // shift length
        memmove(b->bits, b->bits + n, sh * sizeof(_Bool));
        memset(b->bits + sh, 0, n * sizeof(_Bool));
    }
    return BITSET_GOOD;
}

// Performs right shift. 
//
// PARAMS: 
// b - the bitset to right shift
// n - the number of shifts
//
// RET: 
// Zero on success, non-zero on error. 
int bitset_rsh(bitset *b, size_t n) {
    if (b == NULL || b->bits == NULL)
        return BITSET_NULL_ERR;
    if (n == 0)
        return BITSET_GOOD;     // no shifts needed

    if (n >= b->len) {
        memset(b->bits, 0, b->len * sizeof(_Bool));
    } else {
        size_t sh = b->len - n; // shift length
        memmove(b->bits + n, b->bits, sh * sizeof(_Bool));
        memset(b->bits, 0, n * sizeof(_Bool));
    }
    return BITSET_GOOD;

}

// Performs left rotate. 
//
// PARAMS: 
// b - the bitset to left rotate
// n - the number of shifts
//
// RET: 
// Zero on success, non-zero on error. 
int bitset_lrot(bitset *b, size_t n) {
    if (b == NULL || b->bits == NULL)
        return BITSET_NULL_ERR;
    if (n % b->len == 0)
        return BITSET_GOOD;     // no need to rotate

    int ret = BITSET_ALLOC_ERR;
    n %= b->len;
    size_t rot = b->len - n;
    _Bool *temp = malloc(n * (sizeof *temp));
    if (temp != NULL) {
        memcpy(temp, b->bits, n * (sizeof *temp));
        memmove(b->bits, b->bits + n, rot * (sizeof *temp));
        memcpy(b->bits + rot, temp, n * (sizeof *temp));
        free(temp);
        ret = BITSET_GOOD;
    }
    return ret;
}

// Performs right rotate. 
//
// PARAMS: 
// b - the bitset to right rotate
// n - the number of shifts
//
// RET: 
// Zero on success, non-zero on error. 
int bitset_rrot(bitset *b, size_t n) {
    if (b == NULL || b->bits == NULL)
        return BITSET_NULL_ERR;
    if (n % b->len == 0)
        return BITSET_GOOD;     // no need to rotate

    int ret = BITSET_ALLOC_ERR;
    n %= b->len;
    size_t rot = b->len - n;
    _Bool *temp = malloc(n * (sizeof *temp));
    if (temp != NULL) {
        memcpy(temp, b->bits + rot, n * (sizeof *temp));
        memmove(b->bits + n, b->bits, rot * (sizeof *temp));
        memcpy(b->bits, temp, n * (sizeof *temp));
        free(temp);
        ret = BITSET_GOOD;
    }
    return ret;
}

// Resets the bitset, changing all bits to 0. 
//
// PARAMS: 
// b - the bitset to reset
void bitset_reset(bitset *b) {
    if (b != NULL && b->bits != NULL)
        for (size_t i = 0; i < b->len; i++)
            b->bits[i] = false;
}

// Frees the internal storage of the given bitset. 
//
// PARAMS: 
// b - the bitset to free
void bitset_free(bitset *b) {
    if (b != NULL) {
        free(b->bits);
        b->bits = NULL;
    }
}

// Returns the bit representation of a character. The length of the bits will 
// be 8. 
//
// PARAMS: 
// c - the character to convert
//
// RET: 
// The bit representation of the character. 
static _Bool *bits_from_char(unsigned char c) {
    static _Bool bits[] = {0, 0, 0, 0, 0, 0, 0, 0};
    memset(bits, 0, CHAR_LEN * (sizeof *bits));

    int b = CHAR_LEN - 1;
    do {
        bits[b--] = (c & 1);
    } while ((c >>= 1) > 0);
    return bits;
}

