#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED

#include "JuceHeader.h"

/** Peaking filter using TDF-II Biquad **/
class Filter
{
public:
    Filter();

    void reset (double sampleRate, bool enabled);
    void setFilterSpec (float fc, float gainDB, float Q = 0.7071f);
    void processBlock (float* buffer, int numSamples);
    void setEnabled (bool enabled) { curEnabled = enabled; }

private:
    inline float process (float x)
    {
        float y = z[1] + x*b[0];
        z[1] = z[2] + x*b[1] - y*a[1];
        z[2] = x*b[2] - y*a[2];

        return y;
    }

    float fs = 48000.0f;
    std::unique_ptr<float[]> a; // IIR coefs
    std::unique_ptr<float[]> b; // FIR coefs
    std::unique_ptr<float[]> z; // State variables

    const int order = 2;
    float thisFreq = 1000.0f;
    float thisQ = 0.7071f;
    float thisGainDB = 0.0f;

    bool curEnabled = true;
    bool prevEnabled = true;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};

#endif // FILTER_H_INCLUDED
