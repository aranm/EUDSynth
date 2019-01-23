// James Measey 14002897: 2016-17

#include "PlayPage.h"
//======================== Constructer/Destructer =============================
PlayPage::PlayPage(AudioControl& audio)
 :  audio(audio),
    keyboard(audio),
    sequencer(audio),
    masterWidget(audio)
{
    addAndMakeVisible(sequencer);
    addAndMakeVisible(keyboard);
    addAndMakeVisible(masterWidget);
}
PlayPage::~PlayPage()
{
    
}

//========================== Graphic Functions ================================

void PlayPage::paint (Graphics& g)
{
    
}

void PlayPage::resized()
{
    keyboard.setBounds(getLocalBounds().toNearestInt()
                       .removeFromBottom(getLocalBounds().getHeight() / 3.5)
                       .withTrimmedLeft(getLocalBounds().getWidth() / 5));
    
    sequencer.setBounds(getLocalBounds().toNearestInt()
                        .withTrimmedLeft(getLocalBounds().getWidth() / 5)
                        .withTrimmedBottom(getLocalBounds().getHeight() / 3.5));
    
    masterWidget.setBounds(getLocalBounds().toNearestInt()
                           .removeFromLeft(getLocalBounds().getWidth() / 5));
}
