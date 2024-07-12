#pragma once
#include <assert.h>

void drawRectangle(std::vector<uint32_t> &image_par, const size_t imgW, const size_t imgH, const size_t rect_X, const size_t rect_Y, const size_t rect_W, const size_t rect_H, const uint32_t colour)
{
   assert(image_par.size() == imgW * imgH); // This checks if the size of the image data matches the expected size calculated from the image dimensions.
   
   for (size_t i{0}; i < rect_W; i++)
   {
      for (size_t j{0}; j < rect_H; j++)
      {
         size_t cx = rect_X + i; // Calculates the X coordinate of the current pixel in the image by adding the offset of the rectangle to the current loop counter
         size_t cy = rect_Y + j; // Same as above, but for the Y coordinate.

         if (cx >= imgW || cy >= imgH) continue;

         image_par[cx + cy * imgW] = colour;
         // ^ This is the thing that actually draws. It calculates the index of the current pixel in the image data vector. This trick takes advantage of how memory for a 2D image is usually laid out consecutively. 
      }
   }
}