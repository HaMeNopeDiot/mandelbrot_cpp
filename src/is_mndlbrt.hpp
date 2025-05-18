#ifndef _IS_MNDLBRT_HPP_
#define _IS_MNDLBRT_HPP_

#include <stdint.h>

class IsMandelbrot {
    public:
        IsMandelbrot() {};

        size_t is_point_in_mandelbrot_set(double x0, double y0, size_t max_posible_iterations);
};

/*!
        \brief Check this point, on which iteration this point can be passed.
        \param[in] x0,y0 The point in frame. Need to set value in real coordinates.
        \param[in] max_possible_iterations The max possible iterations for Mandelbrot.

        \return Iteration number where point is passed. If don't passed, return maximum possible iteration.
*/
size_t IsMandelbrot::is_point_in_mandelbrot_set(double x0, double y0, size_t max_posible_iterations)
{
            size_t iteration_mandelbrot = 0;
            double value = x0 * x0 + y0 * y0;
            double x = 0, y = 0;
            double xtemp;

            while((double)value <= 4.0f && iteration_mandelbrot <= max_posible_iterations - 1) {
                    iteration_mandelbrot++;
                    xtemp = (x * x - y * y) + x0;
                    y = (2.0 * x * y) + y0;
                    x = xtemp;
                    value = x * x + y * y;
            }
            return iteration_mandelbrot;
}

#endif // !_IS_MNDLBRT_HPP_