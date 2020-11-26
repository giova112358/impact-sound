<!-- omit in toc -->
# Sound Design Toolkit - Impact Model VST3 Plugin
<!-- omit in toc -->
### A plugin realization of the impact model from the Sound Design Toolkit created with [JUCE](https://juce.com/)

<img src="Documents/plugin - version 1.png" width="70%">

<!-- omit in toc -->
## Contents
- [Introduction](#introduction)
- [Software Architecture](#software-architecture)
- [Impact Model](#impact-model)
    - [Description](#description)
- [References](#references)
 
## Introduction
The Sound Design Toolkit consists in a library of ecologically founded (e.g physics based) sound synthesis algorithms. These algorithms have been implemented according to three main points:
- auditory perceptual relevance;
- cartoonification;
- parametric temporal control;

In this project the entire SDT library is ported in C++ and integrated in the JUCE framework for the realization of a VST3 plugin version of the impact model.

## Software Architecture
 The software architecture consists of :
 - **SDT Library** A core library coded in ANSI C, with few and widely supported dependencies, exposing a clean and streamlined API to all the implemented sound models, sound processors and audio feature extractors.
 - **Wrapper class** A class that realizes the porting of the desired SDT objects  to use them in the JUCE framework.
 - **Plugin Processor** The JUCE Framework class that realizes the audio processing for a Plugin.
 - **Plugin Editor** The JUCE Framework class that realizes the GUI and all the parameter listeners used to update the audio processing. 
 
## Impact Model
#### Description
The impact model is one of the two basics solid interaction models implemented by the Sound Design Toolkit. The interaction algorithm has a modular structure "resonator–"interactor–resonator", representing the interaction between two resonating objects.
An efficient tool for describing resonating objects is **Modal Synthesis**.
We can model a parallel connection of N oscillating system, made of lumped mechanical elements (such as masses, springs or dampers), by choosing different stiffness 

<img src="Documents/eq2.png" width="20%">


and account for a set of partials of the resonator spectrum (pitches)

<img src="Documents/eq3.png" width="10%">

The resulting model equations, in matrix form are the following:

<img src="Documents/equation 1.png" width="70%">

The displacement of the resonator is obtained in this way

<img src="Documents/eq5.png" width="20%">

while the velocity of the resonator is

<img src="Documents/eq4.png" width="20%">




## References
- (1) https://www.eecs.qmul.ac.uk/~josh/documents/2012/GiannoulisMassbergReiss-dynamicrangecompression-JAES2012.pdf
- (2) http://c4dm.eecs.qmul.ac.uk/audioengineering/compressors/documents/Reiss-Tutorialondynamicrangecompression.pdf
- (3) http://c4dm.eecs.qmul.ac.uk/audioengineering/compressors/documents/Giannoulis.pdf
- (4) http://www.eecs.qmul.ac.uk/~josh/documents/2013/Giannoulis%20Massberg%20Reiss%20-%20dynamic%20range%20compression%20automation%20-%20JAES%202013.pdf
- (5) https://github.com/DanielRudrich/SimpleCompressor/blob/master/docs/lookAheadLimiter.md


[1]: https://www.eecs.qmul.ac.uk/~josh/documents/2012/GiannoulisMassbergReiss-dynamicrangecompression-JAES2012.pdf
[2]: http://c4dm.eecs.qmul.ac.uk/audioengineering/compressors/documents/Reiss-Tutorialondynamicrangecompression.pdf
[3]: http://c4dm.eecs.qmul.ac.uk/audioengineering/compressors/documents/Giannoulis.pdf
[4]: http://www.eecs.qmul.ac.uk/~josh/documents/2013/Giannoulis%20Massberg%20Reiss%20-%20dynamic%20range%20compression%20automation%20-%20JAES%202013.pdf
[5]: https://github.com/DanielRudrich/SimpleCompressor/blob/master/docs/lookAheadLimiter.md




