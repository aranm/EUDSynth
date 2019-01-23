// James Measey 14002897: 2016-17

#include "ControlPage.h"
//======================== Constructer/Destructer =============================
ControlPage::ControlPage(AudioControl& audio)
 :  audio(audio)
{
    for(int c = 0; c < 2; c++)
        for(int i = 0; i < 12; i++)
        {
            addAndMakeVisible(sControl[i][c]);
            sControl[i][c].setSliderStyle(Slider::Rotary);
            sControl[i][c].setColour(Slider::rotarySliderFillColourId, Colour(0xff999999));
            sControl[i][c].setColour(Slider::rotarySliderOutlineColourId, Colours::seagreen);
            sControl[i][c].setColour(Slider::textBoxOutlineColourId, Colours::seagreen);
            sControl[i][c].setColour(Slider::textBoxBackgroundColourId, Colours::transparentBlack);
            sControl[i][c].setColour(Slider::textBoxTextColourId, Colours::whitesmoke);
            sControl[i][c].addListener(this);
        }
    
    buildIndividualControls();
    
    for(int i = 0; i < 12; i++)
    {
        addAndMakeVisible(sControl[i][2]);
        sControl[i][2].setSliderStyle(Slider::LinearBar);
        sControl[i][2].setColour(Slider::trackColourId, Colour(0xff739cc4));
        sControl[i][2].setColour(Slider::thumbColourId, Colour(0xff999999));
        sControl[i][2].setColour(Slider::textBoxTextColourId, Colours::whitesmoke);
        sControl[i][2].setTextValueSuffix(" Level");
        sControl[i][2].setRange(0.f, 1.f, 0.05);
        sControl[i][2].setTextBoxIsEditable(false);
        sControl[i][2].addListener(this);
        
        addAndMakeVisible(setDefault[i]);
        setDefault[i].addListener(this);
        setDefault[i].setColour(TextButton::buttonColourId, Colour(0xff999999));
        setDefault[i].setButtonText("Default");
    }
    
    
}
ControlPage::~ControlPage()
{
    
}

//======================= Button / State Functions ============================

void ControlPage::buttonClicked (Button* button)
{
    for(int i = 0; i < 12; i++)
        if(&setDefault[i] == button)
            setControlToDefault(i);
}

void ControlPage::sliderValueChanged(Slider* slider)
{
    for(int i = 0; i < 12; i++)
        for(int c = 0; c < 3; c++)
        {
            if(slider == &sControl[i][c])
            {
                //Two seperate drum controllers need changing
                audio.drumController.alter(i,
                                           sControl[i][0].getValue(),
                                           sControl[i][1].getValue(),
                                           sControl[i][2].getValue());
                
                audio.sequencer.drumController.alter(i,
                                                     sControl[i][0].getValue(),
                                                     sControl[i][1].getValue(),
                                                     sControl[i][2].getValue());
            }
        }
}

//========================== Graphic Functions ================================

void ControlPage::paint (Graphics& g)
{
    Rectangle<float> thisWidget;
        
    int count = 0;
    int nameCount = 0;
    g.setColour(Colours::black);
    for(int i = 0; i < 4; i++)
        for(int row = 0; row < 3; row++)
        {
            g.setColour(Colour(0xff999999));
            g.fillRoundedRectangle(drumWidget[count], 10);
            
            g.setColour(Colour(0xff33333a));
            g.fillRoundedRectangle(drumWidget[count].withTrimmedBottom(15).reduced(5, 5), 4);
            
            // Widget Name
            g.setColour(Colour(0xff33333a));
            g.setFont(20);
            g.drawText(drumNames[count], drumWidget[count].getX(),
                       drumWidget[count].getBottom() - 20, drumWidget[count].getWidth(),
                       20, Justification::centred);
            
            g.setColour(Colour(0xff999999));
            g.setFont(15);
            for(int c = 0; c < 2; c++)
            {
                g.drawText(controlNames[nameCount], sControl[count][c].getX(),
                           sControl[count][c].getBottom() - 10,
                           sControl[count][c].getWidth(),
                           20,
                           Justification::centred);
                nameCount++;
            }
            count++;
        }
}

