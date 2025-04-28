#ifndef _MNDLBRT_BMP_HPP_
#define _MNDLBRT_BMP_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <vector>

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

        int8_t doMandelbrot(std::vector<MandelbrotColor> colors, size_t max_possible_iterations, size_t x_center, size_t y_center, double scale = 1.0f);
    
        MandelbrotBMPHeader getHeader() { return header; };
        const size_t getHeight() const { return info.getHeight(); }
        const size_t getWidth()  const { return info.getWidth();  }
        
        const uint8_t* getHeaderRawData() const 
        {
            return reinterpret_cast<const uint8_t*>(&(header.getHeader()));
        }

        const uint8_t* getInfoRawData() const 
        {
            return reinterpret_cast<const uint8_t*>(&(info.getInfo()));
        }

        const uint8_t* getPixelRawData() const 
        {
            return pixels;
        }

        const uint32_t getBMPSize() const 
        {
            return header.getBmpSize();
        }

        const uint32_t getBMPOffset() const 
        {
            return header.getBmpOffset();
        }

        const uint32_t getPixelDataSize() const {
            return header.getBmpSize() - header.getBmpOffset();
        }

        int8_t setPixel(size_t x, size_t y, MandelbrotColor color) 
        {
            if(x < info.getWidth() && y < info.getHeight()) {
                size_t pos = 3 * (x + (info.getHeight() - y - 1) * info.getWidth());
                pixels[pos + 0] = color.getBlue();
                pixels[pos + 1] = color.getGreen();
                pixels[pos + 2] = color.getRed();
                return 0;
            } else {
                return -1;
            }
        }

        MandelbrotColor getPixelColor(size_t x, size_t y) 
        {
            if(x < info.getWidth() && y < info.getHeight()) {
                // get pos in x-y coordinates
                size_t pos = 3 * (x + (info.getHeight() - y - 1) * info.getWidth());
                // take colors
                uint8_t res_array[3] = {pixels[pos + 2], pixels[pos + 1], pixels[pos + 0]};
                // return
                return MandelbrotColor((uint8_t*)res_array);
            } else {
                return MandelbrotColor();
            }
        }

        size_t is_point_in_mandelbrot_set(double x0, double y0, size_t max_posible_iterations)
        {
            size_t iteration_mandelbrot = 0;
            double value = x0 * x0 + y0 * y0;
            double x = 0, y = 0;
            double xtemp;

            while((double)value <= 4.0f && iteration_mandelbrot <= max_posible_iterations - 1) {
                    iteration_mandelbrot++;
                    xtemp = (x * x - y * y) + x0;
                    y = (2.0 * x * y) + y0;
                    x = xtemp;
                    value = x * x + y * y;
            }
            return iteration_mandelbrot;
        }
    private:
        void fillPicture(size_t height, size_t width, MandelbrotColor color = MandelbrotColor());

};              

MandelbrotBMP::MandelbrotBMP(size_t width, size_t height, MandelbrotColor def_color) : header(height, width), info(height, width) 
{
    // Init block of data pixels
    size_t pixels_size = getPixelDataSize();
    pixels = new uint8_t[pixels_size];

    // Set color in each pixel in bmp file.
    fillPicture(height, width, def_color);
}

void MandelbrotBMP::fillPicture (size_t height, size_t width, MandelbrotColor color) 
{
    for(size_t i = 0; i < width; i++) {
        for(size_t j = 0; j < height; j++) {
            setPixel(i, j, color);
        }
    }
}


typedef enum {
    MNDLBRT_OK                  =  0,
    MNDLBRT_COLOR_SIZE_ERR      = -1,
    MNDLBRT_COLOR_VECTOR_ERR    = -2,
    MNDLBRT_COLOR_SET_PIXEL_ERR = -3
} do_mndlbrt_err_e;

int8_t MandelbrotBMP::doMandelbrot(std::vector<MandelbrotColor> colors, size_t max_possible_iterations, size_t x_center, size_t y_center, double scale)
{
    size_t height = getHeight();
    size_t width  = getWidth();

    if(height == 0 || width == 0)
        return MNDLBRT_COLOR_SIZE_ERR;

    if(colors.size() != max_possible_iterations)
        return MNDLBRT_COLOR_VECTOR_ERR;

    
    for(size_t i = 0; i < width; i++) {
        for(size_t j = 0; j < height; j++) {
            double xi, yi;
            double  x,  y;

            xi = (i - (double)x_center);
            yi = (j - (double)y_center);

            x = (double)xi / ((width / 4) * 1.0f);
            y = (double)yi / ((height /  4) * 1.0f);
            
            size_t iteration_mandelbrot = is_point_in_mandelbrot_set(x, y, max_possible_iterations);

            int8_t status = setPixel(i, j, colors[iteration_mandelbrot]);
            if(status != MNDLBRT_OK) {
                return MNDLBRT_COLOR_SET_PIXEL_ERR;
            }
        }
    }
    return MNDLBRT_OK;
}

#endif // !_MNDLBRT_BMP_HPP_
