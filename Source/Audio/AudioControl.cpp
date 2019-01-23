// James Measey 14002897: 2016-17

#include "AudioControl.h"
//======================== Constructer/Destructer =============================

AudioControl::AudioControl()
:   sequencerPlaying(false),
    masterGain(0.8)
{
    audioDeviceManager.initialiseWithDefaultDevices (2, 2);
    
    StringArray sa (MidiInput::getDevices());
    for (String& s : sa)
    {
        DBG(s);
        audioDeviceManager.setMidiInputEnabled (s, true);
    }
    
    audioDeviceManager.addMidiInputCallback (String::empty, this);
    audioDeviceManager.addAudioCallback (this);
    
}

AudioControl::~AudioControl()
{
    audioDeviceManager.removeAudioCallback (this);
    audioDeviceManager.removeMidiInputCallback (String::empty, this);
}

//============================ MIDI Functions =================================

void AudioControl::handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message)
{
    if (message.isNoteOnOrOff())
    {
        handleVirtualKeyboard(message.getNoteNumber(), 127, message.isNoteOn());
        
    }
}

void AudioControl::handleVirtualKeyboard (int noteNum, int vel, bool noteOn)
{
    amplitude = (vel / 127.0);
    frequency = (440 * pow (2.0, (noteNum - 69) / 12.0));
    isNoteOn = noteOn;
    note = noteNum;
    
    if(isNoteOn)    DBG("Note ON message");
    else            DBG("Note OFF message");
    
    DBG("Note" << noteNum << ": amp(" << amplitude.get() << ")\n");
}

//=========================== Audio Processing ================================

void AudioControl::audioDeviceIOCallback (const float** inputChannelData,
                                          int numInputChannels,
                                          float** outputChannelData,
                                          int numOutputChannels,
                                          int numSamples)
{
    const float *inL = inputChannelData[0];
    const float *inR = inputChannelData[1];
    float *outL = outputChannelData[0];
    float *outR = outputChannelData[1];
    
    float monoOutput = 0;
    float level, peak;
    
    if(isNoteOn)
        drumController.start(note);
    else
        drumController.prepare(note);
    
    bool test = false;
    
    while(numSamples--)
    {
        monoOutput = 0;
        
        monoOutput += drumController.play();

        monoOutput += sequencer.getSamplesInSequence();
        
        if(monoOutput > 1.0)
        {
            DBG("PreMaster Capped: " << monoOutput);
            test = true;
        }
        
        monoOutput = basicCompresser(monoOutput);
        
        if(test)
        {
            DBG("FinalOutput: " << monoOutput << "\n");
            test = false;
        }
        
        monoOutput = monoOutput * masterGain;
        
        *outL = monoOutput;
        *outR = monoOutput;
        
        if(monoOutput < 0)  level = monoOutput * -1;
        else                level = monoOutput;
        
        if(level > peak)
            peak = level;
        
        inL++;
        inR++;
        outL++;
        outR++;
    }
    
    if(peak > 0.8)
        DBG("Large peak in cycle: " << peak);
    
}

void AudioControl::audioDeviceAboutToStart (AudioIODevice* device)
{
    sampleRate = device->getCurrentSampleRate();
    //synthDrum.setSampleRate(sampleRate);
    

    DBG("PreparetoPlay");
}

void AudioControl::audioDeviceStopped()
{
    DBG("Release");
}

//=========================== Set/Get Functions ===============================

float AudioControl::basicCompresser(float sample)
{
    float absVal;
    float threshold = 0.8;
    float ratio = 4.0; //can not be less than 1
    
    if(sample < 0)  absVal = sample * -1;
    else            absVal = sample;
    
    if(absVal > threshold)
    {
        if(sample < 0)  sample = -1 * (threshold + ((absVal - threshold) / ratio));
        else            sample = (threshold + ((absVal - threshold) / ratio));
    }
    
    return sample;
}

void AudioControl::setMasterGain(float gain)
{
    masterGain = gain;
    DBG(masterGain);
}


