// James Measey 14002897: 2016-17
#include "SequencerWidget.h"
//======================== Constructer/Destructer =============================
SequencerWidget::SequencerWidget(AudioControl& audio)
 :  numDrums(NUM_DRUMS),
    numSteps(16),
    audio(audio)
{
    for(int c = 0; c < numDrums; c++)
        for(int l = 0; l < MAX_STEPS; l++)
        {
            addChildComponent(sequencerButton[c][l]);
            sequencerButton[c][l].addListener(this);
            sequencerButton[c][l].setColour(TextButton::buttonColourId,
                                            Colours::transparentBlack);
            sequencerButton[c][l].setColour(TextButton::buttonOnColourId,
                                            Colours::black);
            sequencerButton[c][l].setConnectedEdges(1 | 2 | 4 | 8);
        }
    
    for(int c = 0; c < 3; c++)
    {
        addAndMakeVisible(numStepsSelect[c]);
        numStepsSelect[c].addListener(this);
        
        numStepsSelect[c].setRadioGroupId (1, dontSendNotification);
        numStepsSelect[c].setConnectedEdges(2 | 1);
        numStepsSelect[c].setColour(TextButton::buttonColourId,
                                    Colour(0xff999999));
        numStepsSelect[c].setColour(TextButton::buttonOnColourId,
                                    Colours::seagreen);
    }
    
    numStepsSelect[0].setConnectedEdges(1);
    numStepsSelect[0].setButtonText("32");
    numStepsSelect[1].setConnectedEdges(1 | 2);
    numStepsSelect[1].setButtonText("16");
    numStepsSelect[2].setConnectedEdges(2);
    numStepsSelect[2].setButtonText("8");
    
    numStepsSelect[1].setToggleState(true, dontSendNotification);
    
    for(int c = 0; c < numDrums; c++)
    {
        addAndMakeVisible(muteButton[c]);
        muteButton[c].addListener(this);
        
        muteButton[c].setColour(TextButton::buttonColourId,
                                    Colour(0xff999999));
        muteButton[c].setColour(TextButton::buttonOnColourId,
                                Colours::seagreen);
        muteButton[c].setButtonText("mute");
    }
    
    addAndMakeVisible(BPMSlider);
    BPMSlider.setSliderStyle(Slider::SliderStyle::IncDecButtons);
    BPMSlider.setIncDecButtonsMode(Slider::incDecButtonsDraggable_Vertical);
    BPMSlider.setRange(50, 200, 1);
    BPMSlider.setValue(120);
    audio.sequencer.setBPM(120);
    BPMSlider.addListener(this);
    
    addAndMakeVisible(playButton);
    playButton.setButtonText("Play");
    playButton.setColour(TextButton::buttonColourId, Colour(0xff999999));
    playButton.setColour(TextButton::buttonOnColourId, Colours::seagreen);
    playButton.addListener(this);
    
    addAndMakeVisible(clearSequencer);
    clearSequencer.setButtonText("Clear");
    clearSequencer.setColour(TextButton::buttonColourId, Colour(0xff999999));
    clearSequencer.addListener(this);
}
SequencerWidget::~SequencerWidget()
{
    
}

//============================ GUI Functions ==================================

void SequencerWidget::buttonClicked (Button* button)
{
    for(int i = 0; i < numDrums; i++)
        if(button == &muteButton[i])
        {
            button->setToggleState(!button->getToggleState(), dontSendNotification);
            audio.sequencer.setMute(button->getToggleState(), i);
            return;
        }
    
    if(button == &numStepsSelect[0])
    {
        button->setToggleState(true, dontSendNotification);
        numSteps = 32;
        updateSequencer();
        repaint();
        audio.sequencer.setStepNum(32);
    }
    else if(button == &numStepsSelect[1])
    {
        button->setToggleState(true, dontSendNotification);
        numSteps = 16;
        updateSequencer();
        repaint();
        audio.sequencer.setStepNum(16);
    }
    else if(button == &numStepsSelect[2])
    {
        button->setToggleState(true, dontSendNotification);
        numSteps = 8;
        updateSequencer();
        repaint();
        audio.sequencer.setStepNum(8);
    }
    else if(button == &playButton)
    {
        button->setToggleState(!button->getToggleState(), dontSendNotification);
        audio.sequencer.setPlaybackState(button->getToggleState());
    }
    else if(button == &clearSequencer)
    {
        clearButtons();
    }
    else
    {
        button->setToggleState(!button->getToggleState(), dontSendNotification);
        
        for(int drum = 0; drum < NUM_DRUMS; drum++)
            for(int step = 0; step < MAX_STEPS; step++)
                if(button == &sequencerButton[drum][step])
                    audio.sequencer.setStep(button->getToggleState(), drum, step);
    }
}

void SequencerWidget::sliderValueChanged (Slider* slider)
{
    audio.sequencer.setBPM(slider->getValue());
}

//========================== Graphic Functions ================================

