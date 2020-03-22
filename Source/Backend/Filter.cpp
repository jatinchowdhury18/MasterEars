#include "Filter.h"

Filter::Filter()
{
    a.reset (new float[order+1]);
    b.reset (new float[order+1]);
    z.reset (new float[order+1]);
}

void Filter::reset (double sampleRate, bool enabled)
{
    curEnabled = prevEnabled = enabled;

    //clear state
    for (int n = 0; n <= order; ++n)
        z[n] = 0.0f;

    fs = (float) sampleRate;
    setFilterSpec (thisFreq, thisGainDB, thisQ);
}

void Filter::setFilterSpec (float fc, float gainDB, float Q)
{
    thisFreq = fc;
    thisGainDB = gainDB;
    thisQ = Q;

    auto newGain = Decibels::decibelsToGain (gainDB);

    float wc = MathConstants<float>::twoPi * fc / fs;
    float c = 1.0f / tanf (wc / 2.0f);
    float phi = c*c;
    float Knum = c / Q;
    float Kdenom = Knum;

    if (newGain > 1.0f)
        Knum *= newGain;
    else if (newGain < 1.0f)
        Kdenom /= newGain;

    float a0 = phi + Kdenom + 1.0f;

    b[0] = (phi + Knum + 1.0f) / a0;
    b[1] = 2.0f * (1.0f - phi) / a0;
    b[2] = (phi - Knum + 1.0f) / a0;

    a[1] = 2.0f * (1.0f - phi) / a0;
    a[2] = (phi - Kdenom + 1.0f) / a0;
}

void Filter::processBlock (float* buffer, int numSamples)
{
    if (! curEnabled && ! prevEnabled) // bypassed!
        return;

    if (curEnabled && prevEnabled) // normal operation
    {
        for (int n = 0; n < numSamples; ++n)
            buffer[n] = process (buffer[n]);

        return;
    }

    if (curEnabled) // fade in
    {
        float mult = 1.0f;
        for (int n = 0; n < numSamples; ++n)
        {
            mult = float (n) / float (numSamples);
            buffer[n] = mult * process (buffer[n]) + (1.0f - mult) * buffer[n];
        }
    }

    if (prevEnabled) // fade out
    {
        float mult = 1.0f;
        for (int n = 0; n < numSamples; ++n)
        {
            mult = 1.0f - (float (n) / float (numSamples));
            buffer[n] = mult * process (buffer[n]) + (1.0f - mult) * buffer[n];
        }
    }

    prevEnabled = curEnabled;
}
