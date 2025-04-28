#ifndef _MNDLBRT_COLOR_HPP_
#define _MNDLBRT_COLOR_HPP_

#include "mndlbrt_cfg.hpp"

class MandelbrotColor {
    private:
        mndlbrt_pixel_t color;

    public:
        MandelbrotColor() 
        {
            color.blue  = 0;
            color.green = 0;
            color.red   = 0;
        }

        MandelbrotColor(uint32_t hex_color)
        {
            color.blue   = (uint8_t)(hex_color           % 0x100);
            color.green  = (uint8_t)((hex_color >> 8)    % 0x100);
            color.red    = (uint8_t)((hex_color >> 16)   % 0x100);
        }

        MandelbrotColor(uint8_t* hex_color)
        {
            color.blue   = (uint8_t)hex_color[2];
            color.green  = (uint8_t)hex_color[1];
            color.red    = (uint8_t)hex_color[0]; 
        }

        MandelbrotColor(uint8_t red, uint8_t green, uint8_t blue)
        {
            color.blue   = blue;
            color.green  = green;
            color.red    = red; 
        }

        const uint8_t getRed()      const { return color.red;   };
        const uint8_t getBlue()     const { return color.blue;  };
        const uint8_t getGreen()    const { return color.green; };

        const void print() const { std::cout << "R:" << int(color.red) << " G:" << int(color.green) << " B:" << int(color.blue) << std::endl; }

};

#endif // !_MNDLBRT_COLOR_HPP_
