/*
 ==============================================================================
 
 This file contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EarlyReflectionsAudioProcessorEditor::EarlyReflectionsAudioProcessorEditor (EarlyReflectionsAudioProcessor& p)
: AudioProcessorEditor (&p), audioProcessor (p),
absorptionBoxFrontBackAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xMaterialFrontBack), absorptionBoxFrontBack),

absorptionBoxRightLeftAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xMaterialRightLeft), absorptionBoxRightLeft),

absorptionBoxCeilingFloorAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xMaterialCeilingFloor), absorptionBoxCeilingFloor),

tempSliderAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xTemp), tempSlider),
micPolarAngleSliderAttachment(*audioProcessor.getPluginState(),
                              getParameterIdentifier(ParameterIDIndex::xMicPolAng), micPolarAngleSlider),

micPolarDistanceSliderAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xMicPolDist), micPolarDistanceSlider),

sourcePolarAngleSliderAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xSourcePolAng), sourcePolarAngleSlider),

sourcePolarDistanceSliderAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xSourcePolDist), sourcePolarDistanceSlider), 

micXSliderAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xMicX), micXSlider),

micYSliderAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xMicY), micYSlider),

sourceXSliderAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xSourceX), sourceXSlider),

sourceYSliderAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xSourceY), sourceYSlider),

roomXSliderAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xRoomX), roomXSlider),

roomYSliderAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xRoomY), roomYSlider),

roomZSliderAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xRoomZ), roomZSlider),

allPassButtonAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xAllPassButton), allPassButton),

directSoundButtonAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xDirectSoundButton), directSoundButton),

filtersButtonAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xFiltersButton), filtersButton),

mButtonChooseIRButtonAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xmButtonChooseIR), mButtonChooseIR),


convolutionButtonAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xConvolutionOnOff), convolutionButton)


{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    sourceCoordinateLabel.setFont (juce::Font (16.0f, juce::Font::plain));
    sourceCoordinateLabel.setText ("Source: "+ (String)audioProcessor.sourceXLim + ", " +(String)audioProcessor.sourceYLim, juce::dontSendNotification);
    sourceCoordinateLabel.setColour (juce::Label::textColourId, juce::Colours::black);
    sourceCoordinateLabel.setJustificationType (juce::Justification::left);
    sourceCoordinateLabel.setBounds(685, 240, 200, 100);
    addAndMakeVisible (sourceCoordinateLabel);
    
    
    micCoordinateLabel.setFont (juce::Font (16.0f, juce::Font::plain));
    micCoordinateLabel.setText ("Mic: "+ (String)audioProcessor.micXLim + ", " + (String)audioProcessor.micYLim, juce::dontSendNotification);
    micCoordinateLabel.setColour (juce::Label::textColourId, juce::Colours::black);
    micCoordinateLabel.setJustificationType (juce::Justification::left);
    micCoordinateLabel.setBounds(685, 260, 200, 100);
    addAndMakeVisible (micCoordinateLabel);
    
    // add items to the combo-box
    absorptionBoxFrontBack.setBounds(15, 30, 160, 20);
    absorptionBoxFrontBack.addItem("Carpet: heavy on concrete", 1);
    absorptionBoxFrontBack.addItem("Carpet: heavy on 40-oz hair felt", 2);
    absorptionBoxFrontBack.addItem("Acoustical tile, 3/4-in thick", 3);
    absorptionBoxFrontBack.addItem("Concrete block, coarse", 4);
    absorptionBoxFrontBack.addItem("Wood", 5);
    absorptionBoxFrontBack.addItem("Glass: large panes, heavy glass", 6);
    absorptionBoxFrontBack.addItem("Plywood panel: 3/8-in thick", 7);
    absorptionBoxFrontBack.addItem("Perforated Panel. Perf: 1.4%", 8);
        absorptionBoxFrontBack.setSelectedId(1);
    addAndMakeVisible(absorptionBoxFrontBack);
    
    absorptionLabelFrontBack.setText("Front/Back Wall Material", dontSendNotification);
    absorptionLabelFrontBack.setColour (Label::textColourId, juce::Colours::black);
    absorptionLabelFrontBack.attachToComponent(&absorptionBoxFrontBack,false);
    absorptionLabelFrontBack.setJustificationType(Justification::centred);
    addAndMakeVisible(absorptionLabelFrontBack);
    
    
    // add items to the combo-box
    absorptionBoxRightLeft.setBounds(15, 90, 160, 20);
    absorptionBoxRightLeft.addItem("Carpet: heavy on concrete", 1);
    absorptionBoxRightLeft.addItem("Carpet: heavy on 40-oz hair felt", 2);
    absorptionBoxRightLeft.addItem("Acoustical tile, 3/4-in thick", 3);
    absorptionBoxRightLeft.addItem("Concrete block, coarse", 4);
    absorptionBoxRightLeft.addItem("Wood", 5);
    absorptionBoxRightLeft.addItem("Glass: large panes, heavy glass", 6);
    absorptionBoxRightLeft.addItem("Plywood panel: 3/8-in thick", 7);
    absorptionBoxRightLeft.addItem("Perforated Panel. Perf: 1.4%", 8);
    
    absorptionBoxRightLeft.setSelectedId(1);
    addAndMakeVisible(absorptionBoxRightLeft);
    
    absorptionLabelRightLeft.setText("Right/Left Wall Material", dontSendNotification);
    absorptionLabelRightLeft.setColour (Label::textColourId, juce::Colours::black);
    absorptionLabelRightLeft.attachToComponent(&absorptionBoxRightLeft,false);
    absorptionLabelRightLeft.setJustificationType(Justification::centred);
    addAndMakeVisible(absorptionLabelRightLeft);
    
    // add items to the combo-box
    absorptionBoxCeilingFloor.setBounds(15, 150, 160, 20);
    absorptionBoxCeilingFloor.addItem("Carpet: heavy on concrete", 1);
    absorptionBoxCeilingFloor.addItem("Carpet: heavy on 40-oz hair felt", 2);
    absorptionBoxCeilingFloor.addItem("Acoustical tile, 3/4-in thick", 3);
    absorptionBoxCeilingFloor.addItem("Concrete block, coarse", 4);
    absorptionBoxCeilingFloor.addItem("Wood", 5);
    absorptionBoxCeilingFloor.addItem("Glass: large panes, heavy glass", 6);
    absorptionBoxCeilingFloor.addItem("Plywood panel: 3/8-in thick", 7);
    absorptionBoxCeilingFloor.addItem("Perforated Panel. Perf: 1.4%", 8);
    
    
    absorptionBoxCeilingFloor.setSelectedId(1);
    addAndMakeVisible(absorptionBoxCeilingFloor);
    
    absorptionLabelCeilingFloor.setText("Ceiling/Floor Material", dontSendNotification);
    absorptionLabelCeilingFloor.setColour (Label::textColourId, juce::Colours::black);
    absorptionLabelCeilingFloor.attachToComponent(&absorptionBoxCeilingFloor,false);
    absorptionLabelCeilingFloor.setJustificationType(Justification::centred);
    addAndMakeVisible(absorptionLabelCeilingFloor);
    
    
    
    
    
    tempSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    tempSlider.setBounds(45, 220, 100, 100);
    tempSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,false,50,30);
    tempSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    tempSlider.setColour(Slider::thumbColourId, juce::Colours::firebrick);

    addAndMakeVisible(tempSlider);
    
    tempLabel.setText("Air temperature", dontSendNotification);
    tempLabel.setColour (Label::textColourId, juce::Colours::black);
    tempLabel.attachToComponent(&tempSlider,false);
    tempLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(tempLabel);
    
    
    
    
    
     
     // SOURCE X SLIDER
     
     // sourceXSlider.addListener(this);
     sourceXSlider.setSliderStyle(juce::Slider::LinearHorizontal);
     sourceXSlider.setBounds(275, 100, 100, 100);
     sourceXSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,false,50,30);
     
     sourceXSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
     //  sourceXSlider.setRange(0.01, 35.f, 0.01);;
     
     //    sourceXSlider.getValueObject().referTo(audioProcessor.sourceX);
     
     addAndMakeVisible(sourceXSlider);
     sourceXLabel.setText("Source x", dontSendNotification);
     sourceXLabel.setColour (Label::textColourId, juce::Colours::black);
     sourceXLabel.attachToComponent(&sourceXSlider,true);
     sourceXLabel.setJustificationType(Justification::centred);
     addAndMakeVisible(sourceXLabel);
     
     
     // SOURCE Y SLIDER
     
     // sourceYSlider.addListener(this);
     sourceYSlider.setSliderStyle(juce::Slider::LinearVertical);
     sourceYSlider.setBounds(210, 30, 100, 100);
     sourceYSlider.setTextBoxStyle(juce::Slider::TextBoxLeft,false,50,30);
     sourceYSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
     //  sourceYSlider.setRange(0.01, 35.f, 0.01);
     
     //    sourceYSlider.getValueObject().referTo(audioProcessor.sourceY);
     
     addAndMakeVisible(sourceYSlider);
     
     sourceYLabel.setText("Source y", dontSendNotification);
     sourceYLabel.setColour (Label::textColourId, juce::Colours::black);
     sourceYLabel.attachToComponent(&sourceYSlider,false);
     sourceYLabel.setJustificationType(Justification::centred);
     addAndMakeVisible(sourceYLabel);
     
     
    
    /*
    // SOURCE POLAR MAGNITUDE
    
    sourcePolarDistanceSlider.setSliderStyle(juce::Slider::LinearVertical);
    sourcePolarDistanceSlider.setBounds(210, 30, 100, 150);
    sourcePolarDistanceSlider.setTextBoxStyle(juce::Slider::TextBoxLeft,false,50,30);
    sourcePolarDistanceSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    sourcePolarDistanceSlider.setColour(Slider::thumbColourId, juce::Colours::seagreen);
    
    addAndMakeVisible(sourcePolarDistanceSlider);
    
    sourcePolarDistanceLabel.setText("Source Dist", dontSendNotification);
    sourcePolarDistanceLabel.setColour (Label::textColourId, juce::Colours::black);
    sourcePolarDistanceLabel.attachToComponent(&sourcePolarDistanceSlider,false);
    sourcePolarDistanceLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(sourcePolarDistanceLabel);
    
    
    // POLAR ANGLE KNOB
    
    sourcePolarAngleSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sourcePolarAngleSlider.setBounds(195, 220, 180, 180);
    sourcePolarAngleSlider.setTextBoxStyle(juce::Slider::NoTextBox,false,50,30);
    sourcePolarAngleSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    sourcePolarAngleSlider.setColour(Slider::thumbColourId, juce::Colours::seagreen);
    // sourcePolarAngleSlider.setRange(-MathConstants<float>::halfPi, MathConstants<float>::halfPi, 0.01);;
    //   sourcePolarAngleSlider.getValueObject().referTo(audioProcessor.sourcePolAng);
    sourcePolarAngleSlider.setRotaryParameters(0.75*MathConstants<float>::twoPi, 1.25*MathConstants<float>::twoPi, true);
    addAndMakeVisible(sourcePolarAngleSlider);
    
    sourcePolarAngleLabel.setText("Source Ang", dontSendNotification);
    sourcePolarAngleLabel.setColour (Label::textColourId, juce::Colours::black);
    sourcePolarAngleLabel.attachToComponent(&sourcePolarAngleSlider,false);
    sourcePolarAngleLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(sourcePolarAngleLabel);
    
    */
     
    
    
     // MIC X SLIDER
     
     // micXSlider.addListener(this);
     micXSlider.setSliderStyle(juce::Slider::LinearHorizontal);
     micXSlider.setBounds(465, 100, 100, 100);
     micXSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,false,50,30);
     
     micXSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
     //   micXSlider.setRange(0.01, 35.f, 0.01);;
     //   micXSlider.getValueObject().referTo(audioProcessor.micX);
     
     addAndMakeVisible(micXSlider);
     
     micXLabel.setText("Mic x", dontSendNotification);
     micXLabel.setColour (Label::textColourId, juce::Colours::black);
     micXLabel.attachToComponent(&micXSlider,true);
     micXLabel.setJustificationType(Justification::centred);
     addAndMakeVisible(micXLabel);
     
     
     // MIC Y SLIDER
     
     // micYSlider.addListener(this);
     micYSlider.setSliderStyle(juce::Slider::LinearVertical);
     micYSlider.setBounds(400, 30, 100, 100);
     micYSlider.setTextBoxStyle(juce::Slider::TextBoxLeft,false,50,30);
     micYSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
     //  micYSlider.setRange(0.01, 35.f, 0.01);;
     //    micYSlider.getValueObject().referTo(audioProcessor.micY);
     addAndMakeVisible(micYSlider);
     
     micYLabel.setText("Mic y", dontSendNotification);
     micYLabel.setColour (Label::textColourId, juce::Colours::black);
     micYLabel.attachToComponent(&micYSlider,false);
     micYLabel.setJustificationType(Justification::centred);
     addAndMakeVisible(micYLabel);
     
    
  /*
    // MIC POLAR MAGNITUDE
    
    //micPolarDistanceSlider.addListener(this);
    micPolarDistanceSlider.setSliderStyle(juce::Slider::LinearVertical);
    micPolarDistanceSlider.setBounds(430, 30, 100, 150);
    micPolarDistanceSlider.setTextBoxStyle(juce::Slider::TextBoxLeft,false,50,30);
    micPolarDistanceSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    micPolarDistanceSlider.setColour(Slider::thumbColourId, juce::Colours::seagreen);
    
    // micPolarDistanceSlider.setRange(0.01, 35.f, 0.01);;
    //   micPolarDistanceSlider.getValueObject().referTo(audioProcessor.micPolDist);
    
    addAndMakeVisible(micPolarDistanceSlider);
    
    micPolarDistanceLabel.setText("Mic Dist", dontSendNotification);
    micPolarDistanceLabel.setColour (Label::textColourId, juce::Colours::black);
    micPolarDistanceLabel.attachToComponent(&micPolarDistanceSlider,false);
    micPolarDistanceLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(micPolarDistanceLabel);
    
    
    // POLAR ANGLE KNOB
    
    //micPolarAngleSlider.addListener(this);
    micPolarAngleSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    micPolarAngleSlider.setBounds(415, 220, 180, 180);
    micPolarAngleSlider.setTextBoxStyle(juce::Slider::NoTextBox,false,50,30);
    micPolarAngleSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    micPolarAngleSlider.setColour(Slider::thumbColourId, juce::Colours::seagreen);
    // micPolarAngleSlider.setRange(-MathConstants<float>::halfPi, MathConstants<float>::halfPi, 0.01);;
    //   micPolarAngleSlider.getValueObject().referTo(audioProcessor.micPolAng);
    micPolarAngleSlider.setRotaryParameters(0.75*MathConstants<float>::twoPi, 1.25*MathConstants<float>::twoPi, true);
    addAndMakeVisible(micPolarAngleSlider);
    
    micPolarAngleLabel.setText("Mic Angle", dontSendNotification);
    micPolarAngleLabel.setColour (Label::textColourId, juce::Colours::black);
    micPolarAngleLabel.attachToComponent(&micPolarAngleSlider,false);
    micPolarAngleLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(micPolarAngleLabel);
    
    */
    // ROOM X SLIDER
    
    //  roomXSlider.addListener(this);
    roomXSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    roomXSlider.setBounds(685, 100, 100, 100);
    roomXSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,false,50,30);
    
    roomXSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    //  roomXSlider.setRange(0.01f, 35.f, 0.01f);
    
    //   roomXSlider.getValueObject().referTo(audioProcessor.roomX);
    
    addAndMakeVisible(roomXSlider);
    
    roomXLabel.setText("Room x", dontSendNotification);
    roomXLabel.setColour (Label::textColourId, juce::Colours::black);
    roomXLabel.attachToComponent(&roomXSlider,true);
    roomXLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(roomXLabel);
    
    
    // room Y SLIDER
    
    // roomYSlider.addListener(this);
    roomYSlider.setSliderStyle(juce::Slider::LinearVertical);
    roomYSlider.setBounds(620, 30, 100, 100);
    roomYSlider.setTextBoxStyle(juce::Slider::TextBoxLeft,false,50,30);
    roomYSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    //  roomYSlider.setRange(0.01f, 35.f, 0.01f);;
    //    roomYSlider.getValueObject().referTo(audioProcessor.roomY);
    addAndMakeVisible(roomYSlider);
    
    roomYLabel.setText("Room y", dontSendNotification);
    roomYLabel.setColour (Label::textColourId, juce::Colours::black);
    roomYLabel.attachToComponent(&roomYSlider,false);
    roomYLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(roomYLabel);
    
    // room Z SLIDER
    
    //  roomZSlider.addListener(this);
    roomZSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    roomZSlider.setBounds(800, 30, 100, 100);
    roomZSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,false,50,30);
    roomZSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    // roomZSlider.setRange(0.01f, 35.f, 0.01f);;
    //   roomZSlider.getValueObject().referTo(audioProcessor.roomZ);
    addAndMakeVisible(roomZSlider);
    
    roomZLabel.setText("Room z", dontSendNotification);
    roomZLabel.setColour (Label::textColourId, juce::Colours::black);
    roomZLabel.attachToComponent(&roomZSlider,false);
    roomZLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(roomZLabel);
    
    directSoundButton.setButtonText ("Direct");
    directSoundButton.setBounds(685, 240, 50, 30);
    directSoundButton.setClickingTogglesState (true);
    directSoundButton.setColour(TextButton::buttonColourId, juce::Colours::grey);
    directSoundButton.setColour(TextButton::buttonOnColourId, juce::Colours::turquoise);
    directSoundButton.setColour(TextButton::textColourOnId, juce::Colours::black);
    directSoundButton.setColour(TextButton::textColourOffId, juce::Colours::white);
    addAndMakeVisible (directSoundButton);
    
    
    allPassButton.setButtonText ("APF");
    allPassButton.setBounds(745, 240, 50, 30);
    allPassButton.setClickingTogglesState (true);
    allPassButton.setColour(TextButton::buttonColourId, juce::Colours::grey);
    allPassButton.setColour(TextButton::buttonOnColourId, juce::Colours::turquoise);
    allPassButton.setColour(TextButton::textColourOnId, juce::Colours::black);
    allPassButton.setColour(TextButton::textColourOffId, juce::Colours::white);
    addAndMakeVisible (allPassButton);
    
    
    
    
    
    filtersButton.setButtonText ("Filters");
    filtersButton.setBounds(805, 240, 50, 30);
    filtersButton.setClickingTogglesState (true);
    filtersButton.setColour(TextButton::buttonColourId, juce::Colours::grey);
    filtersButton.setColour(TextButton::buttonOnColourId, juce::Colours::turquoise);
    filtersButton.setColour(TextButton::textColourOnId, juce::Colours::black);
    filtersButton.setColour(TextButton::textColourOffId, juce::Colours::white);
    addAndMakeVisible (filtersButton);
    
    mButtonChooseIR.setButtonText ("Select IR");
    mButtonChooseIR.setBounds(500, 240, 50, 30);
    mButtonChooseIR.setClickingTogglesState (true);
    mButtonChooseIR.setColour(TextButton::buttonColourId, juce::Colours::grey);
    addAndMakeVisible (mButtonChooseIR);
    
    convolutionButton.setButtonText ("Tail");
    convolutionButton.setBounds(560, 240, 50, 30);
    convolutionButton.setClickingTogglesState (true);
    convolutionButton.setColour(TextButton::buttonColourId, juce::Colours::grey);
    addAndMakeVisible (convolutionButton);
    
    audioProcessor.addChangeListener(this);
    
    setSize (910, 350);
}


