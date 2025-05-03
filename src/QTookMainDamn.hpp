#ifndef QTOOKMAINDAMN_HPP
#define QTOOKMAINDAMN_HPP

#include <iostream>

#pragma warning (disable : 4996)

#pragma pack(1)

#include "mndlbrt_bmp.hpp"
#include "mndlbrt_cpu_multithread.hpp"
#include "mndlbrt_color.hpp"

#include <QObject>

class QTookMainDamn : public QObject{
    Q_OBJECT

public:
    size_t save_bmp_to_file(MandelbrotBMP &bmp_obj, const char* path)
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
        MandelbrotColor color(0xFFFFFF);
        color.print();

        MandelbrotBMPMultithreaded A(1024, 1024, color);

        MandelbrotColor color1(0x111140);
        MandelbrotColor color2(0x404080);
        MandelbrotColor color3(0x6060A0);

        std::vector<MandelbrotColor> colors;

        for(size_t i = 0; i < 300; i++) {
            colors.push_back(MandelbrotColor(0x11 + i, 0x11 + i, 0x40 + i));
        }

        int8_t status = A.doMandelbrot(colors, colors.size(), 1024 / 2.0f, 1024 / 2.0f, 1.00f);

        save_bmp_to_file(A, "result.bmp");
        std::cout << "Done! Status code: " << (int)status << std::endl;
        exit(status);
    };
};

#endif // QTOOKMAINDAMN_HPP
