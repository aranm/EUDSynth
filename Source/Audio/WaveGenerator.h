// James Measey 14002897: 2016-17

#ifndef WaveGenerator_h
#define WaveGenerator_h

#include "../JuceLibraryCode/JuceHeader.h"

#define NUM_HARMONICS 12

//============================= SineGenerator =================================
class SineGenerator
{
public:
    SineGenerator();
    ~SineGenerator();
    
    /** Produces a basic sine waveform.
     
     @param freq    The frequency of the waveform to be produced.
     @param amp     The amplitude of the waveform to be produced.
     @return        a basic sine waveform.
     */
    float sine (float freq, float amp);
    
    
    /** Sets sampleRate
     
     Takes the sample rate of the device and uses it to create sine waveform.
     
     @param sampleRate      The sample rate of the the device.
     */
    void setSampleRate (float sampleRate);
    
private:
    float phasePos;
    float sampRate;
    
    /////
    int sampleCount;
};

//============================== WaveBuilder ==================================
class WaveBuilder : Component
{
public:
    WaveBuilder();
    ~WaveBuilder();
    
    /** Produces a basic sine waveform.
     
     @param freq    The frequency of the waveform to be produced.
     @param amp     The amplitude of the waveform to be produced.
     @return        a basic sine waveform.
     */
    float getSine (float freq, float amp);
    
    /** Produces a Square waveform.
     
     @param freq    The frequency of the waveform to be produced.
     @param amp     The amplitude of the waveform to be produced.
     @return        an additive square waveform.
     */
    float getSquare (float freq, float amp);
    
    /** Produces a Sawtooth waveform.
     
     @param freq    The frequency of the waveform to be produced.
     @param amp     The amplitude of the waveform to be produced.
     @return        an additive sawtooth waveform.
     */
    float getSaw (float freq, float amp);
    
    /** Produces random white noise audio samples.
     
     @param amp     The amplitude of the noise.
     @return        white noise audio.
     */
    float getNoise (float amp);
    
private:
    SineGenerator waveGen[NUM_HARMONICS];
};

#endif  // WaveGenerator_h
