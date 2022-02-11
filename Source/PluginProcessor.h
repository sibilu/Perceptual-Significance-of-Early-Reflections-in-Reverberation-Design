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
#include "RandomAPF.h"

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

    
    int materialFrontBack = 1;
    int materialRightLeft= 1;
    int materialCeilingFloor = 1;
    
    
    int temp = 20;

   
    SmoothedValue<float, ValueSmoothingTypes::Linear> smoothMicX;

    Value roomX {35.f}; //should match default value in parameters.h
    Value roomY {25.f};
    Value roomZ {15.0f};
 
    
    // ==================
    
    
    
    Value sourcePolDist{ 20.f };
    Value sourcePolAng{0.f};
    
    Value micPolDist{5.f};
    Value micPolAng{0.f};

    float micXLim = 0.5 * (double)roomX.getValue() + (double)micPolDist.getValue() * std::sin((double)micPolAng.getValue());
    float micYLim = (double)micPolDist.getValue() * std::cos((double)micPolAng.getValue());

    Value micX{ micXLim };
    Value micY{ micYLim };

    // ==================

    float sourceXLim = 0.5 * (double)roomX.getValue() + (double)sourcePolDist.getValue() * std::sin((double)sourcePolAng.getValue());
    float sourceYLim = (double)sourcePolDist.getValue() * std::cos((double)sourcePolAng.getValue());

    Value sourceX{ sourceXLim };
    Value sourceY{ sourceYLim };

    AudioProcessorValueTreeState* getPluginState() {return pluginState.get();}
    void updateMicPolarCoordinates();
    void updateMicCartesianCoordinates();
    void updateSourcePolarCoordinates();
    void updateSourceCartesianCoordinates();

private:
    void valueChanged(Value& sourceValue) override;
    std::unique_ptr<AudioProcessorValueTreeState>  pluginState = nullptr;
    Reflections reflections;
    Absorption absorption;

    bool apfOnOff = true;
    bool directSoundOnOff = true;
    // RANDOM ALLPASS
    RandomAPF randomAPFFrontBack; RandomAPF randomAPFRightLeft; RandomAPF randomAPFCeilingFloor;
    am_IIRFilter iirFilterFrontBack[2]; am_IIRFilter iirFilterRightLeft[2]; am_IIRFilter iirFilterCeilingFloor[2];

    int allPassOrder;
    double dump;
    double aFrontBack[1024], bFrontBack[1024];
    double aRightLeft[1024], bRightLeft[1024];
    double aCeilingFloor[1024], bCeilingFloor[1024];
    
    AudioBuffer<float> outBuffer[6];
    dsp::AudioBlock<float> outputBlock[6];
    
    float directSound;
    
    float frontReflection;
    
    float backReflection;
    
    float rightReflection;
    
    float leftReflection;
    
    float ceilingReflection;
    
    float floorReflection;
     
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EarlyReflectionsAudioProcessor)
};

