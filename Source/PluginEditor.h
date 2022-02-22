/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <algorithm>
//==============================================================================
/**
*/
class EarlyReflectionsAudioProcessorEditor  :  public AudioProcessorEditor, ChangeListener
{
public:
    EarlyReflectionsAudioProcessorEditor (EarlyReflectionsAudioProcessor&);
    ~EarlyReflectionsAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void changeListenerCallback(ChangeBroadcaster* source) override;

private:
    void updateSliderColours();
    Label sourceCoordinateLabel;
    Label micCoordinateLabel;

    EarlyReflectionsAudioProcessor& audioProcessor;

    ComboBox absorptionBoxFrontBack;
    AudioProcessorValueTreeState::ComboBoxAttachment absorptionBoxFrontBackAttachment;
    Label absorptionLabelFrontBack;

    ComboBox absorptionBoxRightLeft;
    AudioProcessorValueTreeState::ComboBoxAttachment absorptionBoxRightLeftAttachment;
    Label absorptionLabelRightLeft;

    ComboBox absorptionBoxCeilingFloor;
    AudioProcessorValueTreeState::ComboBoxAttachment absorptionBoxCeilingFloorAttachment;
    Label absorptionLabelCeilingFloor;


    Slider tempSlider;
    AudioProcessorValueTreeState::SliderAttachment tempSliderAttachment;
    Label tempLabel;
    
    Slider micPolarAngleSlider;
    AudioProcessorValueTreeState::SliderAttachment micPolarAngleSliderAttachment;
    Label micPolarAngleLabel;
    
    Slider micPolarDistanceSlider;
    AudioProcessorValueTreeState::SliderAttachment micPolarDistanceSliderAttachment;
    Label micPolarDistanceLabel;
    
    Slider sourcePolarAngleSlider;
    AudioProcessorValueTreeState::SliderAttachment sourcePolarAngleSliderAttachment;
    Label sourcePolarAngleLabel;
    
    Slider sourcePolarDistanceSlider;
    AudioProcessorValueTreeState::SliderAttachment sourcePolarDistanceSliderAttachment;
    Label sourcePolarDistanceLabel;
    
    Slider micXSlider;
    
    AudioProcessorValueTreeState::SliderAttachment micXSliderAttachment;
     
    Label micXLabel;
    
    Slider micYSlider;
    AudioProcessorValueTreeState::SliderAttachment micYSliderAttachment;
    Label micYLabel;
    
    Slider sourceXSlider;
    AudioProcessorValueTreeState::SliderAttachment sourceXSliderAttachment;
    Label sourceXLabel;
    
    Slider sourceYSlider;
    AudioProcessorValueTreeState::SliderAttachment sourceYSliderAttachment;
    Label sourceYLabel;
    
    Slider roomXSlider;
    AudioProcessorValueTreeState::SliderAttachment roomXSliderAttachment;
    Label roomXLabel;
    
    Slider roomYSlider;
    AudioProcessorValueTreeState::SliderAttachment roomYSliderAttachment;
    Label roomYLabel;
    
    Slider roomZSlider;
    AudioProcessorValueTreeState::SliderAttachment roomZSliderAttachment;
    Label roomZLabel;
    
    
    TextButton allPassButton;
    AudioProcessorValueTreeState::ButtonAttachment allPassButtonAttachment;
  
    TextButton directSoundButton;
    AudioProcessorValueTreeState::ButtonAttachment directSoundButtonAttachment;
  
    
      TextButton filtersButton;
      AudioProcessorValueTreeState::ButtonAttachment filtersButtonAttachment;
    
    
    // CONVOLUTION
    TextButton mButtonChooseIR;
    AudioProcessorValueTreeState::ButtonAttachment mButtonChooseIRButtonAttachment;
    

    TextButton convolutionButton;
    AudioProcessorValueTreeState::ButtonAttachment convolutionButtonAttachment;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EarlyReflectionsAudioProcessorEditor)
};
