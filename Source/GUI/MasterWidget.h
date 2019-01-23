// James Measey 14002897: 2016-17

#ifndef MasterWidget_h
#define MasterWidget_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioControl.h"

class MasterWidget :    public Component,
                        public Slider::Listener
{
public:
    MasterWidget(AudioControl& audio);
    ~MasterWidget();
    
    void sliderValueChanged(Slider* slider) override;
    
    void paint (Graphics& g) override;
    
    void resized() override;
    
private:
    AudioControl& audio;
    
    Rectangle<float> rWindow;
    Slider masterGain;
};

#endif  // MasterWidget_h
