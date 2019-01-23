// James Measey 14002897: 2016-17

#ifndef MainComponent_h
#define MainComponent_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioControl.h"

#include "PlayPage.h"
#include "ControlPage.h"

class MainContentComponent :    public Component,
                                public Button::Listener,
                                public KeyListener
{
public:
    MainContentComponent (AudioControl& audio);
    ~MainContentComponent();
    
    void buttonClicked (Button* button) override;
    
    bool keyPressed(const KeyPress &key, Component *originatingComponent) override;
    
    void paint (Graphics& g) override;
    
    void resized() override;
    
private:
    Rectangle<float> mainView;
    Rectangle<float> namePlate;
    
    AudioControl& audio;
    
    TextButton playPagebutton, controlPagebutton;
    PlayPage playPage;
    ControlPage controlPage;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif /* MainComponent_h */
