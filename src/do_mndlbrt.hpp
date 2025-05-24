#ifndef _DO_MNDLBRT_HPP_
#define _DO_MNDLBRT_HPP_

#include <stdint.h>

#include <QObject>
#include <QList>
#include <QtConcurrentRun>
#include <QThreadPool>
#include <QColor>
#include <QDebug>

#include "is_mndlbrt.hpp"

/*
 * QT MOC doesn't like that both definition and declaration of the functions are in the same file
 * So your hpp style will be utterly butchered by me to a state that works, GLHF
 */

typedef enum {
    MNDLBRT_OK                  =  0,
    MNDLBRT_COLOR_SIZE_ERR      = -1,
    MNDLBRT_COLOR_VECTOR_ERR    = -2,
    MNDLBRT_COLOR_SET_PIXEL_ERR = -3
} do_mndlbrt_err_e;

class DoMandelbrot : public QObject {
    Q_OBJECT

private:
        size_t height;
        size_t width;
        QColor *pixels;

protected:
        IsMandelbrot    isMandelbrot;
public:
    /*!
    \brief Constructor for class.

    This constructor allocates memory for the pixel data, and also fills this pixel data default color.
    \param[in] width Width of the frame.
    \param[in] heigth Height of frame.
    \param[in] def_color Default color.
    */
    explicit DoMandelbrot(size_t _width, size_t _height, const QColor &def_color, QObject *parent = nullptr)
        : QObject{parent}
    {
        width   = _width;
        height  = _height;
        // Init block of data pixels
        size_t pixels_size = getPixelDataSize();
        pixels = new QColor[pixels_size];
        qInfo() << pixels_size << " yeees\n";


        // Set color in each pixel in bmp file.
        for(size_t i = 0; i < width; i++) {
            for(size_t j = 0; j < height; j++) {
                setPixel(i, j, def_color);
            }
        }
    }

    const size_t  getHeight()           const { return height; }
    const size_t  getWidth()            const { return width;  }
    const QColor *getPixelData()        const { return pixels; }
    const size_t  getPixelDataSize()    const { return height * width;} // use this method to determine the returned array length

    /*!
    \brief Set color on pixel.

    Paint pixel to input color.
    \param[in] x,y The point in frame. Need to set value in screen coordinates.

    \todo Need to change here MandelbrotColor to QColor.
    */
    int8_t  setPixel(size_t x, size_t y, const QColor &color)
    {
        if(x < getWidth() && y < getHeight()) {
            size_t pos = (x + (getHeight() - y - 1) * getWidth());
            pixels[pos] = color;
            return 0;
        } else {
            return -1;
        }
    }


    /*!
    \brief Make frame's pixel data to Mandelbrot

    This method take colors and max_possible_iterations and draw a Mandelbrot. This function can draw on different positions of Mandelbrot and can use scaling.
    Blocks until complete
    \param[in] colors The array of colors, which be use for paint each iteration pixels this colors.
    \param[in] max_possible_iterations The max possible iterations for Mandelbrot. Must be equal size array of colors.
    \param[in] x_center_frame,y_center_frame The center point in frame. Need to set value in screen coordinates.
    \param[in] scale The scale in frame. Values more 1.0 zooms camera

    \return final status code of method.

    \todo Need to change here MandelbrotColor to QColor. Also you can delete max_possible_iterations, because (maybe) QColor can have something like "size" or "length" (but I don't sure).
    */
    do_mndlbrt_err_e  doMandelbrot(QList<QColor> colors, size_t max_possible_iterations,
                                   size_t x_center_frame, size_t y_center_frame, double scale)
    {
        size_t height = getHeight();
        size_t width  = getWidth();

        if(height == 0 || width == 0)
            return MNDLBRT_COLOR_SIZE_ERR;

        if(colors.size() != max_possible_iterations)
            return MNDLBRT_COLOR_VECTOR_ERR;

        int max_thread_count = QThreadPool::globalInstance()->maxThreadCount(); // this value is never one

        QList<QFuture<do_mndlbrt_err_e>> futures;
        for (int i = 0; i < max_thread_count; i++) {
            // QtConcurrent requires a static method, a terrible hack that works
            futures.append(QtConcurrent::run(DoMandelbrot::_doMandelbrot, this, colors, max_possible_iterations, x_center_frame,
                                             y_center_frame, scale, max_thread_count, i));
        }

        do_mndlbrt_err_e return_code = MNDLBRT_OK;
        for (const auto &future : futures) {
            do_mndlbrt_err_e result = future.result();
            if (result != MNDLBRT_OK)
                return_code = result; // I need to properly wait for all threads to finish, so im not returning here
        }

        return return_code;
    }

private:
    /*!
    \brief Make frame's pixel data to Mandelbrot

    This method take colors and max_possible_iterations and draw a Mandelbrot. This function can draw on different positions of Mandelbrot and can use scaling.
    The synchronisation is not needed, because this method does not write to the same place in the array accross different threads
    \param[in] self The pointer to an object, that called it
    \param[in] colors The array of colors, which be use for paint each iteration pixels this colors.
    \param[in] max_possible_iterations The max possible iterations for Mandelbrot. Must be equal size array of colors.
    \param[in] x_center_frame,y_center_frame The center point in frame. Need to set value in screen coordinates.
    \param[in] scale The scale in frame. Values more 1.0 zooms camera
    \param[in] line_divisor instructs on the lines this method should draw

    \return final status code of method.

    \todo Need to change here MandelbrotColor to QColor. Also you can delete max_possible_iterations, because (maybe) QColor can have something like "size" or "length" (but I don't sure).

    For the love of god im not solving the optimal box packing problem here, it will take too much time
    Even to find a good enough optimum candidate, drawing by lines is far simpler and dumber
    */
    static do_mndlbrt_err_e  _doMandelbrot(DoMandelbrot *self, QList<QColor> colors, size_t max_possible_iterations,
                                            size_t x_center_frame, size_t y_center_frame, double scale,
                                            size_t line_divisor, size_t line_start)
    {
        size_t height = self->getHeight();
        size_t width  = self->getWidth();

        double x_center = self->getWidth()  / 2.0;
        double y_center = self->getHeight() / 2.0;


        for(size_t i = line_start; i < width; i += line_divisor) {
            for(size_t j = 0; j < height; j++) {
                double x = ((double)(i - x_center)) / (width  /  4.0) / scale;
                double y = ((double)(j - y_center)) / (height /  4.0) / scale;

                double x_offset = (x_center - x_center_frame) / (width  / 4.0);
                double y_offset = (y_center - y_center_frame) / (height / 4.0);

                double x_real = x - x_offset;
                double y_real = y - y_offset;

                int iteration_mandelbrot = self->isMandelbrot.is_point_in_mandelbrot_set(x_real, y_real, max_possible_iterations);

                if (iteration_mandelbrot >= colors.length()) {
                    qFatal() << "Trying to access outside the range of colors: " << iteration_mandelbrot
                             << " and the colors array length is: " << colors.length();
                }
                int8_t status = self->setPixel(i, j, colors[iteration_mandelbrot]);
                if(status != MNDLBRT_OK) {
                    return MNDLBRT_COLOR_SET_PIXEL_ERR;
                }
            }
        }
        return MNDLBRT_OK;
    }
};
#endif // !_DO_MNDLBRT_HPP_
