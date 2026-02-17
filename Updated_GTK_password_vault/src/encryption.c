#include "encryption.h"

#define XOR_KEY 5  // Simple XOR key

// Encrypts/decrypts the buffer in place
void xor_buffer(unsigned char *buf, size_t len) {
    for (size_t i = 0; i < len; i++) {
        buf[i] ^= XOR_KEY;
    }
}