void SequencerWidget::paint (Graphics& g)
{
    // Basic Windows
    g.setColour(Colour(0xff999999));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 10);
    g.setColour(Colour(0xff33333a));
    g.fillRoundedRectangle(rWindow, 4);
    
    // Widget Name
    g.setColour(Colour(0xff33333a));
    g.setFont(20);
    g.drawText("Sequencer", 12, 3, getWidth() - 6, 15, Justification::centredLeft);
    
    // Border
    g.setColour(Colours::black);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 10, 3);
    
    // Sequencer Background
    g.setColour(Colour(0xff395244));
    g.fillRect(sequencerWindow);
    
    // Sequencer Grid Lines
    g.setColour(Colours::black);
    for(int c = 0; c < numDrums + 1; c++)
        g.drawLine(sequencerWindow.getX(),
                   sequencerWindow.getY() + (c * buttonHeight),
                   sequencerWindow.getRight(),
                   sequencerWindow.getY() + (c * buttonHeight),
                   1);
    for(int l = 0; l < numSteps + 1; l++)
    {
        g.setColour(Colours::black);
        g.setOpacity(1.f);
        g.drawLine(sequencerWindow.getX() + (l * buttonWidth),
                   sequencerWindow.getY(),
                   sequencerWindow.getX() + (l * buttonWidth),
                   sequencerWindow.getBottom(),
                   1);
        
        if(l % 4 == 0 && l < numSteps)
        {
            g.setColour(Colours::white);
            g.setOpacity(0.08);
            g.fillRect(sequencerWindow.getX() + (l* buttonWidth),
                       sequencerWindow.getY(),
                       buttonWidth,
                       sequencerWindow.getHeight());
        }
    }
    
    // Drum and Step names/nums
    g.setColour(Colour(0xff999999));
    g.setFont(15);
    for(int c = 0; c < numDrums; c++)
        g.drawText(drumNames[c],
                   sequencerWindow.getX() - (rWindow.getWidth() / 9),
                   sequencerWindow.getY() + (c * buttonHeight),
                   (rWindow.getWidth() / 9) - 4,
                   buttonHeight,
                   Justification::centredRight);
    for(int l = 0; l < numSteps; l++)
        g.drawText(String(l + 1),
                   sequencerWindow.getX() + (l * buttonWidth),
                   sequencerWindow.getY() - 24,
                   buttonWidth,
                   24,
                   Justification::centred);
    
}

void SequencerWidget::resized()
{

    // Rectangle Areas
    rWindow.setBounds(6, 21, getWidth() - 12, getHeight() - 27);
    sequencerWindow.setBounds(rWindow.getWidth() / 5.5,
                              rWindow.getY() + 24,
                              (rWindow.getWidth() * 0.80),
                              rWindow.getHeight() * 0.65);
    
    updateSequencer();
}

void SequencerWidget::playbackPosControl()
{
    
}

void SequencerWidget::setPlaybackButtonState(bool isOn)
{
    playButton.setToggleState(isOn, dontSendNotification);
}

void SequencerWidget::updateSequencer() // Cleaning and fixing this
{
    // Re-position sequencer buttons
    buttonWidth = sequencerWindow.getWidth() / MAX_STEPS;
    buttonHeight = sequencerWindow.getHeight() / NUM_DRUMS;
    
    float stepButtonWidth = sequencerWindow.getWidth() / 12;
    BPMSlider.setBounds(sequencerWindow.getX(),
                        sequencerWindow.getBottom() + 4,
                        buttonWidth * 8,
                        buttonHeight);
    
    playButton.setBounds(sequencerWindow.getX(),
                         sequencerWindow.getBottom() + (BPMSlider.getHeight() * 2),
                         getWidth() / 1.5,
                         buttonHeight * 2);
    
    clearSequencer.setBounds(sequencerWindow.getRight() - ((sequencerWindow.getWidth() / 2) +(buttonWidth * 4)),
                             sequencerWindow.getBottom() + 4,
                             buttonWidth * 8,
                             buttonHeight);
    
    // Re-position sequencer buttons
    buttonWidth = sequencerWindow.getWidth() / numSteps;
    buttonHeight = sequencerWindow.getHeight() / numDrums;

    // Clear ALL sequencer buttons
    for(int c = 0; c < numDrums; c++)
        for(int l = 0; l < MAX_STEPS; l++)
            sequencerButton[c][l].setVisible(false);
    
    // Make wanted buttons visable again
    for(int c = 0; c < numDrums; c++)
        for(int l = 0; l < numSteps; l++)
        {
            sequencerButton[c][l].setVisible(true);
            sequencerButton[c][l].setBounds(sequencerWindow.getX() + (l * buttonWidth),
                                            sequencerWindow.getY() + (c * buttonHeight),
                                            buttonWidth + 2,
                                            buttonHeight + 2);
        }
    
    // Position stepnum select
    for(int c = 0; c < 3; c++)
        numStepsSelect[c].setBounds(sequencerWindow.getRight() - ((c + 1) * stepButtonWidth),
                                    sequencerWindow.getBottom() + 4,
                                    stepButtonWidth,
                                    buttonHeight);
    
    // Position drum mute buttons
    for(int c = 0; c < numDrums; c++)
        muteButton[c].setBounds(10,
                                sequencerWindow.getY() + (buttonHeight / 4) + (c * buttonHeight),
                                (rWindow.getWidth() / 9) / 2,
                                buttonHeight / 1.5);
    
}

void SequencerWidget::clearButtons()
{
    for(int c = 0; c < numDrums; c++)
        for(int l = 0; l < MAX_STEPS; l++)
        {
            sequencerButton[c][l].setToggleState(false, dontSendNotification);
            audio.sequencer.setStep(false, c, l);
        }
}
