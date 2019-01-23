// James Measey 14002897: 2016-17

#include "SynthDrum.h"

//============================== SynthDrums ===================================
SynthDrum::SynthDrum()
:   isPlaying(false),
    isPrepared(true),
    isFadeOut(false),
    gainLevel(0.8),
    fadeOut(1.f)
{}
SynthDrum::~SynthDrum() {}

void SynthDrum::start()
{
    if (isPrepared)
    {
        ampEnv.startEnv();
        for(int i = 0; i < 5; i++)
            env[i].startEnv();
        
        isPrepared = false;
        isPlaying = true;
        isFadeOut = false;
        fadeOut = 1.f;
    }
}

void SynthDrum::prepare()
{
    isPrepared = true;
}

void SynthDrum::quickFadeOut()
{
    isFadeOut = true;
}

bool SynthDrum::isAudioPlaying()
{
    return isPlaying;
}

bool SynthDrum::isAudioPrepared()
{
    return isPrepared;
}

float SynthDrum::variableCompresser(float sample, float ratio, float threshold)
{
    assert (ratio > 1.f); //Must be more than 1
    
    float absVal;
    if(sample < 0)  absVal = sample * -1;
    else            absVal = sample;
    
    if(absVal > threshold)
    {
        if(sample < 0)  sample = -1 * (threshold + ((absVal - threshold) / ratio));
        else            sample = (threshold + ((absVal - threshold) / ratio));
    }
    
    return sample;
}

void SynthDrum::alterGain(float gain)
{
    gainLevel = gain;
}
//============================== Bass Drum ====================================
BassSynth::BassSynth()
:   ampDecay(0.2),
    freq(60.f)
{
    mixLevel = 1.0;
    
    // FILTERS
    filter[0].setCoefficients(IIRCoefficients::makeHighPass(44100, 30));
    filter[1].setCoefficients(IIRCoefficients::makeHighShelf(44100, 500, 1.0 / std::sqrt (2.0), 0.05));
}
BassSynth::~BassSynth() {}

void BassSynth::alter(float drumLength, float drumFreq, float gain)
{
    freq = drumFreq;
    ampDecay = drumLength;
    alterGain(gain);
}

float BassSynth::play()
{
    float sample = 0;
    
    if(isPlaying)
    {
        amplitude = ampEnv.ADSR(0.01, ampDecay, 0.005, 0.3, 0.2);
        frequency = env[0].pointToPoint(0.0, freq * 4, 0.005, freq, 0.05, freq * 0.66, 0.5, freq * 0.5);
        
        float noiseOsc = osc[0].getNoise(amplitude * 0.1);
        noiseOsc = filter[1].processSingleSampleRaw(noiseOsc);
        
        sample = ((osc[1].getSine(frequency, amplitude) +
                   osc[2].getSquare(frequency, amplitude) +
                   noiseOsc) * 0.5);
        
        sample = filter[0].processSingleSampleRaw(sample);
        
        if(isFadeOut)
        {
            fadeOut -= 1.f / (0.1* 44100.f);
            
            if(fadeOut <= 0)
            {
                fadeOut = 0.f;
            }
        }
    }
    
    isPlaying = ampEnv.getEnvPlaying();
    sample = variableCompresser(sample, 5.0, 0.85);
    return ((sample * fadeOut) * gainLevel) * mixLevel;
}

//============================== Kick Drum ====================================
KickSynth::KickSynth()
:   freq(70.f),
    decayChange(0.1)
{
    mixLevel = 1.0;
    
    // FILTERS
    filter[0].setCoefficients(IIRCoefficients::makeHighPass(44100, 30));
    filter[1].setCoefficients(IIRCoefficients::makeHighShelf(44100, 500, 1.0 / std::sqrt (2.0), 0.05));
}
KickSynth::~KickSynth() {}

void KickSynth::alter(float drumLength, float drumFreq, float gain)
{
    freq = drumFreq;
    decayChange = drumLength;
    alterGain(gain);
}

