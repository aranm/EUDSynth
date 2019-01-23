// James Measey 14002897: 2016-17

#ifndef PlayPage_h
#define PlayPage_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "KeyboardWidget.h"
#include "SequencerWidget.h"
#include "MasterWidget.h"
#include "AudioControl.h"

class PlayPage :    public Component
{
public:
    PlayPage (AudioControl& audio);
    ~PlayPage();
    
    void paint (Graphics& g) override;
    
    void resized() override;
    
    SequencerWidget sequencer;
private:
    AudioControl& audio;
    
    Rectangle<float> sampleBarView;
    Rectangle<float> keyboardView;
    Rectangle<float> widgetView;
    
    KeyboardWidget keyboard;
    MasterWidget masterWidget;
};

#endif  // PlayPage_h
