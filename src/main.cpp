#include <iostream>

#pragma warning (disable : 4996)

#pragma pack(1)

#include "gt_mndlbrt.hpp"

int main() {
    MandelbrotColor color(0xFFFFFF);

    GetMandelbrotPixelData Mndlbrt(1024, 1024, color);    

    std::vector<MandelbrotColor> colors;

    for(size_t i = 0; i < 300; i++) {
        colors.push_back(MandelbrotColor(0x11 + i, 0x11 + i, 0x40 + i));
    } 

    const uint8_t* pixel_data = Mndlbrt.getMandelbrotPixelData(colors, colors.size(), 512, 512, 1.0);

    // std::cout << "N: " << pixel_data;

    return 0;
}