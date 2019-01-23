// James Measey 14002897: 2016-17
#ifndef SequencerWidget_h
#define SequencerWidget_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioControl.h"

class SequencerWidget : public Component,
                        public Button::Listener,
                        public Slider::Listener
{
public:
    SequencerWidget(AudioControl& audio);
    ~SequencerWidget();
    
    void buttonClicked (Button* button) override;
    void sliderValueChanged (Slider* slider) override;
    
    //==========================================================
    
    void paint (Graphics& g) override;
    void resized() override;
    void playbackPosControl();
    void setPlaybackButtonState(bool isOn);
    
    //==========================================================
    
    void clearButtons();
    void updateSequencer();
    
private:
    Rectangle<float> rWindow, sequencerWindow;
    
    TextButton sequencerButton[NUM_DRUMS][MAX_STEPS];
    TextButton muteButton[NUM_DRUMS];
    TextButton numStepsSelect[3];
    TextButton clearSequencer;

    TextButton playButton;
    Slider BPMSlider;
    float sequencerBPM;
    
    String drumNames[NUM_DRUMS]
    {   "Bass Drum",    "Kick Drum",    "RimShot",  "Snare" ,   "Clap",     "Cowbell",
        "Low Tom",      "Closed Hat",   "Mid Tom",  "Cymbal",   "High Tom", "Open Hat"};
    
    int numDrums, numSteps;
    float buttonWidth, buttonHeight;
    
    AudioControl& audio;
};

#endif  // SequencerWidget_h
