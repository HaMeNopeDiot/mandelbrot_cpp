#ifndef _MNDLBRT_BMP_INFO_HPP_
#define _MNDLBRT_BMP_INFO_HPP_

#include <stdint.h>

#include "mndlbrt_cfg.hpp"

class MandelbrotBMPInfo {
    private:
        mndlbrt_bmp_info_t info;

    public:
        MandelbrotBMPInfo(size_t height, size_t width);
};

MandelbrotBMPInfo::MandelbrotBMPInfo(size_t height, size_t width) {
    info.info_header_size = sizeof(mndlbrt_bmp_info_t);
    info.width = width;
    info.height = height;
    info.planes = DEFAULT_PLANES;
    info.bits_per_pixel = DEFAULT_BBP;
    info.compression_method = 0;
    info.image_size = 0;
    info.h_res = DEFAULT_RES;
    info.v_res = DEFAULT_RES;
    info.num_colors = 0;
    info.num_imp_colors = 0;
}

#endif // !_MNDLBRT_BMP_INFO_HPP_