#pragma once

class LPF {
public:
    LPF(float cutoff, float samplerate);
    ~LPF();

    float update(float input);
    void setCutoff(float cutoff);


private:
    float cutoff;
    float deltaTime;
    float output;
    float ePow;
};