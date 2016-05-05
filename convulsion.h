#ifndef CONVULSION_H
#define CONVULSION_H

#include "qimage.h"
#include "kernel.h"
#include "math.h"
#include "imageutil.h"
class Convulsion
{
    public:
        static const int MAX_INTENSITY = 255;
        Convulsion();
        static QImage applySobelKernel(const QImage &image, const int kernel[3][3]);
        static QImage applySobel(const QImage &image);
        static QRgb* normalize(QRgb* bufferInput, int min, int max, int length);
};

#endif // CONVULSION_H
