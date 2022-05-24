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

convolutionButtonAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xConvolutionOnOff), convolutionButton),

earlyReflectionsButtonAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xEarlyReflectionsButton), earlyReflectionsButton),

tailButtonAttachment(*audioProcessor.getPluginState(), getParameterIdentifier(ParameterIDIndex::xTailButton), tailButton)


{
 
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
    tempSlider.setBounds(45, 240, 100, 100);
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
    
    sourceXSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    sourceXSlider.setBounds(275, 100, 100, 100);
    sourceXSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,false,50,30);
    sourceXSlider.setColour(Slider::thumbColourId, juce::Colours::skyblue);
    sourceXSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(sourceXSlider);
    
    sourceXLabel.setText("Source x", dontSendNotification);
    sourceXLabel.setColour (Label::textColourId, juce::Colours::black);
    sourceXLabel.attachToComponent(&sourceXSlider,true);
    sourceXLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(sourceXLabel);
    
    
    // SOURCE Y SLIDER
    
    sourceYSlider.setSliderStyle(juce::Slider::LinearVertical);
    sourceYSlider.setBounds(210, 30, 100, 100);
    sourceYSlider.setTextBoxStyle(juce::Slider::TextBoxLeft,false,50,30);
    sourceYSlider.setColour(Slider::thumbColourId, juce::Colours::skyblue);
    sourceYSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(sourceYSlider);
    
    sourceYLabel.setText("Source y", dontSendNotification);
    sourceYLabel.setColour (Label::textColourId, juce::Colours::black);
    sourceYLabel.attachToComponent(&sourceYSlider,false);
    sourceYLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(sourceYLabel);
    
    
 
    
    
    // MIC X SLIDER
    
    // micXSlider.addListener(this);
    micXSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    micXSlider.setBounds(465, 100, 100, 100);
    micXSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,false,50,30);
    micXSlider.setColour(Slider::thumbColourId, juce::Colours::skyblue);
    micXSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(micXSlider);
    
    micXLabel.setText("Mic x", dontSendNotification);
    micXLabel.setColour (Label::textColourId, juce::Colours::black);
    micXLabel.attachToComponent(&micXSlider,true);
    micXLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(micXLabel);
    
    
    // MIC Y SLIDER
    
    micYSlider.setSliderStyle(juce::Slider::LinearVertical);
    micYSlider.setBounds(400, 30, 100, 100);
    micYSlider.setTextBoxStyle(juce::Slider::TextBoxLeft,false,50,30);
    micYSlider.setColour(Slider::thumbColourId, juce::Colours::skyblue);
    micYSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(micYSlider);
    
    micYLabel.setText("Mic y", dontSendNotification);
    micYLabel.setColour (Label::textColourId, juce::Colours::black);
    micYLabel.attachToComponent(&micYSlider,false);
    micYLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(micYLabel);
    
    
  
    // ROOM X SLIDER
    
    roomXSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    roomXSlider.setBounds(685, 100, 100, 100);
    roomXSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,false,50,30);
    roomXSlider.setColour(Slider::thumbColourId, juce::Colours::skyblue);
    roomXSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(roomXSlider);
    
    roomXLabel.setText("Room x (width)", dontSendNotification);
    roomXLabel.setColour (Label::textColourId, juce::Colours::black);
    roomXLabel.attachToComponent(&roomXSlider,true);
    roomXLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(roomXLabel);
    
    
    // room Y SLIDER
    
    roomYSlider.setSliderStyle(juce::Slider::LinearVertical);
    roomYSlider.setBounds(620, 30, 100, 100);
    roomYSlider.setTextBoxStyle(juce::Slider::TextBoxLeft,false,50,30);
    roomYSlider.setColour(Slider::thumbColourId, juce::Colours::skyblue);
    roomYSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(roomYSlider);
    
    roomYLabel.setText("Room z (depth)", dontSendNotification);
    roomYLabel.setColour (Label::textColourId, juce::Colours::black);
    roomYLabel.attachToComponent(&roomYSlider,false);
    roomYLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(roomYLabel);
    
    // room Z SLIDER
    
    roomZSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    roomZSlider.setBounds(800, 30, 100, 100);
    roomZSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,false,50,30);
    roomZSlider.setColour(Slider::thumbColourId, juce::Colours::skyblue);
    roomZSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(roomZSlider);
    
    roomZLabel.setText("Room y (height)", dontSendNotification);
    roomZLabel.setColour (Label::textColourId, juce::Colours::black);
    roomZLabel.attachToComponent(&roomZSlider,false);
    roomZLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(roomZLabel);
    
    
    
    
    // FIRST ROW BUTTONS
    
    directSoundButton.setButtonText ("Direct Sound");
    directSoundButton.setBounds(185, 335, 128, 30);
    directSoundButton.setClickingTogglesState (true);
    directSoundButton.setColour(TextButton::buttonOnColourId, juce::Colours::skyblue);
    directSoundButton.setColour(TextButton::textColourOnId, juce::Colours::black);
    directSoundButton.setColour(TextButton::textColourOffId, juce::Colours::white);
    addAndMakeVisible (directSoundButton);
    
    
    
    earlyReflectionsButton.setButtonText ("Early Reflections");
    earlyReflectionsButton.setBounds(326, 335, 128, 30);
    earlyReflectionsButton.setClickingTogglesState (true);
    earlyReflectionsButton.setColour(TextButton::buttonOnColourId, juce::Colours::skyblue);
    earlyReflectionsButton.setColour(TextButton::textColourOnId, juce::Colours::black);
    earlyReflectionsButton.setColour(TextButton::textColourOffId, juce::Colours::white);
    addAndMakeVisible (earlyReflectionsButton);
    
    
    tailButton.setButtonText ("Tail");
    tailButton.setBounds(467, 335, 128, 30);
    tailButton.setClickingTogglesState (true);
    tailButton.setColour(TextButton::buttonOnColourId, juce::Colours::skyblue);
    tailButton.setColour(TextButton::textColourOnId, juce::Colours::black);
    tailButton.setColour(TextButton::textColourOffId, juce::Colours::white);
    addAndMakeVisible (tailButton);
    
    
    
    // SECOND ROW BUTTONS
    
    
    filtersButton.setButtonText ("Absorption");
    filtersButton.setBounds(185, 370, 128, 30);
    filtersButton.setClickingTogglesState (true);
    filtersButton.setColour(TextButton::buttonColourId, juce::Colours::grey);
    filtersButton.setColour(TextButton::buttonOnColourId, juce::Colours::skyblue);
    filtersButton.setColour(TextButton::textColourOnId, juce::Colours::black);
    filtersButton.setColour(TextButton::textColourOffId, juce::Colours::white);
    addAndMakeVisible (filtersButton);
    
    allPassButton.setButtonText ("Allpass Filters");
    allPassButton.setBounds(326, 370, 128, 30);
    allPassButton.setClickingTogglesState (true);
    allPassButton.setColour(TextButton::buttonColourId, juce::Colours::grey);
    allPassButton.setColour(TextButton::buttonOnColourId, juce::Colours::skyblue);
    allPassButton.setColour(TextButton::textColourOnId, juce::Colours::black);
    allPassButton.setColour(TextButton::textColourOffId, juce::Colours::white);
    addAndMakeVisible (allPassButton);
    
    mButtonChooseIR.setButtonText ("Select Tail");
    mButtonChooseIR.setBounds(467, 370, 128, 30);
    mButtonChooseIR.setClickingTogglesState (true);
    mButtonChooseIR.setColour(TextButton::buttonColourId, juce::Colours::grey);
    mButtonChooseIR.setColour(TextButton::buttonOnColourId, juce::Colours::grey);
    addAndMakeVisible (mButtonChooseIR);
    
    
    audioProcessor.addChangeListener(this);
    
    setSize (910, 410);
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
    g.setColour (juce::Colours::skyblue);
    g.fillRect (185, 218, 410, 110);
    g.setColour (juce::Colours::lightblue);

    int startPosX = 763;
    int startPosY = 300;
    int cubeSize = 6;
    //HORISONTAL FRONT
    int offsetDepth = 0.25*roomYSlider.getValue()*cubeSize;
    int offsetWidth = 0.5*roomXSlider.getValue()*cubeSize;
    int offsetHeight = 0.5*roomZSlider.getValue()*cubeSize;
   
    
    // DYNAMIC VISUALIZATION OF ROOM DIMENSIONS.
    
    
    // FRONT SQUARE
    
    juce::Line<float> line1 (juce::Point<float> (startPosX-offsetDepth-offsetWidth, startPosY+offsetDepth-offsetHeight),
                             juce::Point<float> (startPosX-offsetDepth+offsetWidth, startPosY+offsetDepth-offsetHeight));
    
    g.drawLine (line1, 2.0f);
    
    
    juce::Line<float> line2 (juce::Point<float> (startPosX-offsetDepth-offsetWidth, startPosY+offsetDepth+offsetHeight),
                             juce::Point<float>(startPosX-offsetDepth+offsetWidth, startPosY+offsetDepth+offsetHeight));
    g.drawLine (line2, 2.0f);
    
    
    juce::Line<float> line3 (juce::Point<float> (startPosX-offsetDepth-offsetWidth, startPosY+offsetDepth+offsetHeight),
                             juce::Point<float>(startPosX-offsetDepth-offsetWidth, startPosY+offsetDepth-offsetHeight));
    g.drawLine (line3, 2.0f);
    
    
    juce::Line<float> line4 (juce::Point<float> (startPosX-offsetDepth+offsetWidth, startPosY+offsetDepth+offsetHeight),
                             juce::Point<float>(startPosX-offsetDepth+offsetWidth, startPosY+offsetDepth-offsetHeight));
    g.drawLine (line4, 2.0f);
    
    
    
    
    // BACK SQUARE
    
    juce::Line<float> line5 (juce::Point<float> (startPosX+offsetDepth-offsetWidth, startPosY-offsetDepth-offsetHeight),
                             juce::Point<float> (startPosX+offsetDepth+offsetWidth, startPosY-offsetDepth-offsetHeight));
    
    g.drawLine (line5, 2.0f);
    
    
    juce::Line<float> line6 (juce::Point<float> (startPosX+offsetDepth-offsetWidth, startPosY-offsetDepth+offsetHeight),
                             juce::Point<float>(startPosX+offsetDepth+offsetWidth, startPosY-offsetDepth+offsetHeight));
    g.drawLine (line6, 2.0f);
    
    
    juce::Line<float> line7 (juce::Point<float> (startPosX+offsetDepth-offsetWidth, startPosY-offsetDepth+offsetHeight),
                             juce::Point<float>(startPosX+offsetDepth-offsetWidth, startPosY-offsetDepth-offsetHeight));
    g.drawLine (line7, 2.0f);
    
    
    juce::Line<float> line8 (juce::Point<float> (startPosX+offsetDepth+offsetWidth, startPosY-offsetDepth+offsetHeight),
                             juce::Point<float>(startPosX+offsetDepth+offsetWidth, startPosY-offsetDepth-offsetHeight));
    g.drawLine (line8, 2.0f);
    
    
    
    // LINES BETWEEN SQUARES
    
   
    juce::Line<float> line9 (juce::Point<float> (startPosX-offsetDepth-offsetWidth, startPosY+offsetDepth-offsetHeight),
                             juce::Point<float> (juce::Point<float> (startPosX+offsetDepth-offsetWidth, startPosY-offsetDepth-offsetHeight)));
    
    g.drawLine (line9, 2.0f);
   
    
    juce::Line<float> line10 (juce::Point<float> (startPosX-offsetDepth-offsetWidth, startPosY+offsetDepth+offsetHeight),
                             juce::Point<float>(startPosX+offsetDepth-offsetWidth, startPosY-offsetDepth+offsetHeight));
    g.drawLine (line10, 2.0f);
    
    
    juce::Line<float> line11 (juce::Point<float> (startPosX-offsetDepth+offsetWidth, startPosY+offsetDepth+offsetHeight),
                             juce::Point<float>(startPosX+offsetDepth+offsetWidth, startPosY-offsetDepth+offsetHeight));
    g.drawLine (line11, 2.0f);
    
    
    juce::Line<float> line12 (juce::Point<float> (startPosX-offsetDepth+offsetWidth, startPosY+offsetDepth-offsetHeight),
                              juce::Point<float>(startPosX+offsetDepth+offsetWidth, startPosY-offsetDepth-offsetHeight));
    g.drawLine (line12, 2.0f);
    
    
    
    
    
    // IMAGES FOR VISUALIZATION OF STATE
    Image direct = ImageCache::getFromMemory(BinaryData::direct_png, BinaryData::direct_pngSize);
    
    Image er = ImageCache::getFromMemory(BinaryData::er_png, BinaryData::er_pngSize);
    Image erFilterAPF = ImageCache::getFromMemory(BinaryData::erapffiltersoft_png, BinaryData::erapffiltersoft_pngSize);
    Image erAPF = ImageCache::getFromMemory(BinaryData::erapf_png, BinaryData::erapf_pngSize);
    Image erfilter = ImageCache::getFromMemory(BinaryData::erfilter_png, BinaryData::erfilter_pngSize);
    
    Image tail = ImageCache::getFromMemory(BinaryData::tailonly_png, BinaryData::tailonly_pngSize);
    
    int imageX = 190;
    int imageY = 230;
    
  
    
    
    // CHANGE OPACITY OF IMAGES ON GUI BASED ON BUTTON INPUT
    
    if(earlyReflectionsButton.getToggleState() == true && allPassButton.getToggleState()==true && filtersButton.getToggleState() == true){
        g.setOpacity(1);
        g.drawImageAt(erFilterAPF,imageX, imageY);
        
    }
    
    else  if(earlyReflectionsButton.getToggleState() == true && allPassButton.getToggleState()==false && filtersButton.getToggleState() == false){
        g.setOpacity(1);
        g.drawImageAt(er,imageX, imageY);
        
    }
    else    if(earlyReflectionsButton.getToggleState() == true && allPassButton.getToggleState()==true && filtersButton.getToggleState() == false){
        g.setOpacity(1);
        g.drawImageAt(erAPF,imageX, imageY);
        
    }
    
    else   if(earlyReflectionsButton.getToggleState() == true && allPassButton.getToggleState()==false && filtersButton.getToggleState() == true){
        g.drawImageAt(erfilter,imageX, imageY);
        g.setOpacity(1);
        
    }
    
    
    if(earlyReflectionsButton.getToggleState() == false && allPassButton.getToggleState()==true && filtersButton.getToggleState() == true){
        g.setOpacity(0.2);
        g.drawImageAt(erFilterAPF,imageX, imageY);
        
    }
    
    else      if(earlyReflectionsButton.getToggleState() == false && allPassButton.getToggleState()==false && filtersButton.getToggleState() == false){
        g.setOpacity(0.2);
        g.drawImageAt(er,imageX, imageY);
        
    }
    else      if(earlyReflectionsButton.getToggleState() == false && allPassButton.getToggleState()==true && filtersButton.getToggleState() == false){
        g.setOpacity(0.2);
        g.drawImageAt(erAPF,imageX, imageY);
        
    }
    
    else        if(earlyReflectionsButton.getToggleState() == false && allPassButton.getToggleState()==false && filtersButton.getToggleState() == true){
        g.setOpacity(0.2);
        g.drawImageAt(erfilter,imageX, imageY);
        
    }
    
    
    
    if(directSoundButton.getToggleState() == true){
        g.setOpacity(1);
        g.drawImageAt(direct,imageX, imageY);
        
    } else {
        g.setOpacity(0.2);
        g.drawImageAt(direct,imageX, imageY);
    }
    
    
    
    
    
    
    if(tailButton.getToggleState() == true){
        g.setOpacity(1);
        g.drawImageAt(tail,imageX, imageY);
        
    } else {
        g.setOpacity(0.2);
        g.drawImageAt(tail,imageX, imageY);
    }
    
    
    
    
    
    
}






