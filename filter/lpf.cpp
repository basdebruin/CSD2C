#include "lpf.h"
#include <cmath>

LPF::LPF(float cutoff, float samplerate) {
    this->cutoff = cutoff;
    deltaTime = 1 / samplerate;
};

LPF::~LPF(){};

float LPF::update(float input) {
    ePow = 1 - exp(-deltaTime * 2 * M_PI * cutoff);
    return output = (input - output) * ePow;
}

void LPF::setCutoff(float cutoff) {
    this->cutoff = cutoff;
}