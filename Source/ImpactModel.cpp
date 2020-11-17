/*
  ==============================================================================

    ImpactModel.cpp
    Created: 5 Nov 2020 6:38:13pm
    Author:  Giova

  ==============================================================================
*/

#include "ImpactModel.h"

//==============================================================================
ImpactModel::ImpactModel()
{
    impact = SDTImpact_new();
    inertial = SDTResonator_new(1, 1);
    modal = SDTResonator_new(3, 2);
}

ImpactModel::~ImpactModel()
{
}

//===============================================================================
void ImpactModel::setResonatorsID(char* key0, char* key1)
{
    SDT_registerResonator(inertial, key0);
    SDT_registerResonator(modal, key1);
}

void ImpactModel::registerInteraction(char* key0, char* key1)
{
    SDT_registerInteractor(impact, key0, key1);
}

//===============================================================================
void ImpactModel::setImpactParameters(float stiffness, double dissipation, 
    double shape, long contact0, long contact1)
{
    SDTImpact_setStiffness(impact, stiffness);
    SDTImpact_setDissipation(impact, dissipation);
    SDTImpact_setShape(impact, shape);
    SDTInteractor_setFirstPoint(impact, contact0);
    SDTInteractor_setSecondPoint(impact, contact1);
}

//================================================================================
void ImpactModel::setInertialParameters(double mass, double fragmentSize)
{
    SDTResonator_setFrequency(inertial, 0, 0.0);
    SDTResonator_setDecay(inertial, 0, 0.0);
    SDTResonator_setWeight(inertial, 0, mass);
    SDTResonator_setGain(inertial, 0, 0, 1.0);
    SDTResonator_setFragmentSize(inertial, fragmentSize);
    SDTResonator_setActiveModes(inertial, 1);
}

void ImpactModel::setStrike(double position, double velocity)
{
    SDTResonator_setPosition(inertial, 0, position);
    SDTResonator_setVelocity(inertial, 0, velocity);
}

void ImpactModel::setExtenalForce(double extForce)
{
    f = extForce;
}

//===================================================================================
void ImpactModel::setModalParameters(double freqs[SDT_MAX_MODES], 
    double decays[SDT_MAX_MODES], double gains[SDT_MAX_PICKUPS][SDT_MAX_MODES],
    double fragmentSize, long activeModes)
{
    for (int mode = 0; mode < nModes; mode++) {
        SDTResonator_setFrequency(modal, mode, freqs[mode]);
        SDTResonator_setDecay(modal, mode, decays[mode]);
        SDTResonator_setWeight(modal, mode, 1.0);
        for (int pickup = 0; pickup < nPickups; pickup++) {
            SDTResonator_setGain(modal, pickup, mode, gains[pickup][mode]);
        }
    }
    SDTResonator_setFragmentSize(modal, fragmentSize);
    SDTResonator_setActiveModes(modal, activeModes);
}

//====================================================================================
void ImpactModel::setSampleRate(double sampleRate)
{
    SDT_setSampleRate(sampleRate);
}

double ImpactModel::process()
{
    SDTInteractor_dsp(impact, f, 0, 0, 0, 0, 0, tmpOuts);
    return tmpOuts[1];
}

//======================================================================================
void ImpactModel::reset()
{

}