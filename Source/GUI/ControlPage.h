// James Measey 14002897: 2016-17

#ifndef ControlPage_h
#define ControlPage_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioControl.h"

class ControlPage : public Component,
                    public Button::Listener,
                    public Slider::Listener
{
public:
    ControlPage(AudioControl& audio);
    ~ControlPage();
    
    void buttonClicked (Button* button) override;
    
    void sliderValueChanged(Slider* slider) override;
    
    void paint (Graphics& g) override;
    void resized() override;
    
    void buildIndividualControls();
    void setControlToDefault(int drumNum);
    
private:
    AudioControl& audio;
    
    Rectangle<float> rWindow;
    Rectangle<float> drumWidget[12];
    
    //Bass Drum
    Slider sControl[12][3];
    TextButton setDefault[12];
    
    
    String drumNames[12]
    {   "Bass Drum",    "Kick Drum",    "RimShot",  "Snare" ,   "Clap",     "Cowbell",
        "Low Tom",      "Closed Hat",   "Mid Tom",  "Cymbal",   "High Tom", "Open Hat"};
    String controlNames[24]
    {   "Drum Length",  "Frequency",    "Drum Length",   "Frequency",   "Air Level",   "Tone",
        "Rattle",       "Frequency",       "Length",   "Frequency",   "Length",   "Tone",
        "Drum Length",   "Air Level",       "Frequency",   "Length",   "Drum Length",   "Air Level",
        "Tone",       "Hiss",       "Drum Length",   "Air Level",   "Frequency",   "Length",};
    
};

#endif  // ControlPage_h
