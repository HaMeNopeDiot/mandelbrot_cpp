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

        MandelbrotColor(uint8_t* hex_color)
        {
            color.blue  = (uint8_t)hex_color[2];
            color.green = (uint8_t)hex_color[1];
            color.red   = (uint8_t)hex_color[0]; 
        }

        const uint8_t getRed()      const { return color.red;   };
        const uint8_t getBlue()     const { return color.blue;  };
        const uint8_t getGreen()    const { return color.green; };

};

#endif // !_MNDLBRT_COLOR_HPP_
