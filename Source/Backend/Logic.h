#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

#include "../SessionGUI/FreqButtons.h"
#include "Configuration.h"

class Logic
{
public:
    Logic (Configuration* config);

    void getNextFilterSpec (float& freq, float& gainDB);
    void guessMade (int guess);

    String getResults();
    int calcScore();

private:
    Random rand;
    int numBands;
    std::unique_ptr<float[]> freqBands;

    Array<int> guesses;
    Array<int> truths;

    const Configuration* config;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Logic)
};

#endif // LOGIC_H_INCLUDED
