#ifndef MANDELBROT_CPU_MULTITHREAD_HPP
#define MANDELBROT_CPU_MULTITHREAD_HPP

#include <QObject>
#include <QThread>

#include "mndlbrt_color.hpp"
#include "mndlbrt_bmp.hpp"

class MandelbrotWorker : public QThread {
    Q_OBJECT

private:
    MandelbrotBMP *bmp;
    size_t line_mod;
    size_t workers_count;
    size_t x_center;
    size_t y_center;
    size_t max_possible_iterations;
    std::vector<MandelbrotColor> *colors;
    double scale;

public:
    void setParameters(MandelbrotBMP *pbmp, const size_t pline_mod, const size_t pworkers_count,
                              const size_t px_center, const size_t py_center,
                              const size_t pmax_possible_iterations, std::vector<MandelbrotColor> *pcolors,
                              const double pscale) {
        bmp = pbmp;
        line_mod = pline_mod;
        workers_count = pworkers_count;
        x_center = px_center;
        y_center = py_center;
        max_possible_iterations = pmax_possible_iterations;
        colors = pcolors;
        scale = pscale;
    }

public slots:
    // i copied the code provided by Danila, and just changed it to work in the multithreaded environment
    void run() override {
        size_t height = bmp->getHeight();
        size_t width  = bmp->getWidth();

        for (size_t line = line_mod; line < width; line += workers_count) {
            for (size_t column = 0; column < height; column++) {
                double xi, yi;
                double x, y;

                xi = (line - (double)x_center);
                yi = (column - (double)y_center);

                x = (double)xi / ((width / 4) * 1.0f);
                y = (double)yi / ((height /  4) * 1.0f);

                size_t iteration_mandelbrot = bmp->is_point_in_mandelbrot_set(x, y, max_possible_iterations);

                int8_t status = bmp->setPixel(line, column, (*colors)[iteration_mandelbrot]);
                if(status != MNDLBRT_OK) {
                    emit resultReady(MNDLBRT_COLOR_SET_PIXEL_ERR);
                    return;
                }
            }
        }

        emit resultReady(MNDLBRT_OK);
        return;
    }

signals:
    void resultReady(const int8_t &result);
};





class MandelbrotBMPMultithreaded : public MandelbrotBMP {
    Q_OBJECT

private:
    size_t m_worker_threads_count = 1;
    int8_t m_error_code = MNDLBRT_OK;

public:
    MandelbrotBMPMultithreaded(size_t width, size_t height, MandelbrotColor def_color)
        : MandelbrotBMP(width, height, def_color){};

    int8_t doMandelbrot(std::vector<MandelbrotColor> colors, size_t max_possible_iterations,
                        size_t x_center, size_t y_center, double scale = 1.0f) override;

public slots:
    void handleResults(const int8_t &result) {
        if (result != MNDLBRT_OK) {
            m_error_code = result; // whatever the last error code is, we return it
        }
    }
};


inline int8_t MandelbrotBMPMultithreaded::doMandelbrot(std::vector<MandelbrotColor> colors,
                                                       size_t max_possible_iterations, size_t x_center,
                                                       size_t y_center, double scale)
{
    size_t height = getHeight();
    size_t width  = getWidth();
    m_error_code = MNDLBRT_OK;

    if(height == 0 || width == 0)
        return MNDLBRT_COLOR_SIZE_ERR;

    if(colors.size() != max_possible_iterations)
        return MNDLBRT_COLOR_VECTOR_ERR;

    QList<MandelbrotWorker *> workerThreads;
    for (size_t i = 0; i < m_worker_threads_count; i++) {
        MandelbrotWorker *worker = new MandelbrotWorker;
        workerThreads.append(worker);

        connect(worker, &MandelbrotWorker::resultReady, this, &MandelbrotBMPMultithreaded::handleResults);
        connect(worker, &MandelbrotWorker::finished, worker, &QObject::deleteLater);

        worker->setParameters(this, i, m_worker_threads_count, x_center, y_center, max_possible_iterations, &colors, scale);
        worker->start();
    }

    for (int i = 0; i < workerThreads.size(); i++) {
        QThread *currentThread = workerThreads.first();
        currentThread->wait();
        workerThreads.pop_front();
    }

    return m_error_code;
}

#endif // MANDELBROT_CPU_MULTITHREAD_HPP
