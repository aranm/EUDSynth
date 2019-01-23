// James Measey 14002897: 2016-17

#ifndef Envelope_h
#define Envelope_h

#include <math.h>

class Envelope
{
public:
    Envelope();
    ~Envelope();
    
    float ADSR (float attack,   float decay,
                float sustain,  float release,
                float sustainLvl);
    
    float pointToPoint (float p1Time, float p1Lvl,
                        float p2Time, float p2Lvl,
                        float p3Time, float p3Lvl,
                        float p4Time, float p4Lvl);
    
    
    void setSampleRate (float sampleRate);
    
    void startEnv();
    bool getEnvPlaying();
    
private:
    float env;
    int envPos;
    bool envPlaying;
    float sampRate;
};

#endif  // Envelope_h
