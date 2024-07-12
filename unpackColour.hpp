#pragma once
#include <cstdint>

/*
   This function unpacks the individual colour components, including alpha, from a 32-bit unsigned int, then assigns them to seperate variables for future processing.
*/
void unpackColour(const uint32_t &colour, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a)
{
   r = (colour >> 0) & 255;
   // This shifts all bits in colour to the right 0 bits (which does nothing), then the result is combined with 255 using bitwise AND. This makes sure only the lowest 8 bits (red component) are kept and higher order bits are set to 0.
   g = (colour >> 8) & 255;
   // Similar to above, the value is shifted 8 bits to the right. It's ANDed with 255 to isolate the green bits, and assign it to the g variable.
   b = (colour >> 16) & 255;
   a = (colour >> 24) & 255;
}