// James Measey 14002897: 2016-17

#ifndef SynthDrums_h
#define SynthDrums_h

#include "WaveGenerator.h"
#include "Envelope.h"

class SynthDrum
{
public:
    enum Filters {LPF, LPF2, HPF, HPF2, LSF, LSF2, HSF, HSF2, NumFilters};
    SynthDrum();
    virtual ~SynthDrum();
    
    virtual float play() = 0;
    
    void start();
    void prepare();
    void quickFadeOut();
    bool isAudioPlaying();
    bool isAudioPrepared();
    
    float variableCompresser(float sample, float ratio, float threshold);
    void alterGain(float gain);

protected:
    Envelope ampEnv, env[3];
    
    float frequency, amplitude, sampleRate;
    float gainLevel, mixLevel;
    
    bool isPlaying, isPrepared, isFadeOut;
    float fadeOut;
};

//============================== Bass Drum ====================================
class BassSynth :   public SynthDrum
{
public:
    BassSynth();
    ~BassSynth();
    
    void alter(float drumLength, float drumFreq, float gain);
    float play();
    
private:
    WaveBuilder osc[3];
    IIRFilter filter[2];
    float ampDecay, freq;
};

//============================== Kick Drum ====================================
class KickSynth :   public SynthDrum
{
public:
    KickSynth();
    ~KickSynth();
    
    void alter(float drumLength, float drumFreq, float gain);
    float play();
    
private:
    WaveBuilder osc[3];
    IIRFilter filter[2];
    float freq, decayChange;
};

//============================== Snare Drum ===================================
class SnareSynth : public SynthDrum
{
public:
    SnareSynth();
    ~SnareSynth();
    
    void alter(float rattle, float drumFreq, float gain);
    float play();
    
private:
    WaveBuilder osc[3];
    IIRFilter filter[2];
    float freq;
};

//================================ Low Tom ====================================
class LowTomSynth : public SynthDrum
{
public:
    LowTomSynth();
    ~LowTomSynth();
    
    void alter(float drumLength, float airLevel, float gain);
    float play();
    
private:
    WaveBuilder osc[3];
    IIRFilter filter[2];
    float decay, noiseLevel;
};

//================================ Mid Tom ====================================
class MidTomSynth : public SynthDrum
{
public:
    MidTomSynth();
    ~MidTomSynth();
    
    void alter(float drumLength, float airLevel, float gain);
    float play();
    
private:
    WaveBuilder osc[3];
    IIRFilter filter[2];
    float decay, noiseLevel;
};

//================================ High Tom ===================================
class HighTomSynth : public SynthDrum
{
public:
    HighTomSynth();
    ~HighTomSynth();
    
    void alter(float drumLength, float airLevel, float gain);
    float play();
    
private:
    WaveBuilder osc[3];
    IIRFilter filter[2];
    float decay, noiseLevel;
};

//============================== Closed Hat ===================================
class ClosedHatSynth : public SynthDrum
{
public:
    ClosedHatSynth();
    ~ClosedHatSynth();
    
    void alter(float freq, float drumLength, float gain);
    float play();
    
private:
    WaveBuilder osc[3];
    IIRFilter filter[2];
    float length;
};

//=============================== Open Hat ====================================
class OpenHatSynth : public SynthDrum
{
public:
    OpenHatSynth();
    ~OpenHatSynth();
    
    void alter(float freq, float drumLength, float gain);
    float play();
    
private:
    WaveBuilder osc[3];
    IIRFilter filter[2];
    float length;
};

//================================ Cymbal =====================================
class CymbalSynth : public SynthDrum
{
public:
    CymbalSynth();
    ~CymbalSynth();
    
    void alter(float tone, float frequency, float gain);
    float play();
    
private:
    WaveBuilder osc[3];
    IIRFilter filter[2];
    float pitch, drumLength;
};

//================================ Rimshot ====================================
class RimshotSynth : public SynthDrum
{
public:
    RimshotSynth();
    ~RimshotSynth();
    
    void alter(float noise, float tone, float gain);
    float play();
    
private:
    WaveBuilder osc[3];
    IIRFilter filter[2];
    float freq, noiseLength;
};

//================================= Clap ======================================
class ClapSynth : public SynthDrum
{
public:
    ClapSynth();
    ~ClapSynth();
    
    void alter(float release, float filterFreq, float gain);
    float play();
    
private:
    WaveBuilder osc[3];
    IIRFilter filter[2];
    float releaseT;
};

//================================ Cowbell =====================================
class CowbellSynth : public SynthDrum
{
public:
    CowbellSynth();
    ~CowbellSynth();
    
    void alter(float drumLength, float tone, float gain);
    float play();
    
private:
    WaveBuilder osc[3];
    IIRFilter filter[2];
    float freq, release;
};

#endif  // SynthDrums_h