float KickSynth::play()
{
    float sample = 0;
    
    if(isPlaying)
    {
        amplitude = ampEnv.ADSR(0.001, decayChange, 0.005, 0.15, 0.1);
        frequency = env[0].pointToPoint(0.0, freq*10, 0.005, freq, 0.05, freq*0.7, 0.05, freq*0.6);
        
        
        float noiseEnv = env[1].ADSR(0.005, 0.04, 0.001, 0.1, 0.03);
        float noiseOsc = osc[2].getNoise(noiseEnv * 0.3);
        noiseOsc = filter[1].processSingleSampleRaw(noiseOsc);
        
        sample = ((osc[0].getSine(frequency, amplitude) +
                  osc[1].getSquare(frequency, amplitude) +
                  noiseOsc) * 0.5);
        
        sample = filter[0].processSingleSampleRaw(sample);
        
        if(isFadeOut)
        {
            fadeOut -= 1.f / (0.1* 44100.f);
            
            if(fadeOut <= 0)
            {
                fadeOut = 0.f;
            }
        }
    }
    
    isPlaying = ampEnv.getEnvPlaying();
    sample = variableCompresser(sample, 5.0, 0.85);
    return ((sample * fadeOut) * gainLevel) * mixLevel;
}

//============================== Snare Drum ===================================
SnareSynth::SnareSynth()
:   freq(250)
{
    mixLevel = 0.6f;
    
    // FILTERS
    filter[0].setCoefficients(IIRCoefficients::makeHighPass(44100, 3000));
}
SnareSynth::~SnareSynth() {}

void SnareSynth::alter(float rattle, float drumFreq, float gain)
{
    filter[0].setCoefficients(IIRCoefficients::makeHighPass(44100, rattle));
    freq = drumFreq;
    alterGain(gain);
}

float SnareSynth::play()
{
    float sample = 0;

    if(isPlaying)
    {
        amplitude = env[1].ADSR(0.001, 0.015, 0.001, 0.11, 0.95);
        frequency = env[0].pointToPoint(0.0, 2000, 0.005, freq * 1.7, 0.008, freq, 0.001, freq);
        
        sample = osc[0].getSquare(frequency, amplitude / 10) + osc[1].getSine(frequency, amplitude);
        
        float noiseEnv = ampEnv.ADSR(0.005, 0.12, 0.001, 0.1, 0.05);
        float noise = osc[2].getNoise(noiseEnv);
        noise = filter[0].processSingleSampleRaw(noise);
        
        sample = (sample / 3) + noise;
        
        if(isFadeOut)
        {
            fadeOut -= 1.f / (0.1 * 44100.f);
            
            if(fadeOut <= 0)
            {
                fadeOut = 0.f;
            }
        }
    }
    
    isPlaying = ampEnv.getEnvPlaying();
    
    sample = variableCompresser(sample, 3.0, 0.8);
    return ((sample * fadeOut) * gainLevel) * mixLevel;
}

//=============================== Low Tom ====================================
LowTomSynth::LowTomSynth()
 :  decay(0.3),
    noiseLevel(0.01)
{
    mixLevel = 0.6;
    
    filter[0].setCoefficients(IIRCoefficients::makeHighPass(44100, 40));
}
LowTomSynth::~LowTomSynth() {}

void LowTomSynth::alter(float drumLength, float airLevel, float gain)
{
    decay = drumLength;
    noiseLevel = airLevel / 10;
    alterGain(gain);
}

float LowTomSynth::play()
{
    float sample = 0;
    
    if(isPlaying)
    {
        amplitude = ampEnv.ADSR(0.001, decay, 0.001, 0.001, 0.001);
        frequency = env[0].pointToPoint(0.0, 90, 0.5, 40, 0.001, 40, 0.001, 40);
        
        sample = osc[0].getSine(frequency, amplitude) + osc[1].getSine(frequency * 2, amplitude);
        
        float noiseEnv = env[1].ADSR(0.001, 0.4, 0.001, 0.001, 0.001);
        float noise = osc[2].getNoise(noiseEnv * noiseLevel);
        
        sample = (sample + noise) / 1.5;
        
        sample = filter[0].processSingleSampleRaw(sample);
        
        if(isFadeOut)
        {
            fadeOut -= 1.f / (0.1 * 44100.f);
            
            if(fadeOut <= 0)
            {
                fadeOut = 0.f;
            }
        }
    }
    
    isPlaying = ampEnv.getEnvPlaying();
    
    sample = variableCompresser(sample, 2.0, 0.8);
    return ((sample * fadeOut) * gainLevel) * mixLevel;
}

