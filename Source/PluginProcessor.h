/*
 ==============================================================================
 
 This file contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "Position.h"
#include "Junction.h"
#include "Reflections.h"
#include "Absorption.h"
#include "Parameters.h"
#include "Allpass.h"



#include "Convolution/UniformPartitionConvolver.h"
#include "Convolution/TimeDistributedFFTConvolver.h"
#include "Convolution/ConvolutionManager.h"
//==============================================================================
/**
 */
class EarlyReflectionsAudioProcessor  : public juce::AudioProcessor, AudioProcessorValueTreeState::Listener, Value::Listener, public ChangeBroadcaster
{
public:
    //==============================================================================
    EarlyReflectionsAudioProcessor();
    ~EarlyReflectionsAudioProcessor() override;
    

    //==============================================================================
    void parameterChanged (const String &parameterID, float newValue) override;
    
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    
#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif
    
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    
    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    
    //==============================================================================
    const juce::String getName() const override;
    
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    
    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    
    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;


    // CONVOLUTION
    void setImpulseResponse(const AudioSampleBuffer& impulseResponseBuffer, const juce::String pathToImpulse = "") ;
    // -------------------------------------
    int materialFrontBack = 1;
    int materialRightLeft= 1;
    int materialCeilingFloor = 1;
    
    
    int temp = 20;

   
    SmoothedValue<float, ValueSmoothingTypes::Linear> smoothMicX;

    Value roomX {35.f}; //should match default value in parameters.h
    Value roomY {25.f};
    Value roomZ {15.0f};
 
    
    // ==================
    
    
    
    Value sourcePolDist{};
    Value sourcePolAng{};
    
    Value micPolDist{};
    Value micPolAng{};

    float micXLim = 0.5 * (double)roomX.getValue() + (double)micPolDist.getValue() * std::sin((double)micPolAng.getValue());
    float micYLim = (double)micPolDist.getValue() * std::cos((double)micPolAng.getValue());

    Value micX{};
    Value micY{ };

    // ==================

    float sourceXLim = 0.5 * (double)roomX.getValue() + (double)sourcePolDist.getValue() * std::sin((double)sourcePolAng.getValue());
    float sourceYLim = (double)sourcePolDist.getValue() * std::cos((double)sourcePolAng.getValue());

    Value sourceX{ };
    Value sourceY{ };

    AudioProcessorValueTreeState* getPluginState() {return pluginState.get();}
    void updateMicPolarCoordinates();
    void updateMicCartesianCoordinates();
    void updateSourcePolarCoordinates();
    void updateSourceCartesianCoordinates();

    void getEarlyReflections(int channel, int sample);
    
 
private:
   void valueChanged(Value& sourceValue) override;
    std::unique_ptr<AudioProcessorValueTreeState>  pluginState = nullptr;
    Reflections reflections;
    Absorption absorption;
  
    // BUTTON BOOLS
    bool directSoundOnOff = true;
    bool erOnOff = true;
    bool tailOnOff = true;
    bool apfOnOff = true;
    bool convOnOff = true;
    
    // BUFFER AND BLOCKS
    AudioBuffer<float> outBuffer[6];
    dsp::AudioBlock<float> outputBlock[6];
    
    // PREDELAY
    dsp::DelayLine<float,dsp::DelayLineInterpolationTypes::Linear> predelayLine {100000};

    // SIGNALS
    float directSound;
    float convolutedSignal;
    float directAndER;
    float directAndERAndTail;
    float outConv;

    // REFLECTIONS
    float frontReflection;
    float backReflection;
    float rightReflection;
    float leftReflection;
    float ceilingReflection;
    float floorReflection;
     

    // APF
    Allpass allPass1;
    Allpass allPass2;
    Allpass allPass3;
    Allpass allPass4;
    Allpass allPass5;
    Allpass allPass6;

    // CONVOLUTION
    ConvolutionManager<float> mConvolutionManager[2];
    juce::CriticalSection mLoadingLock;
    float mSampleRate;
    int mBufferSize;
    juce::String mImpulseResponseFilePath;
    
    
    juce::AudioFormatManager formatManager;                    // [3]
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    juce::AudioThumbnailCache thumbnailCache;                  // [1]
    juce::AudioThumbnail thumbnail;                            // [2]

    
    AudioSampleBuffer scratchBuffer;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EarlyReflectionsAudioProcessor)
};

