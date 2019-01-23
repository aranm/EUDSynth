// James Measey 14002897: 2016-17

#include "MasterWidget.h"
//======================== Constructer/Destructer =============================
MasterWidget::MasterWidget(AudioControl& audio)
:   audio(audio)
{
    addAndMakeVisible(masterGain);
    masterGain.setSliderStyle(Slider::LinearBarVertical);
    masterGain.setColour(Slider::backgroundColourId, Colour(0xaa395244));
    masterGain.setColour(Slider::thumbColourId, Colours::seagreen);
    masterGain.setColour(Slider::textBoxTextColourId, Colours::whitesmoke);
    masterGain.setRange(0.0, 1.0, 0.01);
    masterGain.setValue(0.8);
    masterGain.setTextBoxIsEditable(false);
    masterGain.addListener(this);
}
MasterWidget::~MasterWidget()
{
    
}

//======================= Button / State Functions ============================

void MasterWidget::sliderValueChanged(Slider* slider)
{
    audio.setMasterGain(slider->getValue());
}

//========================== Graphic Functions ================================

void MasterWidget::paint (Graphics& g)
{
    // Basic Windows
    g.setColour(Colour(0xff999999));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 10);
    g.setColour(Colour(0xff33333a));
    g.fillRoundedRectangle(rWindow, 4);
    
    // Border
    g.setColour(Colours::black);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 10, 3);
    
    // Widget Name
    g.setColour(Colour(0xff33333a));
    g.setFont(20);
    g.drawText("Master Level", 12, 3, getWidth(), 15, Justification::centredLeft);
}

void MasterWidget::resized()
{
    rWindow.setBounds(6, 21, getWidth() - 12, getHeight() - 27);
    masterGain.setBounds(rWindow.getX() + rWindow.getWidth() / 4,
                         rWindow.getY() + rWindow.getHeight() / 20,
                         rWindow.getWidth() / 2,
                         rWindow.getHeight() * 0.9);
}