//=============================== Mid Tom ====================================
MidTomSynth::MidTomSynth()
 :  decay(0.3),
    noiseLevel(0.01)
{
    mixLevel = 0.6;
    
    filter[0].setCoefficients(IIRCoefficients::makeHighPass(44100, 80));
}
MidTomSynth::~MidTomSynth() {}

void MidTomSynth::alter(float drumLength, float airLevel, float gain)
{
    decay = drumLength;
    noiseLevel = airLevel / 10;
    alterGain(gain);
}

float MidTomSynth::play()

{
    float sample = 0;
    
    if(isPlaying)
    {
        amplitude = ampEnv.ADSR(0.001, decay, 0.001, 0.001, 0.001);
        frequency = env[0].pointToPoint(0.0, 120, 0.2, 45, 0.001, 45, 0.001, 45);
        
        sample = osc[0].getSine(frequency, amplitude) + osc[1].getSine(frequency * 2, amplitude);
        
        float noiseEnv = env[1].ADSR(0.001, 0.4, 0.001, 0.001, 0.001);
        float noise = osc[2].getNoise(noiseEnv * noiseLevel);
        
        sample = (sample + noise) / 1.5;
        
        sample = filter[0].processSingleSampleRaw(sample);
        
        if(isFadeOut)
        {
            fadeOut -= 1.f / (0.1 * 44100.f);
            
            if(fadeOut <= 0)
            {
                fadeOut = 0.f;
            }
        }
    }
    
    isPlaying = ampEnv.getEnvPlaying();
    
    sample = variableCompresser(sample, 2.0, 0.8);
    return ((sample * fadeOut) * gainLevel) * mixLevel;
}

//=============================== High Tom ====================================
HighTomSynth::HighTomSynth()
 :  decay(0.3),
    noiseLevel(0.01)
{
    mixLevel = 0.6;
    
    filter[0].setCoefficients(IIRCoefficients::makeHighPass(44100, 150));
}
HighTomSynth::~HighTomSynth() {}

void HighTomSynth::alter(float drumLength, float airLevel, float gain)
{
    decay = drumLength;
    noiseLevel = airLevel / 10;
    alterGain(gain);
}

float HighTomSynth::play()
{
    float sample = 0;
    
    if(isPlaying)
    {
        amplitude = ampEnv.ADSR(0.001, decay, 0.001, 0.001, 0.001);
        frequency = env[0].pointToPoint(0.0, 130, 0.2, 55, 0.001, 55, 0.001, 55);
        
        sample = osc[0].getSine(frequency, amplitude) + osc[1].getSine(frequency * 2, amplitude);
        
        float noiseEnv = env[1].ADSR(0.001, 0.4, 0.001, 0.001, 0.001);
        float noise = osc[2].getNoise(noiseEnv * noiseLevel);
        
        sample = (sample + noise) / 1.5;
        
        sample = filter[0].processSingleSampleRaw(sample);
        
        if(isFadeOut)
        {
            fadeOut -= 1.f / (0.1 * 44100.f);
            
            if(fadeOut <= 0)
            {
                fadeOut = 0.f;
            }
        }
    }
    
    isPlaying = ampEnv.getEnvPlaying();
    
    sample = variableCompresser(sample, 2.0, 0.8);
    return ((sample * fadeOut) * gainLevel) * mixLevel;
}

