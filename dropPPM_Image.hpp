#pragma once
#include "unpackColour.hpp"
#include <iostream>
#include <fstream>
#include <cassert>

/*
   This function takes image data in a specific format, validates its size, then saves it as a PPM image with the given filename.
*/


void dropPPM_Image(const std::string filename, const std::vector<uint32_t> &image, const size_t width, const size_t height)
{
   assert(image.size() == width * height);        // Ensure the image size matches the expected size
   std::ofstream ofs(filename, std::ios::binary); // Open the file in binary mode for accurate data transfer

   ofs << "P6\n"
       << width << " " << height << "\n255\n";
   // ^ This writes the header for a PPM image format to the file, "P6" signifies a binary RGB image format.

   for (size_t i{0}; i < height * width; ++i) // This iterates through every pixel in the image
   {
      uint8_t r, g, b, a;
      unpackColour(image[i], r, g, b, a);
      //  This calls the unpackColour function to extract the red, green, blue, and alpha components from a single 32bit value in the image vector
      ofs << static_cast<char>(r) << static_cast<char>(g) << static_cast<char>(b);
   }
   ofs.close(); // Once all image data has been written, the file stream is closed to free up resources
}