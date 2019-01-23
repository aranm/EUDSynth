// James Measey 14002897: 2016-17
#include "DrumController.h"

DrumController::DrumController() {}
DrumController::~DrumController() {}

float DrumController::play()
{
    float sample = 0.f;
    
    for(int voice = 0; voice < 2; voice++)
    {
        if(bass[voice].isAudioPlaying())    sample += bass[voice].play();
        if(kick[voice].isAudioPlaying())    sample += kick[voice].play();
        if(snare[voice].isAudioPlaying())   sample += snare[voice].play();
        if(loTom[voice].isAudioPlaying())   sample += loTom[voice].play();
        if(miTom[voice].isAudioPlaying())   sample += miTom[voice].play();
        if(hiTom[voice].isAudioPlaying())   sample += hiTom[voice].play();
        
        if(clHat[voice].isAudioPlaying())   sample += clHat[voice].play();
        if(opHat[voice].isAudioPlaying())   sample += opHat[voice].play();
        if(cymbal[voice].isAudioPlaying())  sample += cymbal[voice].play();
        if(rimshot[voice].isAudioPlaying()) sample += rimshot[voice].play();
        if(clap[voice].isAudioPlaying())    sample += clap[voice].play();
        if(cowbell[voice].isAudioPlaying()) sample += cowbell[voice].play();
    }
    
    return sample;
}

void DrumController::alter(int drumNum, float control1, float control2, float gain)
{
    if(drumNum == 0)
    {
        bass[0].alter(control1, control2, gain);
        bass[1].alter(control1, control2, gain);
    }
    else if(drumNum == 1)
    {
        kick[0].alter(control1, control2, gain);
        kick[1].alter(control1, control2, gain);
    }
    else if(drumNum == 2)
    {
        rimshot[0].alter(control1, control2, gain);
        rimshot[1].alter(control1, control2, gain);
    }
    else if(drumNum == 3)
    {
        snare[0].alter(control1, control2, gain);
        snare[1].alter(control1, control2, gain);
    }
    else if(drumNum == 4)
    {
        clap[0].alter(control1, control2, gain);
        clap[1].alter(control1, control2, gain);
    }
    else if(drumNum == 5)
    {
        cowbell[0].alter(control1, control2, gain);
        cowbell[1].alter(control1, control2, gain);
    }
    else if(drumNum == 6)
    {
        loTom[0].alter(control1, control2, gain);
        loTom[1].alter(control1, control2, gain);
    }
    else if(drumNum == 7)
    {
        clHat[0].alter(control1, control2, gain);
        clHat[1].alter(control1, control2, gain);
    }
    else if(drumNum == 8)
    {
        miTom[0].alter(control1, control2, gain);
        miTom[1].alter(control1, control2, gain);
    }
    else if(drumNum == 9)
    {
        cymbal[0].alter(control1, control2, gain);
        cymbal[1].alter(control1, control2, gain);
    }
    else if(drumNum == 10)
    {
        hiTom[0].alter(control1, control2, gain);
        hiTom[1].alter(control1, control2, gain);
    }
    else if(drumNum == 11)
    {
        opHat[0].alter(control1, control2, gain);
        opHat[1].alter(control1, control2, gain);
    }
}

