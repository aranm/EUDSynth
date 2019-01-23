// James Measey 14002897: 2016-17
#ifndef SEQUENCER_H_INCLUDED
#define SEQUENCER_H_INCLUDED

#include "SynthDrum.h"
#include "DrumController.h"


class Sequencer
{
public:
    Sequencer();
    ~Sequencer();
    
    void setStep(bool isOn, int drumNum, int stepNum);
    void setAllSteps(bool isOnArray[12][32]);
    
    float getSamplesInSequence();
    void startAndPrepareDrums(int drumNum);
    
    void setBPM(float bpm);
    void setPlaybackState(bool playing);
    void setStepNum(int stepNum);
    void setMute(bool muted, int drumNum);
    
    bool getPlaybackState();
    int getStepPosition();
    
    DrumController drumController;
private:
    bool isStepOn[12][32];
    bool isFadeOut[12];
    
    float playbackBPM;
    bool isPlaying;
    bool isMuted[12];
    
    int stepPosition;
    int stepDuration;
    int curSteps;
    int count;
};

#endif  // Sequencer_h
