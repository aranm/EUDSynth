// James Measey 14002897: 2016-17
#ifndef DRUMCONTROLLER_H_INCLUDED
#define DRUMCONTROLLER_H_INCLUDED

#include "SynthDrum.h"

class DrumController
{
public:
    DrumController();
    ~DrumController();
    
    void start(int note);
    void prepare(int note);
    
    float play();
    void alter(int drumNum, float control1, float control2, float gain);
    
private:
    BassSynth bass[2];
    KickSynth kick[2];
    SnareSynth snare[2];
    LowTomSynth loTom[2];
    MidTomSynth miTom[2];
    HighTomSynth hiTom[2];
    ClosedHatSynth clHat[2];
    OpenHatSynth opHat[2];
    CymbalSynth cymbal[2];
    RimshotSynth rimshot[2];
    ClapSynth clap[2];
    CowbellSynth cowbell[2];
};



#endif  // DRUMCONTROLLER_H_INCLUDED
