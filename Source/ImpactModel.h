/*
  =================================================================================

    ImpactModel.h
    Created: 5 Nov 2020 6:38:13pm
    Author:  Giova

    Basic solid impact interaction algorithm. The interaction is 
    represented by the structure resonator-interactor-resonator 
    object models expose two pickup points, for the resonating object,
    and one pickup point for the exciter. Each pickup point gives information
    about displacement and velocity, and can as well be used to apply
    an external force to the resonator.

  =================================================================================
*/

#pragma once
#include "SDTCommon.h"
#include "SDTSolids.h"

class ImpactModel
{
public:
    ImpactModel();
    ~ImpactModel();

    /*
        ============================================================================
        Set the ID of the two resonators (exciter and resonating object). Link the
        two resonators with the interactor.
        ============================================================================
    */
    void setResonatorsID(char* key0, char* key1);
    void registerInteraction(char* key0, char* key1);

    /*
        ============================================================================
        The first resonator simulates an inertial point mass used as an exciter for 
        the modal resonator. 
        Set the parameter of the inertial resonator, set the position and velocity of 
        the inertial point mass.
        (Optional) set the external force applied to the inertial point mass.
        ============================================================================
    */
    void setInertialParameters(double mass, double fragmentSize);
    void setStrike(double position, double velocity);
    void setExtenalForce(double f);

    /*
        =============================================================================
         Physical model of a set of parallel mass–spring–damper mechanical oscillators, 
         with each oscillator representing a resonant frequency of the object.
         Set the parameters of the modal resonator. The constant parameters of this
         specific model are:
         - number of modes = 3
         - number of pickup points = 2
         ============================================================================
    */
    void setModalParameters(double freqs[SDT_MAX_MODES], double decays[SDT_MAX_MODES], 
        double gains[SDT_MAX_PICKUPS][SDT_MAX_MODES], double fragmentSize, 
        long activeModes);

    /*
          ============================================================================
          Simulates a non-linear impact, by computing the contact force from the total 
          compression, namely the relative displacement between the two contact points.
          Set the parameter of the impact interaction.
          =============================================================================
    */
    void setImpactParameters(float stiffness, double dissipation, double shape, 
        long contact0, long contact1);

    /*
           ==============================================================================
           The processing is done by retriving the displacement of the modal resonator
           in the first pickup point. The processing is a sample-by-sample processing.
           The only processing information needed by the library is the sample rate.
           ==============================================================================
    */
    void setSampleRate(double sampleRate);
    double process();
    void reset();

    SDTResonator* inertial; /*inertial resonator object*/
    SDTResonator* modal;    /*modal resonator object*/
    SDTInteractor* impact; /*impact inetractor object*/

private:
    unsigned int nModes = 3; /*number of frequencies of the modal resonator*/
    unsigned int nPickups = 2; /*number of pickup points of the modal resonator*/

    double tmpOuts[2 * SDT_MAX_PICKUPS]; /*array where the velocity and displacent information
                                         of the modal resonator in the two pickup points are 
                                         stored*/
                                         

    double f{ 0.0 };
};