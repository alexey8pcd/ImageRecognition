#ifndef CONVULSION_H
#define CONVULSION_H

#include "qimage.h"
#include "kernel.h"
#include "math.h"
#include "imageutil.h"
class Convolution
{
    public:
        static const int MAX_INTENSITY = 255;
        Convolution();
        static QImage applySobelKernel(const QImage &image, const int kernel[3][3]);
        static QImage applySobel(const QImage &image);
        static QRgb* normalize(QRgb* bufferInput, int min, int max, int length);
        static QRgb* normalizeD(double * bufferInput, double min, double max, int length);
        static QImage applyGauss(const QImage &image, const double sigma);
};

#endif // CONVULSION_H