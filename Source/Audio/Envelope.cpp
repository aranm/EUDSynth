// James Measey 14002897: 2016-17

#include "Envelope.h"
#include "../../JuceLibraryCode/JuceHeader.h"

Envelope::Envelope()
 : envPos(0),
   envPlaying(false) {}

Envelope::~Envelope() {}

float Envelope::ADSR (float attack,   float decay,
                      float sustain,  float release,
                      float sustainLvl)
{
    if (!envPlaying)
        return 0;
    
    //Covert each point from (time) to (samples)
    attack *= 44100.f;
    decay *= 44100.f;
    sustain *= 44100.f;
    release *= 44100.f;

    envPos++;
    
    if (envPos <= attack)
        env = envPos / attack;
    else if (envPos <= (decay + attack))
        env = 1.f - (((envPos - attack) * (1 - sustainLvl)) / decay);
    else if (envPos <= (attack + decay + sustain))
        env = sustainLvl;
    else if (envPos <= (attack + decay + sustain + release))
        env -= sustainLvl / release;
    else
    {
        envPlaying = false;
        env = 0;
    }
    
    return env;
}

float Envelope::pointToPoint (float p1Time, float p1Lvl,
                              float p2Time, float p2Lvl,
                              float p3Time, float p3Lvl,
                              float p4Time, float p4Lvl)
{
    //Stop program if p1Time is not 0 (should always be 0)
    assert (p1Time == 0.f);
    
    if(envPlaying)
    {
        envPos++;
        
        //Covert each point from (time) to (sample)
        p1Time *= 44100.f;
        p2Time *= 44100.f;
        p3Time *= 44100.f;
        p4Time *= 44100.f;
        
        Point<float> p1, p2;
        float offset = 0.f;
        
        //attack
        if (envPos <= (p2Time))
        {
            p1 = Point<float>(p1Time, p1Lvl);
            p2 = Point<float>(p2Time, p2Lvl);
            offset = p1Time;
        }
        else if (envPos <= (p2Time + p3Time))
        {
            p1 = Point<float>(p2Time, p2Lvl);
            p2 = Point<float>(p3Time, p3Lvl);
            offset = p1Time + p2Time;
        }
        else if (envPos <= (p2Time + p3Time + p4Time))
        {
            p1 = Point<float>(p3Time, p3Lvl);
            p2 = Point<float>(p4Time, p4Lvl);
            offset = p1Time + p2Time + p3Time;
            
        }
        else
        {
            envPlaying = false;
            return env;
        }
        
        const float envPosRelativeToOffset = envPos - offset;
        const float positionRatio = envPosRelativeToOffset / p2.getX();
        env = (1 - positionRatio) * p1.getY() + positionRatio * p2.getY();
    }

    
    return env;
}


void Envelope::startEnv()
{
    envPos = 0;
    envPlaying = true;
}

void Envelope::setSampleRate(float sampleRate)
{
    sampRate = sampleRate;
}

bool Envelope::getEnvPlaying()
{
    return envPlaying;
}

