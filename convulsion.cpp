#include "convulsion.h"



Convulsion::Convulsion(){

}

QImage Convulsion::applySobelKernel(const QImage &image, const int kernel[3][3]){
    const int width = image.width();
    const int height = image.height();
    const int length = width * height;
    const int coreSize = 3;
    const int halfSize = coreSize / 2;
    QRgb* outputX = new QRgb[length];
    int minX = 0;
    int maxX = 0;
    for (int y = 1; y < height - 1; ++y){
        int index = y * width;
        for (int x = 1; x < width - 1; ++x){
            int resultX = 0;
            for (int i = 0, dx = halfSize; i < coreSize; ++i, --dx){
                for(int j = 0, dy = halfSize; j < coreSize; ++j, --dy){
                    int xi = x + dx;
                    int yj = y + dy;
                    QRgb bright = image.pixel(xi, yj);
                    QRgb intensivity = ImageUtil::toGray(bright);
                    resultX += intensivity * kernel[i][j];
                }
            }
            if (resultX > maxX) {
                maxX = resultX;
            }
            if (resultX < minX) {
                minX = resultX;
            }
            outputX[index++] = resultX;
        }
    }
    outputX = normalize(outputX, minX, maxX, length);
    QImage resultImage = ImageUtil::toImage(outputX, width, height);
    delete outputX;
    return resultImage;
}

QImage Convulsion::applySobel(const QImage &image){
    const int width = image.width();
    const int height = image.height();
    const int length = width * height;
    const int coreSize = 3;
    const int halfSize = coreSize / 2;
    const int sobelKernelX[3][3] = {
        {-1,0,1},
        {-2,0,2},
        {-1,0,1}
    };
    const int sobelKernelY[3][3] = {
        {-1,-2,-1},
        {0,0,0},
        {1,2,1}
    };

    QRgb* outputX = new QRgb[length];
    QRgb* outputY = new QRgb[length];
    int minX = 0;
    int maxX = 0;
    int minY = 0;
    int maxY = 0;

    for (int y = 1; y < height - 1; ++y){
        int index = y * width;
        for (int x = 1; x < width - 1; ++x){
            int resultX = 0;
            int resultY = 0;
            for (int i = 0, dx = halfSize; i < coreSize; ++i, --dx){
                for(int j = 0, dy = halfSize; j < coreSize; ++j, --dy){
                    int xi = x + dx;
                    int yj = y + dy;
                    QRgb bright = image.pixel(xi, yj);
                    QRgb intensity = ImageUtil::toGray(bright);
                    resultX += intensity * sobelKernelX[i][j];
                    resultY += intensity * sobelKernelY[i][j];
                }
            }
            if (resultX > maxX) {
                maxX = resultX;
            }
            if (resultY > maxY) {
                maxY = resultY;
            }
            if (resultX < minX) {
                minX = resultX;
            }
            if (resultY < minY) {
                minY = resultY;
            }
            outputX[index] = resultX;
            outputY[index++] = resultY;
        }
    }
    outputX = normalize(outputX, minX, maxX, length);
    outputY = normalize(outputY, minY, maxY, length);
    QRgb * out = new QRgb[length];
    int minXY = 1 << 30;
    int maxXY = 0;
    for (int i = 0; i < length; ++i) {
        int resultX = outputX[i];
        int resultY = outputY[i];
        int result = (int)sqrt(resultX * resultX + resultY * resultY);
        if (result > maxXY){
            maxXY = result;
        }
        if (result < minXY){
            minXY = result;
        }
        out[i] = result;
    }
    delete outputX;
    delete outputY;
    out = normalize(out, minXY, maxXY, length);
    QImage resultImage = ImageUtil::toImage(out, width, height);
    delete out;
    return resultImage;
}

QRgb * Convulsion::normalize(QRgb* bufferInput, int min, int max, int length){
    if(max != MAX_INTENSITY && min != 0){
        int diff = max -  min;
        for (int i = 0; i < length; ++i) {
            double value = bufferInput[i] - min;
            bufferInput[i] = (QRgb) (value / diff * MAX_INTENSITY);
        }
    }
    return bufferInput;
}



