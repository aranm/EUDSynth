// James Measey 14002897: 2016-17

#include "WaveGenerator.h"

//============================= SineGenerator =================================

SineGenerator::SineGenerator() {}
SineGenerator::~SineGenerator() {}

float SineGenerator::sine(float freq, float amp)
{
    const float twoPi = 2 * M_PI;
    const float phaseIncrement = (twoPi * freq) / 44100 /*TODO: change to varaible*/;
    
    phasePos += phaseIncrement;
    
    if (phasePos > twoPi) phasePos -= twoPi;

    return sin(phasePos) * amp;
}

void SineGenerator::setSampleRate (float sampleRate)
{
    sampRate = sampleRate;
}

//============================== WaveBuilder ==================================

WaveBuilder::WaveBuilder() {}
WaveBuilder::~WaveBuilder() {}

float WaveBuilder::getSine(float freq, float amp)
{
    return waveGen[0].sine(freq, amp);
}

float WaveBuilder::getSquare(float freq, float amp)
{
    float harmonics[NUM_HARMONICS];
    float newWave = 0;
    
    for(int c = 1; c < NUM_HARMONICS; c++)
    {
        harmonics[c-1] = waveGen[c-1].sine(freq * c, amp / c);
    }
    
    for(int c = 0; c < NUM_HARMONICS; c += 2)
    {
        newWave += harmonics[c];
    }
    
    
    return newWave;
}

float WaveBuilder::getSaw (float freq, float amp)
{
    float harmonics[NUM_HARMONICS];
    float newWave = 0;
    
    for(int c = 1; c < NUM_HARMONICS; c++)
    {
        harmonics[c-1] = waveGen[c-1].sine(freq * c, amp / c);
        newWave += harmonics[c-1];
    }
    
    
    return newWave * 0.6;
}

float WaveBuilder::getNoise(float amp)
{
    Random r;
    return ((r.nextFloat() * 2) - 1) * amp;
}

