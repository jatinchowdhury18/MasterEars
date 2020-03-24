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

    int getNumTrials() const { return truths.size(); }
    String getGuess (int trial, bool truth);
    int getScoreForTrial (int trial);

private:
    Random rand;
    int numBands;
    std::unique_ptr<float[]> freqBands;
    StringArray freqStrings;

    Array<int> guesses;
    Array<int> truths;

    const Configuration* config;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Logic)
};

#endif // LOGIC_H_INCLUDED
