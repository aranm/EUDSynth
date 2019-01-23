// James Measey 14002897: 2016-17

#include "MainComponent.h"
//======================== Constructer/Destructer =============================

MainContentComponent::MainContentComponent (AudioControl& audio)
 :  audio(audio),
    playPage(audio),
    controlPage(audio)
{
    setSize(900, 700);
    
    addChildComponent(playPage);
    addChildComponent(controlPage);
    
    addAndMakeVisible(playPagebutton);
    playPagebutton.setButtonText("Play");
    playPagebutton.setColour(TextButton::buttonColourId,
                                Colour(0xff999999));
    playPagebutton.setColour(TextButton::buttonOnColourId,
                             Colours::forestgreen);
    playPagebutton.setConnectedEdges(2);
    playPagebutton.setRadioGroupId(1, dontSendNotification);
    playPagebutton.addListener(this);
    
    addAndMakeVisible(controlPagebutton);
    controlPagebutton.setButtonText("Controls");
    controlPagebutton.setColour(TextButton::buttonColourId,
                             Colour(0xff999999));
    controlPagebutton.setColour(TextButton::buttonOnColourId,
                                Colours::forestgreen);
    controlPagebutton.setConnectedEdges(1);
    controlPagebutton.setRadioGroupId(1, dontSendNotification);
    controlPagebutton.addListener(this);
    
    buttonClicked(&playPagebutton);
    
    addKeyListener(this);
}

MainContentComponent::~MainContentComponent()
{
}

//======================= Button / State Functions ============================

void MainContentComponent::buttonClicked (Button* button)
{
    if (button == &playPagebutton)
    {
        playPage.setVisible(true);
        controlPage.setVisible(false);
        button->setToggleState(true, dontSendNotification);
    }
    if (button == &controlPagebutton)
    {
        playPage.setVisible(false);
        controlPage.setVisible(true);
        button->setToggleState(true, dontSendNotification);
    }
}

bool MainContentComponent::keyPressed(const KeyPress &key, Component *originatingComponent)
{
    
    if(key.getKeyCode() == 32)
    {

        audio.sequencer.setPlaybackState(!audio.sequencer.getPlaybackState());
        playPage.sequencer.setPlaybackButtonState(audio.sequencer.getPlaybackState());
    }
    else if(key.getKeyCode() == 63234)
    {
        if(!playPagebutton.getToggleState())
        {
            playPage.setVisible(true);
            controlPage.setVisible(false);
            playPagebutton.setToggleState(true, dontSendNotification);
        }
    }
    else if(key.getKeyCode() == 63235)
    {
        if(!controlPagebutton.getToggleState())
        {
            controlPage.setVisible(true);
            playPage.setVisible(false);
            controlPagebutton.setToggleState(true, dontSendNotification);
        }
    }
    else if(key.getKeyCode() == 127)
    {
        playPage.sequencer.clearButtons();
    }

    return 0;
}

//========================== Graphic Functions ================================

void MainContentComponent::paint (Graphics& g)
{
    // Draw Basic Window
    g.fillAll (Colour(0xff395244));
    g.setColour(Colours::black);
    g.fillRoundedRectangle(mainView, 10);
    
    // Draw Borders
    g.drawRoundedRectangle(mainView, 10, 3);
    g.drawRect(0, 0, getWidth(), getHeight(), 3);
    
    // Name Plate
    g.fillRoundedRectangle(namePlate, 15);
    g.setColour(Colours::lightgrey);
    g.setFont(18);
    g.drawText("E U  :  D r u m  S y n t h",
               getWidth() / 3, 0, getWidth() / 3, 25,
               Justification::centred);
}

void MainContentComponent::resized()
{
    playPagebutton.setBounds(getWidth() / 3, 32, getWidth() / 6, 30);
    controlPagebutton.setBounds((getWidth() / 3) + getWidth() / 6, 32, getWidth() / 6, 30);
    
    mainView.setBounds(8, 70, getWidth() - 16, getHeight() - 78);
    
    controlPage.setBounds(mainView.toNearestInt());
    playPage.setBounds(mainView.toNearestInt());
    
    namePlate.setBounds(getWidth() / 3, -25, getWidth() / 3, 50);    
}

