#ifndef _MNDLBRT_BMP_HPP_
#define _MNDLBRT_BMP_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

#include "mndlbrt_bmp_header.hpp"
#include "mndlbrt_bmp_info.hpp"


class MandelbrotBMP {
    private:
        MandelbrotBMPHeader header;
        MandelbrotBMPInfo   info;
        uint8_t*            pixels;
    public:
        MandelbrotBMP(size_t height, size_t width);
        ~MandelbrotBMP();
    
    private:
        void colorPixelData(size_t height, size_t width);
};

MandelbrotBMP::MandelbrotBMP(size_t height, size_t width) : header(height, width), info(height, width) 
{
    // Init block of data pixels
    size_t pixels_size = header.getBmpSize() - header.getBmpOffset();
    pixels = new uint8_t[pixels_size];

    // Set color in each pixel in bmp file.
    colorPixelData(height, width);
}

void MandelbrotBMP::colorPixelData (size_t height, size_t width) 
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
            pixel_data[i][j].red    = 0xAA; // Fixme make a hex color maybe?
            pixel_data[i][j].green  = 0x00; // - Do you think?
            pixel_data[i][j].blue   = 0xAA; // - Yes, I actually think.
        }
    }
    
    // Free after use
    free(pixel_data);
}

MandelbrotBMP::~MandelbrotBMP() {
    free(pixels);
}


#endif // !_MNDLBRT_BMP_HPP_
