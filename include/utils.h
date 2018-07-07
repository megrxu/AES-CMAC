#include <cstring>

// Print functions

void print_bytes(unsigned char* buf, const size_t len);
void block_xor(unsigned char* dst, unsigned char* a, unsigned char* b);
void block_leftshift(unsigned char* dst, unsigned char* src);

bool test();