void ControlPage::resized()
{
    float widgetWidth = getWidth() / 4;
    float widgetHeight = getHeight() / 3;
    
    float buttonWidth;
    float buttonHeight;
    float spaceBetween;

    int count = 0;
    
    for(int col = 0; col < 4; col++)
        for(int row = 0; row < 3; row++)
        {
            drumWidget[count] = Rectangle<float>(1.5 + (widgetWidth * col),
                                                 1.5 + (widgetHeight * row),
                                                 widgetWidth - 3,
                                                 widgetHeight - 3);
            
            buttonWidth = drumWidget[count].withTrimmedBottom(15).reduced(5).getWidth() / 2.5;
            buttonHeight = drumWidget[count].withTrimmedBottom(15).reduced(5).getHeight() / 1.75;
            spaceBetween = buttonWidth / 6;
            
            for(int i = 0; i < 2; i++)
            {
                sControl[count][i].setBounds((drumWidget[count].withTrimmedBottom(15).reduced(5).getX() +spaceBetween) + ((buttonWidth +spaceBetween) * i),
                                             drumWidget[count].withTrimmedBottom(15).reduced(5).getY() + 10,
                                             buttonWidth,
                                             buttonHeight);
                
                sControl[count][i].setTextBoxStyle(Slider::TextBoxAbove, false,
                                                   buttonWidth - 30,
                                                   15);
            }
            
            sControl[count][2].setBounds(drumWidget[count].withTrimmedBottom(15).reduced(5).getX() +spaceBetween,
                                         drumWidget[count].withTrimmedBottom(15).reduced(5).getBottom() -(buttonHeight / 2),
                                         (buttonWidth * 2) +(buttonWidth / 6),
                                         buttonHeight / 4);
            
            setDefault[count].setBounds(sControl[count][2].getX() +sControl[count][2].getWidth() / 4,
                                        drumWidget[count].withTrimmedBottom(15).reduced(5).getBottom() -((buttonHeight / 6) + 5),
                                        sControl[count][2].getWidth() / 2,
                                        buttonHeight / 6);
            
            count++;
        }
}

void ControlPage::buildIndividualControls()
{
    //Bass
    sControl[0][0].setRange(0.1, 2.0, 0.01);
    sControl[0][0].setTextValueSuffix("sec");
    sControl[0][0].setSkewFactor(0.4);
    sControl[0][1].setRange(35, 120, 0.01);
    sControl[0][1].setTextValueSuffix("Hz");
    sControl[0][1].setSkewFactor(0.5);
    
    //Kick
    sControl[1][0].setRange(0.01, 1.0, 0.01);
    sControl[1][0].setTextValueSuffix("sec");
    sControl[1][0].setSkewFactor(0.3);
    sControl[1][1].setRange(35, 100, 0.1);
    sControl[1][1].setTextValueSuffix("Hz");
    sControl[1][1].setSkewFactor(0.3);
    
    //Rimshot
    sControl[2][0].setRange(0.001, 0.05, 0.001);
    sControl[2][0].setTextValueSuffix("sec");
    sControl[2][1].setRange(150, 600, 1.f);
    sControl[2][1].setTextValueSuffix("Hz");
    sControl[2][1].setSkewFactor(0.4);
    
    //Snare
    sControl[3][0].setRange(1000.f, 8000.f, 1.f);
    sControl[3][0].setTextValueSuffix("Hz");
    sControl[3][0].setSkewFactor(0.3);
    sControl[3][1].setRange(125, 500, 1.f);
    sControl[3][1].setTextValueSuffix("Hz");
    sControl[3][1].setSkewFactor(0.3);
    
    //Clap
    sControl[4][0].setRange(0.05, 1.f, 0.01f);
    sControl[4][0].setTextValueSuffix("sec");
    sControl[4][0].setSkewFactor(0.5);
    sControl[4][1].setRange(600, 8000, 1.f);
    sControl[4][1].setTextValueSuffix("Hz");
    sControl[4][1].setSkewFactor(0.3);
    
    //Cowbell
    sControl[5][0].setRange(0.05, 3.f, 0.01f);
    sControl[5][0].setTextValueSuffix("sec");
    sControl[5][0].setSkewFactor(0.5);
    sControl[5][1].setRange(300.f, 800.f, 1.f);
    sControl[5][1].setTextValueSuffix("Hz");
    sControl[5][1].setSkewFactor(0.6);
    
    //Low Tom
    sControl[6][0].setRange(0.1, 1.f, 0.01);
    sControl[6][0].setTextValueSuffix("sec");
    sControl[6][1].setRange(0.0, 1.f, 0.01);
    sControl[6][1].setSkewFactor(0.5);
    
    //Closed hat
    sControl[7][0].setRange(5000.f, 12000.f, 0.1);
    sControl[7][0].setTextValueSuffix("Hz");
    sControl[7][1].setSkewFactor(0.5);
    sControl[7][1].setRange(0.01, 0.2, 0.001);
    
    //Mid Tom
    sControl[8][0].setRange(0.1, 1.f, 0.01);
    sControl[8][0].setTextValueSuffix("sec");
    sControl[8][1].setSkewFactor(0.5);
    sControl[8][1].setRange(0.0, 1.f, 0.01);
    
    //Cymbal
    sControl[9][0].setRange(5000.f, 11000.f, 0.1);
    sControl[9][0].setTextValueSuffix("Hz");
    sControl[9][1].setSkewFactor(0.4);
    sControl[9][1].setRange(0.3, 1.5, 0.01);
    
    //High Tom
    sControl[10][0].setRange(0.1, 1.f, 0.01);
    sControl[10][0].setTextValueSuffix("sec");
    sControl[10][1].setSkewFactor(0.5);
    sControl[10][1].setRange(0.0, 1.f, 0.01);
    
    //Open hat
    sControl[11][0].setRange(3000.f, 8000.f, 0.1);
    sControl[11][0].setTextValueSuffix("Hz");
    sControl[11][1].setSkewFactor(0.5);
    sControl[11][1].setRange(0.1, 0.5, 0.01);
    
    
    for(int i = 0; i < 12; i++)
        setControlToDefault(i);
}

