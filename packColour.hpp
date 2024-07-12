#pragma once
#include <cstdint>

/*
  Packs individual red, green, blue, and alpha components into a 32-bit colour value.
*/
uint32_t packColour(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = 255)
{
   return (a << 24) + (b << 16) + (g << 8) + r;
}