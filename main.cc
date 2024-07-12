#include <vector>
#include <cmath>
#include <cassert>
#include <sstream>
#include <iomanip>
#include "packColour.hpp"
#include "dropPPM_Image.hpp"
#include "drawRectangle.hpp"
constexpr float PI{3.14159265358979};

int main()
{
   const size_t winWidth{1024};
   const size_t winHeight{512};
   std::vector<uint32_t> frameBuffer(winWidth * winHeight, packColour(255, 255, 255));
   // Creates a vector to store image data. The first argument makes sure the vecotr has enough elements to store each pixel, the second argument sets the initial value to 255, making the pixels opaque.

   const size_t mapWidth{16};
   const size_t mapHeight{16};
   const char map[] = "0000222222220000"
                      "1              0"
                      "1     411111   0"
                      "1     0        0"
                      "0     0  1110000"
                      "0     3        0"
                      "0   10000      0"
                      "0   0   11100  0"
                      "0   000 0      0"
                      "0   0   1  00000"
                      "0   0   1      0"
                      "2       1      0"
                      "0       0      0"
                      "0 0000000      0"
                      "0              0"
                      "0002222222200000"; // This is our map. We can change the numbers to make different colours

   assert(sizeof(map) == mapWidth * mapHeight + 1); // + 1 since theres a null terminator ;)

   float playerX = 3.450f;
   float playerY = 2.345f;
   float playerA = 1.520f;
   const float FoV = PI / 3.;

   const size_t nColours = 10;
   std::vector<uint32_t> colours(nColours);
   for (size_t i{0}; i < nColours; i++)
   {
      colours[i] = packColour(rand() % 255, rand() % 255, rand() % 255);
   }


   const size_t rectWidth = winWidth / (mapWidth * 2);
   const size_t rectHeight = winHeight / mapHeight;

   for (size_t frame{0}; frame < 360; frame++)
   {
      std::stringstream ss;
      ss << std::setfill('0') << std::setw(5) << frame << ".ppm";
      playerA += 2 * PI / 360;

      frameBuffer = std::vector<uint32_t>(winWidth * winHeight, packColour(255, 255, 255)); // Clears the screen

      for (size_t i{0}; i < mapHeight; i++)
      {
         for (size_t j{0}; j < mapWidth; j++)
         {
            if (map[j + i * mapWidth] == ' ' || map[j + i * mapWidth] == '\t' || map[j + i * mapWidth] == '\n')
               continue; // Skips empty spaces

            size_t rectX = i * rectHeight;
            size_t rectY = j * rectWidth;
            size_t icolour = map[j + i * mapWidth] - '0';
            assert(icolour < nColours);
            drawRectangle(frameBuffer, winWidth, winHeight, rectX, rectY, rectWidth, rectHeight, colours[icolour]);
         }
      }

      for (size_t i{0}; i < winWidth / 2; i++)
      {
         float angle = playerA - FoV / 2 + FoV * i / float(winWidth / 2);

         for (float d{0}; d < 20; d += 0.01f)
         {
            float cX = playerX + d * cos(angle);
            float cY = playerY + d * sin(angle);

            size_t pixelX = cX * rectWidth;
            size_t pixelY = cY * rectHeight;

            frameBuffer[pixelX + pixelY * winWidth] = packColour(160, 160, 160); // Draws visibility cone

            if (map[int(cX) + int(cY) * mapWidth] != ' ')
            {
               size_t icolour = map[int(cX) + int(cY) * mapWidth] - '0';

               assert(icolour < nColours);

               size_t columnHeight = winHeight / d;
               drawRectangle(frameBuffer, winWidth, winHeight, winWidth / 2 + i, winHeight / 2 - columnHeight / 2, 1, columnHeight, colours[icolour]);

               break;
            }
         } 
      }
      dropPPM_Image(ss.str(), frameBuffer, winWidth, winHeight);
   }

   return 0;
}