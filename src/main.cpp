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
    uint8_t color_array[3] = {0x00, 0xAA, 0xAA};
    MandelbrotColor color((uint8_t*)color_array);

    MandelbrotBMP A(1024, 1024, color);
    std::cout << "Hello World Bitchass!" << std::endl;

    save_bmp_to_file(A, "nigger_path.bmp");
    return 0;
}