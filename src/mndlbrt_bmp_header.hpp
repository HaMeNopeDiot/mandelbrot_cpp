#ifndef _MNDLBRT_BMP_HEADER_HPP_
#define _MNDLBRT_BMP_HEADER_HPP_

#include <stdint.h>

#include "mndlbrt_cfg.hpp"

class MandelbrotBMPHeader {
    private:
        mndlbrt_bmp_header_t header;

    public:
        MandelbrotBMPHeader(size_t height, size_t width);

        const mndlbrt_bmp_header_t& getHeader() const { return header; }

        const uint32_t getBmpSize()   const { return header.bmp_size;   }
        const uint32_t getBmpOffset() const { return header.bmp_offset; }
};

MandelbrotBMPHeader::MandelbrotBMPHeader(size_t height, size_t width) {
    header.bmp_type = BMP_MAGIC;
    header.bmp_reserved[0] = 0;
    header.bmp_reserved[1] = 0;
    header.bmp_offset = sizeof(mndlbrt_bmp_header_t) + sizeof(mndlbrt_bmp_info_t);
    header.bmp_size = header.bmp_offset + width * height * DEFAULT_BBP / 8;
}

#endif // _MNDLBRT_BMP_HEADER_HPP_