void ControlPage::setControlToDefault(int drumNum)
{
    if(drumNum == 0)
    {
        sControl[drumNum][0].setValue(0.2);
        sControl[drumNum][1].setValue(60.f);
        sControl[drumNum][2].setValue(0.8);
    }
    else if(drumNum == 1)
    {
        sControl[drumNum][0].setValue(0.1);
        sControl[drumNum][1].setValue(70.f);
        sControl[drumNum][2].setValue(0.8);
    }
    else if(drumNum == 2)
    {
        sControl[drumNum][0].setValue(0.01);
        sControl[drumNum][1].setValue(300.f);
        sControl[drumNum][2].setValue(0.8);
    }
    else if(drumNum == 3)
    {
        sControl[drumNum][0].setValue(3000.f);
        sControl[drumNum][1].setValue(250.f);
        sControl[drumNum][2].setValue(0.8);
    }
    else if(drumNum == 4)
    {
        sControl[drumNum][0].setValue(0.15);
        sControl[drumNum][1].setValue(1000.f);
        sControl[drumNum][2].setValue(0.8);
    }
    else if(drumNum == 5)
    {
        sControl[drumNum][0].setValue(0.15);
        sControl[drumNum][1].setValue(540.f);
        sControl[drumNum][2].setValue(0.8);
    }
    else if(drumNum == 6)
    {
        sControl[drumNum][0].setValue(0.3);
        sControl[drumNum][1].setValue(0.1);
        sControl[drumNum][2].setValue(0.8);
    }
    else if(drumNum == 7)
    {
        sControl[drumNum][0].setValue(7000.f);
        sControl[drumNum][1].setValue(0.05);
        sControl[drumNum][2].setValue(0.8);
    }
    else if(drumNum == 8)
    {
        sControl[drumNum][0].setValue(0.3);
        sControl[drumNum][1].setValue(0.1);
        sControl[drumNum][2].setValue(0.8);
    }
    else if(drumNum == 9)
    {
        sControl[drumNum][0].setValue(8000.f);
        sControl[drumNum][1].setValue(0.7);
        sControl[drumNum][2].setValue(0.8);
    }
    else if(drumNum == 10)
    {
        sControl[drumNum][0].setValue(0.3);
        sControl[drumNum][1].setValue(0.1);
        sControl[drumNum][2].setValue(0.8);
    }
    else if(drumNum == 11)
    {
        sControl[drumNum][0].setValue(5000.f);
        sControl[drumNum][1].setValue(0.2);
        sControl[drumNum][2].setValue(0.8);
    }
    
    sliderValueChanged(&sControl[drumNum][0]);
    sliderValueChanged(&sControl[drumNum][1]);
    sliderValueChanged(&sControl[drumNum][2]);
    
}

