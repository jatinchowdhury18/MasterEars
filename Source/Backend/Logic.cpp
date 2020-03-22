#include "Logic.h"

Logic::Logic (Configuration* config) :
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

void Logic::getNextFilterSpec (float& freq, float& gainDB)
{
    auto band = rand.nextInt (numBands);
    freq = freqBands[band];

    gainDB = 3.0f * (int (config->amt) + 1);        
    auto signMult = config->type == EQType::Cut ? -1 :
        (config->type == EQType::BoostAndCut ? rand.nextInt (2)*2 - 1 : 1);
    gainDB *= signMult;

    truths.add (band);
}

void Logic::guessMade (int guess)
{
    guesses.add (guess);
}

String Logic::getResults()
{
    jassert (truths.size() == guesses.size());

    String res;
    auto freqStrings = FreqButtons::createFreqStrings();
    for (int i = 0; i < truths.size(); ++i)
    {
        res += "Trial " + String (i) + ":\t";
        res += "Actual: " + String (freqStrings[truths[i]]) + ",\t";
        res += "Guess: " + String (freqStrings[guesses[i]]) + "\n";
    }

    auto score = calcScore();
    res += "\nFINAL SCORE: " + String (score) + "\n";

    return res;
}

int Logic::calcScore()
{
    int score = 0;
    for (int i = 0; i < truths.size(); ++i)
        score += 10 - abs (truths[i] - guesses[i]);

    return score;
}
