#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

#include "../SessionGUI/FreqButtons.h"
#include "Configuration.h"

class Logic
{
public:
    Logic (Configuration* config) :
        config (config)
    {
        auto freqStrings = FreqButtons::createFreqStrings();
        numBands = freqStrings.size();
        freqBands.reset (new float [numBands]);

        for (int i = 0; i < numBands; ++i)
        {
            freqBands[i] = freqStrings[i].upToFirstOccurrenceOf (" ", false, false).getFloatValue();
            if (freqStrings[i].contains ("k"))
                freqBands[i] *= 1000;
        }
    }

    void getNextFilterSpec (float& freq, float& gainDB)
    {
        auto band = rand.nextInt (numBands);
        freq = freqBands[band];

        if (config->amt == EQAmt::Three)
            gainDB = 3.0f;
        else if (config->amt == EQAmt::Six)
            gainDB = 6.0f;
        else if (config->amt == EQAmt::Nine)
            gainDB = 9.0f;
        else
            jassertfalse;
        
        auto signMult = config->type == EQType::Cut ? -1 :
            (config->type == EQType::BoostAndCut ? rand.nextInt (2)*2 - 1 : 1);
        gainDB *= signMult;

        truths.add (band);
    }

    void guessMade (int guess)
    {
        guesses.add (guess);
    }

    String getResults()
    {
        jassert (truths.size() == guesses.size());

        String res;
        for (int i = 0; i < truths.size(); ++i)
        {
            res += "Truth: " + String (truths[i]) + ", Guess: " + String (guesses[i]) + "\n";
        }
        return res;
    }

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