//============================== Closed Hat ===================================
ClosedHatSynth::ClosedHatSynth()
:   length(0.05)
{
    mixLevel = 0.3f;
    
    // FILTERS
    filter[0].setCoefficients(IIRCoefficients::makeHighPass(44100.f, 7000.f));

}
ClosedHatSynth::~ClosedHatSynth() {}

void ClosedHatSynth::alter(float freq, float drumLength, float gain)
{
    length = drumLength;
    filter[0].setCoefficients(IIRCoefficients::makeHighPass(44100.f, freq));
    alterGain(gain);
}

float ClosedHatSynth::play()
{
    float sample = 0;
    
    if(isPlaying)
    {
        amplitude = ampEnv.ADSR(0.001, length, 0.001, 0.01, 0.05);
        
        sample = osc[0].getNoise(amplitude);
        
        sample = filter[0].processSingleSampleRaw(sample);
        
        if(isFadeOut)
        {
            fadeOut -= 1.f / (0.01 * 44100.f);
            
            if(fadeOut <= 0)
            {
                fadeOut = 0.f;
            }
        }
    }
    
    isPlaying = ampEnv.getEnvPlaying();
    sample = variableCompresser(sample, 2.0, 0.8);
    return ((sample * fadeOut) * gainLevel) * mixLevel;
}

//=============================== Open Hat ====================================
OpenHatSynth::OpenHatSynth()
:   length(0.2)
{
    mixLevel = 0.5f;
    
    // FILTERS
    filter[0].setCoefficients(IIRCoefficients::makeHighPass(44100.f, 5000.f));
}
OpenHatSynth::~OpenHatSynth() {}

void OpenHatSynth::alter(float freq, float drumLength, float gain)
{
    length = drumLength;
    filter[0].setCoefficients(IIRCoefficients::makeHighPass(44100.f, freq));
    alterGain(gain);
}

float OpenHatSynth::play()
{
    float sample = 0;
    
    if(isPlaying)
    {
        amplitude = ampEnv.ADSR(0.001, length, 0.001, 0.1, 0.1);
        
        sample = osc[0].getNoise(amplitude);
        
        sample = filter[0].processSingleSampleRaw(sample);
        
        if(isFadeOut)
        {
            fadeOut -= 1.f / (0.01 * 44100.f);
            
            if(fadeOut <= 0)
            {
                fadeOut = 0.f;
            }
        }
    }
    
    isPlaying = ampEnv.getEnvPlaying();
    sample = variableCompresser(sample, 2.0, 0.8);
    return ((sample * fadeOut) * gainLevel) * mixLevel;
}

//=============================== Cymbal ====================================
CymbalSynth::CymbalSynth()
:   pitch(8000.f),
    drumLength(0.7)
{
    mixLevel = 0.2f;
    
    filter[0].setCoefficients(IIRCoefficients::makeHighPass(44100.f, 7000.f));
}
CymbalSynth::~CymbalSynth() {}

void CymbalSynth::alter(float tone, float length, float gain)
{
    pitch = tone;
    drumLength = length;
    alterGain(gain);
}

float CymbalSynth::play()
{
    float sample = 0;
    
    if(isPlaying)
    {
        amplitude = ampEnv.ADSR(0.001, drumLength, 0.001, 0.001, 0.001);
        
        sample = osc[1].getSaw(pitch, amplitude * 0.5);
        
        float noise = osc[0].getNoise(amplitude);
        noise = filter[0].processSingleSampleRaw(noise);
        
        sample = sample + noise;
        
        if(isFadeOut)
        {
            fadeOut -= 1.f / (0.01 * 44100.f);
            
            if(fadeOut <= 0)
            {
                fadeOut = 0.f;
            }
        }
    }
    
    isPlaying = ampEnv.getEnvPlaying();
    sample = variableCompresser(sample, 2.0, 0.8);
    return ((sample * fadeOut) * gainLevel) * mixLevel;
}

//=============================== Rimshot ====================================
RimshotSynth::RimshotSynth()
:   freq(300),
    noiseLength(0.01)
    
