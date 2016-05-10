#include "kernel.h"

void Kernel::setWidth(int value) {
    this->width = value;
}

void Kernel::setHeight(int value) {
    this->heigth = value;
}

void Kernel::setValues(float *values, int radius) {
    this->values = values;
    this->width = radius;
    this->heigth = radius;
}

int Kernel::getWidth() {
    return width;
}

int Kernel::getHeight() {
    return heigth;
}

float *Kernel::getValues() {
    return values;
}

float Kernel::getValue(int i, int j) {
    return values[i + width * j];
}

Kernel * Kernel::createGaussKernel(double sigma) {
    const double s2 = sigma * sigma * 2;
    const double alpha = 1 / (s2 * 3.141592);
    int radius = (int)(sigma * 3);
    int size = 2 * radius + 1;
    float * values = new float[size * size];
    for(int i = -radius, x = 0; i <= radius; ++i, ++x) {
        for(int j = -radius, y = 0; j <= radius; ++j, ++y) {
            values[x + size * y] = (alpha * exp(-((float)i * i + j * j) / s2));
        }
    }
    return new Kernel(values, size);
}

Kernel *Kernel::createGaussSeparateKernelX(double sigma) {
    const double s2 = sigma * sigma * 2;
    const double alpha = 1 / (sigma * sqrt(3.141592 * 2));
    int halfWidth = (int)(sigma * 3);
    int width = 2 * halfWidth + 1;
    float * values = new float[width];
    for (int i = -halfWidth, x = 0; i <= halfWidth; ++i, ++x) {
        values[x] = (alpha * exp(-(float)i * i / s2));
    }
    return new Kernel(values, width, 1);
}

Kernel* Kernel::createGaussSeparateKernelY(double sigma) {
    Kernel * xKernel = createGaussSeparateKernelX(sigma);
    xKernel->setHeight(xKernel->getWidth());
    xKernel->setWidth(1);
    return xKernel;
}

Kernel::Kernel() {
    this->values = new float[0];
    this->width = 0;
}

Kernel::Kernel(float *values, int width, int height) {
    this->values = values;
    this->width = width;
    this->heigth = height;
}

Kernel::Kernel(float *values, int radius) {
    this->values = values;
    this->width = radius;
    this->heigth = radius;
}

Kernel::~Kernel() {

}

