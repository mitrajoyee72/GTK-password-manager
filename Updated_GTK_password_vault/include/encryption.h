#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stddef.h>

// Applies XOR encryption/decryption to a buffer
void xor_buffer(unsigned char *buf, size_t len);

#endif
