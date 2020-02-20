#pragma once

class LPF {
public:
    LPF(float cutoff, float resonance, float samplerate);
    ~LPF();

    // original without res
    float update(float input);
    // alternative algoritm with resonance
    float rcUpdate(float input);

    inline void setCutoff(float cutoff) {
        this->cutoff = cutoff;
    };
    inline void setRes(float res) {this->resonance = res;};


private:
    float cutoff;
    float resonance;
    float deltaTime;
    float output;

    float ePow;

    float v0, v1 = 0;

};