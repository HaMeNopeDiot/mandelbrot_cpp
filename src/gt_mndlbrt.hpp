#ifndef _GT_MNDLBRT_HPP_
#define _GT_MNDLBRT_HPP_

#include "do_mndlbrt.hpp"

class GetMandelbrotPixelData : public DoMandelbrot {
public:
    GetMandelbrotPixelData(size_t width, size_t height, QColor def_color, QObject *parent = nullptr)
        : DoMandelbrot(width, height, def_color, parent) {};


    /*!
    \brief Make frame's pixel data to Mandelbrot

    This method take colors and max_possible_iterations and draw a Mandelbrot. This function can draw on different positions of Mandelbrot and can use scaling.
    \param[in] colors The array of colors, which be use for paint each iteration pixels this colors.
    \param[in] max_possible_iterations The max possible iterations for Mandelbrot. Must be equal size array of colors.
    \param[in] x_center_frame,y_center_frame The center point in frame. Need to set value in screen coordinates.
    \param[in] scale The scale in frame. Values more 1.0 zooms camera

    \return pixel data in QList<QColor>

    \todo Need to change here MandelbrotColor to QColor. Also you can delete max_possible_iterations, because (maybe) QColor can have something like "size" or "length" (but I don't sure).
    */
    const QColor *getMandelbrotPixelData(QList<QColor> colors, size_t max_possible_iterations,
                                          size_t x_center_frame, size_t y_center_frame, double scale)
    {
        do_mndlbrt_err_e status = doMandelbrot(colors, max_possible_iterations, x_center_frame, y_center_frame, scale);
        if(status == MNDLBRT_OK) {
            return getPixelData();
        } else {
            return nullptr;
        }
    }
};


#endif // !_GT_MNDLBRT_HPP_
