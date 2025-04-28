#ifndef _MNDLBRT_CFG_HPP_
#define _MNDLBRT_CFG_HPP_

#define BMP_MAGIC 0x4D42U

#define DEFAULT_RES 3780
#define DEFAULT_BBP 24
#define DEFAULT_PLANES 1;

#include <iostream>

#pragma pack(push, 1)
typedef struct {
    uint16_t bmp_type;              //2(4)  bytes
    uint32_t bmp_size;              //4     bytes
    uint16_t bmp_reserved[2];       //4     bytes
    uint32_t bmp_offset;            //4     bytes
} mndlbrt_bmp_header_t;

typedef struct {
    uint32_t info_header_size;      //4 bytes
    int32_t width;                  //4 bytes
    int32_t height;                 //4 bytes
    uint16_t planes;                //2 bytes
    uint16_t bits_per_pixel;        //2 bytes
    uint32_t compression_method;    //4 bytes
    uint32_t image_size;            //4 bytes
    int32_t h_res;                  //4 bytes
    int32_t v_res;                  //4 bytes
    uint32_t num_colors;            //4 bytes
    uint32_t num_imp_colors;        //4 bytes
} mndlbrt_bmp_info_t;

typedef struct {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} mndlbrt_pixel_t;

typedef struct {
    mndlbrt_bmp_header_t    header;
    mndlbrt_bmp_info_t      info;
    uint8_t*                pixels;
} mndlbrt_bmp_file_t;
#pragma pack(pop)

#endif // !_MNDLBRT_CFG_HPP_