void EarlyReflectionsAudioProcessorEditor::resized()
{
    // call setbounds here
}




void EarlyReflectionsAudioProcessorEditor::changeListenerCallback(ChangeBroadcaster* source) {
    updateSliderColours();
    repaint();
    
}


void EarlyReflectionsAudioProcessorEditor::updateSliderColours(){
    
    if(micXSlider.getValue()>=roomXSlider.getValue()-0.01f ) {
        micXSlider.setColour(Slider::backgroundColourId, juce::Colours::red);
        micXSlider.setColour(Slider::trackColourId, juce::Colours::red);
        roomXSlider.setColour(Slider::backgroundColourId, juce::Colours::red);
        roomXSlider.setColour(Slider::trackColourId, juce::Colours::red);
    } else {
        micXSlider.setColour(Slider::trackColourId, juce::Colours::black);
        micXSlider.setColour(Slider::backgroundColourId, juce::Colours::black);
        roomXSlider.setColour(Slider::backgroundColourId, juce::Colours::black);
        roomXSlider.setColour(Slider::trackColourId, juce::Colours::black);
        
    }
    
    if (sourceXSlider.getValue()>=roomXSlider.getValue()-0.01f ) {
        sourceXSlider.setColour(Slider::backgroundColourId, juce::Colours::red);
        sourceXSlider.setColour(Slider::trackColourId, juce::Colours::red);
        roomXSlider.setColour(Slider::backgroundColourId, juce::Colours::red);
        roomXSlider.setColour(Slider::trackColourId, juce::Colours::red);
    } else {
        sourceXSlider.setColour(Slider::backgroundColourId, juce::Colours::black);
        sourceXSlider.setColour(Slider::trackColourId, juce::Colours::black);
        roomXSlider.setColour(Slider::backgroundColourId, juce::Colours::black);
        roomXSlider.setColour(Slider::trackColourId, juce::Colours::black);
    }
    
    
    if(micYSlider.getValue()>=roomYSlider.getValue()-0.01f){
        micYSlider.setColour(Slider::backgroundColourId, juce::Colours::red);
        micYSlider.setColour(Slider::trackColourId, juce::Colours::red);
        roomYSlider.setColour(Slider::backgroundColourId, juce::Colours::red);
        roomYSlider.setColour(Slider::trackColourId, juce::Colours::red);
    } else {
        micYSlider.setColour(Slider::backgroundColourId, juce::Colours::black);
        micYSlider.setColour(Slider::trackColourId, juce::Colours::black);
        roomYSlider.setColour(Slider::backgroundColourId, juce::Colours::black);
        roomYSlider.setColour(Slider::trackColourId, juce::Colours::black);
        
    }
    
    if(sourceYSlider.getValue()>=roomYSlider.getValue()-0.01f ){
        sourceYSlider.setColour(Slider::backgroundColourId, juce::Colours::red);
        sourceYSlider.setColour(Slider::trackColourId, juce::Colours::red);
        roomYSlider.setColour(Slider::backgroundColourId, juce::Colours::red);
        roomYSlider.setColour(Slider::trackColourId, juce::Colours::red);
    } else {
        sourceYSlider.setColour(Slider::backgroundColourId, juce::Colours::black);
        sourceYSlider.setColour(Slider::trackColourId, juce::Colours::black);
        roomYSlider.setColour(Slider::backgroundColourId, juce::Colours::black);
        roomYSlider.setColour(Slider::trackColourId, juce::Colours::black);
        
    }
    
}
