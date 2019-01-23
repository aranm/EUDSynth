// James Measey 14002897: 2016-17
#include "Sequencer.h"

Sequencer::Sequencer()
:   stepPosition(0),
    stepDuration(0),
    curSteps(16),
    count(0),
    isPlaying(false)

{
    // Initialise arrays
    for(int drum = 0; drum < 12; drum++)
    {
        isMuted[drum] = false;
        for(int step = 0; step < 36; step++)
            isStepOn[drum][step] = false;
    }

}
Sequencer::~Sequencer() {}

void Sequencer::setStep(bool isOn, int drumNum, int stepNum)
{
    isStepOn[drumNum][stepNum] = isOn;
}

float Sequencer::getSamplesInSequence()
{
    float sample = 0;
    
    if(isPlaying)
    {
        count++;
        
        if(count == stepDuration)
        {
            count = 0;
            
            for(int i = 0; i < 12; i++)
                if(isStepOn[i][stepPosition] && !isMuted[i])
                {
                    drumController.prepare(59+i);
                    drumController.start(59+i);
                }
            stepPosition++;
            
            
            
            if(stepPosition == curSteps)
                stepPosition = 0;
        }
    }
    else
    {
        stepPosition = 0;
        count = 0;
    }

    
    sample = drumController.play();
    
    return sample;
}

void Sequencer::startAndPrepareDrums(int drumNum)
{

}

void Sequencer::setBPM(float bpm)
{
    playbackBPM = bpm;
    stepDuration = ((44100 * 60) / playbackBPM) / 4;
    
    DBG("\n");
}

void Sequencer::setStepNum(int stepNum)
{
    curSteps = stepNum;
    stepPosition = 0;
}

void Sequencer::setMute(bool muted, int drumNum)
{
    isMuted[drumNum] = muted;
}

void Sequencer::setPlaybackState(bool playing)
{
    isPlaying = playing;
    stepPosition = 0;
}

bool Sequencer::getPlaybackState()
{
    return isPlaying;
}

int Sequencer::getStepPosition()
{
    return stepPosition;
}
