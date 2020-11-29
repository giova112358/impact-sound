/*
  ==============================================================================

    DspProcessor.cpp
    Created: 27 Nov 2020 4:00:33pm
    Author:  Giova

  ==============================================================================
*/

#include "DspProcessor.h"

DspProcessor::DspProcessor(char* key0, char* key1)
{
    inertialResonator = std::make_unique<Inertial>(key0);
    modalResonator = std::make_unique<Modal>(key1, nModes, nPickups);
    impactInteractor = std::make_unique<Impact>(key0, key1);
}

DspProcessor::~DspProcessor()
{
}

void DspProcessor::setExternalForce(double f)
{
    this->f = f;
}

void DspProcessor::setSampleRate(double sampleRate)
{
    SDT_setSampleRate(sampleRate);
}

double DspProcessor::process()
{
    //DBG(ctmpOuts[1]);
    SDTInteractor_dsp(impactInteractor.get()->getSDTObj(), f, 0, 0, 0, 0, 0, tmpOuts);
    return tmpOuts[1];
}

//======================================================================================
void DspProcessor::reset()
{

}