EarlyReflectionsAudioProcessorEditor::~EarlyReflectionsAudioProcessorEditor()
{
    
    audioProcessor.removeChangeListener(this);
}


//==============================================================================
void EarlyReflectionsAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (Colours::azure);
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}




void EarlyReflectionsAudioProcessorEditor::resized()
{
    // call setbounds here
}




void EarlyReflectionsAudioProcessorEditor::changeListenerCallback(ChangeBroadcaster* source) {
    updateSliderColours();
    
    sourceCoordinateLabel.setText ("Source: "+ (String)audioProcessor.sourceXLim + ", " +(String)audioProcessor.sourceYLim, juce::dontSendNotification);
    micCoordinateLabel.setText ("Mic: "+ (String)audioProcessor.micXLim + ", " +(String)audioProcessor.micYLim, juce::dontSendNotification);
}


void EarlyReflectionsAudioProcessorEditor::updateSliderColours(){
    
    
    if(micXSlider.getValue()>=roomXSlider.getValue()-0.01f || sourceXSlider.getValue()>=roomXSlider.getValue()-0.01f || micXSlider.getValue()<=0.01f || sourceXSlider.getValue()<=0.01f){
        micXSlider.setColour(Slider::backgroundColourId, juce::Colours::orange);
        roomXSlider.setColour(Slider::backgroundColourId, juce::Colours::orange);
        roomXSlider.setColour(Slider::trackColourId, juce::Colours::orange);
        
        
    } else{
        micXSlider.setColour(Slider::backgroundColourId, juce::Colours::black);
        roomXSlider.setColour(Slider::backgroundColourId, juce::Colours::black);
        roomXSlider.setColour(Slider::trackColourId, juce::Colours::black);
        
    }
    if(micYSlider.getValue()>=roomYSlider.getValue()-0.01f || sourceYSlider.getValue()>=roomYSlider.getValue()-0.01f || micYSlider.getValue()<=0.01f || sourceYSlider.getValue()<=0.01f){
        micYSlider.setColour(Slider::backgroundColourId, juce::Colours::orange);
        roomYSlider.setColour(Slider::backgroundColourId, juce::Colours::orange);
        roomYSlider.setColour(Slider::trackColourId, juce::Colours::orange);
        
    } else{
        micYSlider.setColour(Slider::backgroundColourId, juce::Colours::black);
        roomYSlider.setColour(Slider::backgroundColourId, juce::Colours::black);
        roomYSlider.setColour(Slider::trackColourId, juce::Colours::black);
        
    }
    
}
