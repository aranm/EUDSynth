// James Measey 14002897: 2016-17

#ifndef AudioControl_h
#define AudioControl_h

#define NUM_DRUMS 12
#define MAX_STEPS 32

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthDrum.h"
#include "Sequencer.h"
#include "DrumController.h"

class AudioControl :    public MidiInputCallback,
                        public AudioIODeviceCallback
{
public:
    /** Constructor */
    AudioControl();
    
    /** Destructor */
    ~AudioControl();
    
    /** Returns the audio device manager, don't keep a copy of it! */
    AudioDeviceManager& getAudioDeviceManager() { return audioDeviceManager; }
    
    void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) override;
    void handleVirtualKeyboard (int noteNum, int vel, bool isNoteOn);

    void audioDeviceIOCallback (const float** inputChannelData,
                                int numInputChannels,
                                float** outputChannelData,
                                int numOutputChannels,
                                int numSamples) override;
    void audioDeviceAboutToStart (AudioIODevice* device) override;
    void audioDeviceStopped() override;
    
    float basicCompresser(float sample);
    void setMasterGain(float gain);
    
    Sequencer sequencer;
    DrumController drumController;
private:

    AudioDeviceManager audioDeviceManager;

    float sampleRate, phasePosition;
    Atomic<float> frequency, amplitude;
    float freq;
    
    bool sequencerPlaying;
    
    bool isNoteOn;
    int note;
    
    float masterGain;
    
};

#endif  /* AudioControl_h */

