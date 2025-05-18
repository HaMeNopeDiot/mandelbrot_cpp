#ifndef _DO_MNDLBRT_HPP_
#define _DO_MNDLBRT_HPP_

#include <stdint.h>
#include <vector>

#include "is_mndlbrt.hpp"
#include "mndlbrt_color.hpp"

typedef enum {
    MNDLBRT_OK                  =  0,
    MNDLBRT_COLOR_SIZE_ERR      = -1,
    MNDLBRT_COLOR_VECTOR_ERR    = -2,
    MNDLBRT_COLOR_SET_PIXEL_ERR = -3
} do_mndlbrt_err_e;

class DoMandelbrot : protected IsMandelbrot {
    private:
        size_t      height;
        size_t      width;
        uint8_t*    pixels;

    public:
        DoMandelbrot(size_t _width, size_t _height, MandelbrotColor def_color);

        const size_t    getHeight()    const { return height; }
        const size_t    getWidth()     const { return width;  }
        const uint8_t*  getPixelData() const { return pixels; }

        int8_t  setPixel(size_t x, size_t y, MandelbrotColor color);
        do_mndlbrt_err_e  doMandelbrot(std::vector<MandelbrotColor> colors, size_t max_possible_iterations, size_t x_center_frame, size_t y_center_frame, double scale);
};


/*!
	\brief Constructor for class.
    
	This constructor allocates memory for the pixel data, and also fills this pixel data default color. 
    \param[in] width Width of the frame.
    \param[in] heigth Height of frame.
    \param[in] def_color Default color.

    \todo Need to change here MandelbrotColor to QColor.
*/
DoMandelbrot::DoMandelbrot(size_t _width, size_t _height, MandelbrotColor def_color)
{
    width   = _width;
    height  = _height;
    // Init block of data pixels
    size_t pixels_size = 3 * width * height;
    pixels = new uint8_t[pixels_size];
    std::cout << pixels_size << " yeees" << std::endl;

    

    // Set color in each pixel in bmp file.
    for(size_t i = 0; i < width; i++) {
        for(size_t j = 0; j < height; j++) {
            setPixel(i, j, def_color);
        }
    }
}


/*!
	\brief Make frame's pixel data to Mandelbrot
    
	This method take colors and max_possible_iterations and draw a Mandelbrot. This function can draw on different positions of Mandelbrot and can use scaling. 
    \param[in] colors The array of colors, which be use for paint each iteration pixels this colors. 
    \param[in] max_possible_iterations The max possible iterations for Mandelbrot. Must be equal size array of colors.
    \param[in] x_center_frame,y_center_frame The center point in frame. Need to set value in screen coordinates.
    \param[in] scale The scale in frame. Values more 1.0 zooms camera

    \return final status code of method.

    \todo Need to change here MandelbrotColor to QColor. Also you can delete max_possible_iterations, because (maybe) QColor can have something like "size" or "length" (but I don't sure).
*/
do_mndlbrt_err_e DoMandelbrot::doMandelbrot(std::vector<MandelbrotColor> colors, size_t max_possible_iterations, size_t x_center_frame, size_t y_center_frame, double scale)
{
    size_t height = getHeight();
    size_t width  = getWidth();

    if(height == 0 || width == 0)
        return MNDLBRT_COLOR_SIZE_ERR;

    if(colors.size() != max_possible_iterations)
        return MNDLBRT_COLOR_VECTOR_ERR;

    double x_center = getWidth()  / 2.0;
    double y_center = getHeight() / 2.0;

    
    for(size_t i = 0; i < width; i++) {
        for(size_t j = 0; j < height; j++) {
            double x = ((double)(i - x_center)) / (width  /  4.0) / scale;
            double y = ((double)(j - y_center)) / (height /  4.0) / scale;

            double x_offset = (x_center - x_center_frame) / (width  / 4.0);
            double y_offset = (y_center - y_center_frame) / (height / 4.0);
            
            double x_real = x - x_offset;
            double y_real = y - y_offset;
            
            size_t iteration_mandelbrot = is_point_in_mandelbrot_set(x_real, y_real, max_possible_iterations);

            int8_t status = setPixel(i, j, colors[iteration_mandelbrot]);
            if(status != MNDLBRT_OK) {
                return MNDLBRT_COLOR_SET_PIXEL_ERR;
            }
        }
    }
    return MNDLBRT_OK;
}

/*!
	\brief Set color on pixel.
    
	Paint pixel to input color.
    \param[in] x,y The point in frame. Need to set value in screen coordinates.

    \todo Need to change here MandelbrotColor to QColor.
*/
int8_t DoMandelbrot::setPixel(size_t x, size_t y, MandelbrotColor color) 
        {
            if(x < getWidth() && y < getHeight()) {
                size_t pos = 3 * (x + (getHeight() - y - 1) * getWidth());
                pixels[pos + 0] = color.getBlue();
                pixels[pos + 1] = color.getGreen();
                pixels[pos + 2] = color.getRed();
                return 0;
            } else {
                return -1;
            }
        }

#endif // !_DO_MNDLBRT_HPP_