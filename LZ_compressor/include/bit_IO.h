#ifndef BIT_IO_H
#define BIT_IO_H

#include <vector>
#include <cstdint>

// http://www.avrfreaks.net/forum/tut-c-bit-manipulation-aka-programming-101
#define bit_get(p,m) ((p) & (m))
#define bit_set(p,m) ((p) |= (m))
#define bit_clear(p,m) ((p) &= ~(m))
#define bit_flip(p,m) ((p) ^= (m))
#define bit_write(c,p,m) (c ? bit_set(p,m) : bit_clear(p,m))
#define BIT(x) (0x01 << (x))

std::vector<bool> index2bits (uint16_t index, int index_lenght);
std::vector<bool> char2bits (char c);

#endif // BIT_IO_H