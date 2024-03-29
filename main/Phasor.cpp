#include "Phasor.h"

#define TWOPI_F 6.283185307179586476925286766559f

void Phasor::SetFreq(float freq)
{
    freq_ = freq;
    inc_ = (TWOPI_F * freq_) / sample_rate_;
}

float Phasor::Process()
{
    float out;
    out = phs_ / TWOPI_F;
    phs_ += inc_;
    if (phs_ > TWOPI_F)
    {
        phs_ -= TWOPI_F;
    }
    if (phs_ < 0.0f)
    {
        phs_ = 0.0f;
    }
    return out;
}

