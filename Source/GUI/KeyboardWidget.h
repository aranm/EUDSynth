// James Measey 14002897: 2016-17

#ifndef KeyboardWidget_h
#define KeyboardWidget_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioControl.h"

class KeyboardWidget :  public Component,
                        private MidiKeyboardStateListener
{
public:
    KeyboardWidget (AudioControl& audio);
    ~KeyboardWidget();

    void handleNoteOn (MidiKeyboardState* mk, int midiChannel, int midiNoteNumber, float velocity) override;

    void handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float) override;
    
    void paint (Graphics& g) override;
    
    void resized() override;
    
private:
    MidiKeyboardState state;
    MidiKeyboardComponent virtualKeyboard;
    
    AudioControl& audio;
};

#endif  // KeyboardWidget_h