{
    mixLevel = 0.6f;
    
    // FILTERS
    filter[0].setCoefficients(IIRCoefficients::makeHighPass(44100.f, 5000.f));
}
RimshotSynth::~RimshotSynth() {}

void RimshotSynth::alter(float noise, float tone, float gain)
{
    freq = tone;
    noiseLength = noise;
    alterGain(gain);
}

float RimshotSynth::play()
{
    float sample = 0;
    
    if(isPlaying)
    {
        amplitude = ampEnv.ADSR(0.001, 0.01, 0.001, 0.05, 0.85);
        frequency = env[0].pointToPoint(0.0, 2000, 0.005, 800, 0.008, freq, 0.001, freq);
        
        sample = osc[0].getSine(frequency, amplitude);
        
        float noiseEnv = env[1].ADSR(0.005, noiseLength, 0.001, 0.05, 0.05);
        float noise = osc[2].getNoise(noiseEnv / 20);
        noise = filter[0].processSingleSampleRaw(noise);
        
        sample = (sample / 3) + noise;
        
        if(isFadeOut)
        {
            fadeOut -= 1.f / (0.1 * 44100.f);
            
            if(fadeOut <= 0)
            {
                fadeOut = 0.f;
            }
        }
    }
    
    isPlaying = ampEnv.getEnvPlaying();
    
    sample = variableCompresser(sample, 3.0, 0.8);
    return ((sample * fadeOut) * gainLevel) * mixLevel;
}

//=============================== Clap ====================================
ClapSynth::ClapSynth()
:   releaseT(0.15)
{
    mixLevel = 0.85;
    
    // FILTERS
    filter[0].setCoefficients(IIRCoefficients::makeHighPass(44100.f, 1000.f));
}
ClapSynth::~ClapSynth() {}

void ClapSynth::alter(float release, float filterFreq, float gain)
{
    releaseT = release;
    filter[0].setCoefficients(IIRCoefficients::makeHighPass(44100.f, filterFreq));
    alterGain(gain);
}

float ClapSynth::play()
{
    float sample = 0;
    
    if(isPlaying)
    {
        amplitude = ampEnv.ADSR(0.001, 0.15, 0.001, releaseT, 0.3);
        frequency = env[0].pointToPoint(0.0, 800, 0.005, 80, 0.008, 60, 0.001, 50);
        
        sample = osc[0].getNoise(amplitude);;
        
        sample = filter[0].processSingleSampleRaw(sample);
        
        if(isFadeOut)
        {
            fadeOut -= 1.f / (0.1 * 44100.f);
            
            if(fadeOut <= 0)
            {
                fadeOut = 0.f;
            }
        }
    }
    
    isPlaying = ampEnv.getEnvPlaying();
    
    sample = variableCompresser(sample, 3.0, 0.8);
    return ((sample * fadeOut) * gainLevel) * mixLevel;
}

//=============================== Cowbell ====================================
CowbellSynth::CowbellSynth()
:   freq(540),
    release(0.15)
{
    mixLevel = 0.2f;

    filter[0].setCoefficients(IIRCoefficients::makeLowPass(44100.f, 8000.f));
}
CowbellSynth::~CowbellSynth() {}

void CowbellSynth::alter(float drumLength, float tone, float gain)
{
    release = drumLength;
    freq = tone;
    alterGain(gain);
}

float CowbellSynth::play()
{
    float sample = 0;
    
    if(isPlaying)
    {
        amplitude = ampEnv.ADSR(0.001, 0.15, 0.001, release, 0.1);

        sample = osc[0].getSquare(freq, amplitude) + osc[1].getSquare(freq * 1.5, amplitude);

        sample = filter[0].processSingleSampleRaw(sample);
        
        if(isFadeOut)
        {
            fadeOut -= 1.f / (0.01 * 44100.f);
            
            if(fadeOut <= 0)
            {
                fadeOut = 0.f;
            }
        }
    }
    
    isPlaying = ampEnv.getEnvPlaying();
    sample = variableCompresser(sample, 2.0, 0.8);
    return ((sample * fadeOut) * gainLevel) * mixLevel;
}