void DrumController::start(int note)
{
    if(note == 59) {
        if(bass[0].isAudioPlaying() && bass[0].isAudioPrepared()) {
            bass[1].start();
            bass[0].quickFadeOut();
        }
        else {
            bass[0].start();
            bass[1].quickFadeOut();
        }
    }
    else if(note == 60) {
        if(kick[0].isAudioPlaying() && kick[0].isAudioPrepared()) {
            kick[1].start();
            kick[0].quickFadeOut();
        }
        else {
            kick[0].start();
            kick[1].quickFadeOut();
        }
    }
    else if(note == 61) {
        if(cowbell[0].isAudioPlaying() && cowbell[0].isAudioPrepared()) {
            rimshot[1].start();
            rimshot[0].quickFadeOut();
        }
        else {
            rimshot[0].start();
            rimshot[1].quickFadeOut();
        }
    }
    else if(note == 62) {
        if(snare[0].isAudioPlaying() && snare[0].isAudioPrepared()) {
            snare[1].start();
            snare[0].quickFadeOut();
        }
        else {
            snare[0].start();
            snare[1].quickFadeOut();
        }
    }
    else if(note == 63) {
        if(clap[0].isAudioPlaying() && clap[0].isAudioPrepared()) {
            clap[1].start();
            clap[0].quickFadeOut();
        }
        else {
            clap[0].start();
            clap[1].quickFadeOut();
        }
    }
    else if(note == 64) {
        if(rimshot[0].isAudioPlaying() && rimshot[0].isAudioPrepared()) {
            cowbell[1].start();
            cowbell[0].quickFadeOut();
        }
        else {
            cowbell[0].start();
            cowbell[1].quickFadeOut();
        }
    }
    else if(note == 65) {
        if(loTom[0].isAudioPlaying() && loTom[0].isAudioPrepared()) {
            loTom[1].start();
            loTom[0].quickFadeOut();
        }
        else {
            loTom[0].start();
            loTom[1].quickFadeOut();
        }
    }
    else if(note == 66) {
        if(clHat[0].isAudioPlaying() && clHat[0].isAudioPrepared()) {
            clHat[1].start();
            clHat[0].quickFadeOut();
        }
        else {
            clHat[0].start();
            clHat[1].quickFadeOut();
        }
    }
    else if(note == 67) {
        if(miTom[0].isAudioPlaying() && miTom[0].isAudioPrepared()) {
            miTom[1].start();
            miTom[0].quickFadeOut();
        }
        else {
            miTom[0].start();
            miTom[1].quickFadeOut();
        }
    }
    else if(note == 68) {
        if(cymbal[0].isAudioPlaying() && cymbal[0].isAudioPrepared()) {
            cymbal[1].start();
            cymbal[0].quickFadeOut();
        }
        else {
            cymbal[0].start();
            cymbal[1].quickFadeOut();
        }
    }
    else if(note == 69) {
        if(hiTom[0].isAudioPlaying() && hiTom[0].isAudioPrepared()) {
            hiTom[1].start();
            hiTom[0].quickFadeOut();
        }
        else {
            hiTom[0].start();
            hiTom[1].quickFadeOut();
        }
    }
    else if(note == 70) {
        if(opHat[0].isAudioPlaying() && opHat[0].isAudioPrepared()) {
            opHat[1].start();
            opHat[0].quickFadeOut();
        }
        else {
            opHat[0].start();
            opHat[1].quickFadeOut();
        }
    }
}

void DrumController::prepare(int note)
{
    if(note == 59) {
        bass[0].prepare();
        bass[1].prepare();
    }
    else if(note == 60) {
        kick[0].prepare();
        kick[1].prepare();
    }
    else if(note == 61) {
        rimshot[0].prepare();
        rimshot[1].prepare();
    }
    else if(note == 62) {
        snare[0].prepare();
        snare[1].prepare();
    }
    else if(note == 63) {
        clap[0].prepare();
        clap[1].prepare();
    }
    else if(note == 64) {
        cowbell[0].prepare();
        cowbell[1].prepare();
    }
    else if(note == 65) {
        loTom[0].prepare();
        loTom[1].prepare();
    }
    else if(note == 66) {
        clHat[0].prepare();
        clHat[1].prepare();
    }
    else if(note == 67) {
        miTom[0].prepare();
        miTom[1].prepare();
    }
    else if(note == 68) {
        cymbal[0].prepare();
        cymbal[1].prepare();
    }
    else if(note == 69) {
        hiTom[0].prepare();
        hiTom[1].prepare();
    }
    else if(note == 70) {
        opHat[0].prepare();
        opHat[1].prepare();
    }
}
