#include "Oscillator.h"
#include <math.h>

void Oscillator::Init(float sample_rate)
{
    sample_rate_ = sample_rate;
    phs.Init(sample_rate, 0);
    waveform_ = WAVE_SIN;
    SetWaveform(waveform_);
}

void Oscillator::SetFreq(float freq)
{
    phs.SetFreq(freq);
}

void Oscillator::SetWaveform(int waveform)
{
    switch (waveform)
    {
    case WAVE_SIN:
        for (int i = 0; i < 1024; i++)
        {
            wavetable[i] = sin(2.0 * M_PI * i / 1024);
        }
        break;
    case WAVE_TRI:
        for (int i = 0; i < 1024; i++)
        {
            wavetable[i] = (i < 512) ? -1.0 + (i / 512.0) * 2.0 : 1.0 - ((i - 512) / 512.0) * 2.0;
        }
        break;
    case WAVE_SAW:
        for (int i = 0; i < 1024; i++)
        {
            wavetable[i] = -1.0 + (i / 1024.0) * 2.0;
        }
        break;
    case WAVE_SQUARE:
        for (int i = 0; i < 1024; i++)
        {
            wavetable[i] = (i < 512) ? -1.0 : 1.0;
        }
        break;
    }
}

float Oscillator::Process()
{
    return wavetable[(int)(phs.Process() * 1024)];
}