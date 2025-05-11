#ifndef MULTITHREAD_API_HPP
#define MULTITHREAD_API_HPP

#include "mndlbrt_cpu_multithread.hpp"
#include "mndlbrt_color.hpp"

#define INIT_COLOR 0xFFFFFF

class MultithreadApi {
    private:
        MandelbrotBMPMultithreaded *mMndlbrt;


    public:
        MultithreadApi(int height = 1024, int width = 1024) {
            initBmpFile(height, width);
        }


        size_t saveBmpToFile(const char* path)
        {
            size_t result = 0;

            const uint8_t* headerPtr   = mMndlbrt->getHeaderRawData();
            const uint8_t* infoPtr     = mMndlbrt->getInfoRawData();
            const uint8_t* pixelsPtr   = mMndlbrt->getPixelRawData();

            FILE* fd = fopen(path, "wb+");
            try {
                result += fwrite(headerPtr, sizeof(mndlbrt_bmp_header_t), 1, fd);
                result += fwrite(infoPtr, sizeof(mndlbrt_bmp_info_t), 1, fd);
                result += fwrite(pixelsPtr, mMndlbrt->getBMPSize() - mMndlbrt->getBMPOffset(), 1, fd);
                fclose(fd);
            }
            catch (const std::exception& e){
                std::cout << e.what();
                std::cout << "New message just to check up";
            }
            return result;

        }


        void initBmpFile(int height, int width) {
            MandelbrotColor color(INIT_COLOR);

            mMndlbrt = new MandelbrotBMPMultithreaded(height, width, color);
        }


        /// Пока заглушка.
        /// Потом подправлю до более лучшего результата.
        std::vector<MandelbrotColor> getColors() {
            MandelbrotColor color1(0x111140);
            MandelbrotColor color2(0x404080);
            MandelbrotColor color3(0x6060A0);

            std::vector<MandelbrotColor> colors;

            for(size_t i = 0; i < 300; i++) {
                colors.push_back(MandelbrotColor(0x11 + i, 0x11 + i, 0x40 + i));
            }

            return colors;
        }


        int8_t genBmp(std::vector<MandelbrotColor> colors,
                      size_t maxPossibleIteration,
                      size_t xCenter, size_t yCenter,
                      double scale = 1.0f) {
            int8_t status = mMndlbrt->doMandelbrot(colors,
                                                   maxPossibleIteration,
                                                   xCenter, yCenter, scale);
            return status;
        }
};

#endif // MULTITHREAD_API_HPP
