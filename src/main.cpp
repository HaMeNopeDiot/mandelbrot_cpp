#include <iostream>

#pragma warning (disable : 4996)

#pragma pack(1)

#include "mndlbrt_bmp.hpp"
#include "mndlbrt_color.hpp"

size_t save_bmp_to_file(MandelbrotBMP bmp_obj, const char* path)
{
    size_t result = 0;

    const uint8_t* header_ptr   = bmp_obj.getHeaderRawData();
    const uint8_t* info_ptr     = bmp_obj.getInfoRawData();
    const uint8_t* pixels_ptr   = bmp_obj.getPixelRawData();

    FILE* fd = fopen(path, "wb+");
    if (fd != NULL) {
        result += fwrite(header_ptr, sizeof(mndlbrt_bmp_header_t), 1, fd);
        result += fwrite(info_ptr, sizeof(mndlbrt_bmp_info_t), 1, fd);
        result += fwrite(pixels_ptr, bmp_obj.getBMPSize() - bmp_obj.getBMPOffset(), 1, fd);
    } else {
        fprintf(stderr, "Can't open file for writing\n");
        exit(EIO);
    }
    fclose(fd);
    return result;

}

int main() {
    uint8_t color_array[3] = {0x00, 0xAA, 0x88};
    MandelbrotColor color((uint8_t*)color_array);

    MandelbrotBMP A(1024, 2048, color);
    std::cout << "Done!" << std::endl;

    uint8_t black_array[3] = {0xFF, 0x00, 0x00};
    MandelbrotColor black((uint8_t*)black_array);

    A.setPixel(32, 64, black);
    A.setPixel(0, 0, black);
    A.setPixel(1023, 2047, black);
    A.setPixel(0, 2047, black);
    A.setPixel(1023, 0, black);
    save_bmp_to_file(A, "result.bmp");
    return 0;
}