/*
  ==============================================================================

    SynthSound.h
    Created: 16 Sep 2019 11:02:30pm
    Author:  Tiffjuyen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


class SynthSound : public SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber)
    {
        return true;
    }
    bool appliesToChannel (int midiChannel)
    {
        return true;
    }
};
