#ifndef _MNDLBRT_BMP_HPP_
#define _MNDLBRT_BMP_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

#include "mndlbrt_bmp_header.hpp"
#include "mndlbrt_bmp_info.hpp"
#include "mndlbrt_color.hpp"

class MandelbrotBMP {
    private:
        MandelbrotBMPHeader header;
        MandelbrotBMPInfo   info;
        uint8_t*            pixels;
    public:
        MandelbrotBMP(size_t width, size_t height, MandelbrotColor def_color);
    
        MandelbrotBMPHeader getHeader() { return header; };
        
        const uint8_t* getHeaderRawData() const {
            return reinterpret_cast<const uint8_t*>(&(header.getHeader()));
        }

        const uint8_t* getInfoRawData() const {
            return reinterpret_cast<const uint8_t*>(&(info.getInfo()));
        }

        const uint8_t* getPixelRawData() const {
            return pixels;
        }

        const uint32_t getBMPSize() const {
            return header.getBmpSize();
        }

        const uint32_t getBMPOffset() const {
            return header.getBmpOffset();
        }

        int8_t setPixel(size_t x, size_t y, MandelbrotColor color) {
            if(x < info.getWidth() && y < info.getHeight()) {
                pixels[3 * (x + y * info.getWidth()) + 0] = color.getBlue();
                pixels[3 * (x + y * info.getWidth()) + 1] = color.getGreen();
                pixels[3 * (x + y * info.getWidth()) + 2] = color.getRed();
                return 0;
            } else {
                // Some error
                return -1;
            }
        }

    private:
        void colorPixelData(size_t height, size_t width, MandelbrotColor color = MandelbrotColor());

};

MandelbrotBMP::MandelbrotBMP(size_t width, size_t height, MandelbrotColor def_color) : header(height, width), info(height, width) 
{
    // Init block of data pixels
    size_t pixels_size = header.getBmpSize() - header.getBmpOffset();
    pixels = new uint8_t[pixels_size];

    // Set color in each pixel in bmp file.
    colorPixelData(height, width, def_color);
}

void MandelbrotBMP::colorPixelData (size_t height, size_t width, MandelbrotColor color) 
{
    // Fill data pixels with current color;
    mndlbrt_pixel_t **pixel_data = new mndlbrt_pixel_t*[height];

    // Set pointer on each pixel.
    for(size_t i = 0; i < height; i++) {
        pixel_data[i] = (mndlbrt_pixel_t*)&(pixels[i * width * 3]);
    }
    
    // Set color
    for(size_t i = 0; i < height; i++) {
        for(size_t j = 0; j < width; j++) {
            setPixel(j, i, color);
            // pixel_data[i][j].red    = color.getRed();   // Fixme make a hex color maybe?
            // pixel_data[i][j].green  = color.getGreen(); // - Do you think?
            // pixel_data[i][j].blue   = color.getBlue();  // - Yes, I actually think.
        }
    }
    
    // Free after use
    free(pixel_data);
}

#endif // !_MNDLBRT_BMP_HPP_
