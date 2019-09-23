/*
  ==============================================================================

    SynthVoice.h
    Created: 16 Sep 2019 11:02:42pm
    Author:  Tiffjuyen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

class SynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound (SynthesiserSound *sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition)
    {
        level = velocity;
        currentAngle = 0.0;
        //frequency =  MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        //std::cout << midiNoteNumber<<std::endl;
        auto cyclesPerSecond = MidiMessage::getMidiNoteInHertz (midiNoteNumber);
        auto cyclesPerSample = cyclesPerSecond / getSampleRate();
        
        angleDelta = cyclesPerSample * MathConstants<double>::twoPi;
    }
    void stopNote (float velocity, bool allowTailOff)
    {
        clearCurrentNote();
        level = 0;
    }
    
    void renderNextBlock (AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
    {
        while (--numSamples >= 0)
        {
            auto currentSample = (float) (std::sin (currentAngle) * level);
            
            for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                outputBuffer.addSample (i, startSample, currentSample);
            
            currentAngle += angleDelta;
            ++startSample;
        }
        
    }
    void pitchWheelMoved (int newPitchWheelValue)
    {
        
    }
    void controllerMoved (int controllerNumber, int newControllerValue)
    {
        
    }

private:
    double level;//聲音大小
    double frequency;//頻率
    double angleDelta;
    double currentAngle;
};
