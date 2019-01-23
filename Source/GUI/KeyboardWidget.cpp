// James Measey 14002897: 2016-17

#include "KeyboardWidget.h"
//======================== Constructer/Destructer =============================

KeyboardWidget::KeyboardWidget (AudioControl& audio)
 :  virtualKeyboard (state, MidiKeyboardComponent::horizontalKeyboard),
    audio(audio)
{
    addAndMakeVisible (virtualKeyboard);
    state.addListener (this);
    
    virtualKeyboard.setAvailableRange(59, 70); //B3-F#3 range (12 for 12 drums)
    virtualKeyboard.setColour(MidiKeyboardComponent::keyDownOverlayColourId, Colours::seagreen);
    virtualKeyboard.setColour(MidiKeyboardComponent::mouseOverKeyOverlayColourId, Colour(0xaa395244));
}
KeyboardWidget::~KeyboardWidget()
{
    
}

//======================= Button / State Functions ============================

void KeyboardWidget::handleNoteOn (MidiKeyboardState* mk, int midiChannel,
                                   int midiNoteNumber, float velocity)
{
    audio.handleVirtualKeyboard(midiNoteNumber, 80, true);
}

void KeyboardWidget::handleNoteOff (MidiKeyboardState*, int midiChannel,
                                    int midiNoteNumber, float )
{
    audio.handleVirtualKeyboard(midiNoteNumber, 0, false);
}

//========================== Graphic Functions ================================

void KeyboardWidget::paint (Graphics& g)
{
    // Basic Windows
    g.setColour(Colour(0xff99999e));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 10);
    g.setColour(Colour(0xff33333a));
    g.fillRoundedRectangle(getLocalBounds().toFloat()
                           .withTrimmedTop(15).reduced(6, 6), 4);
    
    // Border
    g.setColour(Colours::black);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 10, 3);
    
    // Widget Name
    g.setColour(Colour(0xff33333a));
    g.setFont(20);
    g.drawText("MIDI Keyboard", 12, 3, getWidth() - 6, 15, Justification::centredLeft);
}

void KeyboardWidget::resized()
{
    virtualKeyboard.setBounds(getLocalBounds().withTrimmedTop(15).reduced(12, 12));
    virtualKeyboard.setKeyWidth(getWidth() / 7.75);
}
 
