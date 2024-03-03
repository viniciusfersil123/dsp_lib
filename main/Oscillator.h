#ifndef OSCILLATOR_H
#define OSCILLATOR_H
#include "Phasor.h"

class Oscillator
{
public:
    Oscillator(){};
    ~Oscillator(){};

    enum
    {
        WAVE_SIN,
        WAVE_TRI,
        WAVE_SAW,
        WAVE_SQUARE,
    };

    void Init(float sample_rate);

    void SetFreq(float freq);

    void SetWaveform(int waveform);

    float Process();

private:
    float sample_rate_, waveform_;
    float wavetable[1024];
    Phasor phs;
};

#endif