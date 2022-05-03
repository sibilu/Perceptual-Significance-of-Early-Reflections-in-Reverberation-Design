/*
 ==============================================================================
 
 This file contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Convolution/util/SincFilter.hpp"
#include "Convolution/util/util.h"

//==============================================================================
EarlyReflectionsAudioProcessor::EarlyReflectionsAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
                  
                  
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
                  ),
// WAVEFORM
thumbnailCache (5),                            // [4]
thumbnail (512, formatManager, thumbnailCache) // [5]
//  ,lowPassFilter(dsp::IIR::Coefficients<float>::makeLowPass(44100, 400, 0.1f)),  highPassFilter(dsp::IIR::Coefficients<float>::makeHighPass(44100, 2000, 0.1f))
#endif
{
    pluginState.reset(new AudioProcessorValueTreeState(*this,nullptr,"EarlyReflection",getParameterLayout()));
    
    for(auto param:ParameterID){
        pluginState->addParameterListener(param, this);
    }
    
    micX.referTo(pluginState->getParameterAsValue(getParameterIdentifier(ParameterIDIndex::xMicX)));
    micY.referTo(pluginState->getParameterAsValue(getParameterIdentifier(ParameterIDIndex::xMicY)));
    micPolDist.referTo(pluginState->getParameterAsValue(getParameterIdentifier(ParameterIDIndex::xMicPolDist)));
    micPolAng.referTo(pluginState->getParameterAsValue(getParameterIdentifier(ParameterIDIndex::xMicPolAng)));
    
    sourceX.referTo(pluginState->getParameterAsValue(getParameterIdentifier(ParameterIDIndex::xSourceX)));
    sourceY.referTo(pluginState->getParameterAsValue(getParameterIdentifier(ParameterIDIndex::xSourceY)));
    sourcePolDist.referTo(pluginState->getParameterAsValue(getParameterIdentifier(ParameterIDIndex::xSourcePolDist)));
    sourcePolAng.referTo(pluginState->getParameterAsValue(getParameterIdentifier(ParameterIDIndex::xSourcePolAng)));
    
    roomX.referTo(pluginState->getParameterAsValue(getParameterIdentifier(ParameterIDIndex::xRoomX)));
    roomY.referTo(pluginState->getParameterAsValue(getParameterIdentifier(ParameterIDIndex::xRoomY)));
    roomZ.referTo(pluginState->getParameterAsValue(getParameterIdentifier(ParameterIDIndex::xRoomZ)));
    
    
    
    micX.addListener(this);
    micY.addListener(this);
    micPolDist.addListener(this);
    micPolAng.addListener(this);
    
    sourceX.addListener(this);
    sourceY.addListener(this);
    sourcePolDist.addListener(this);
    sourcePolAng.addListener(this);
    
    roomX.addListener(this);
    roomY.addListener(this);
    roomZ.addListener(this);
    
    
    
    // WAVEFORM
    //   thumbnail.addChangeListener (this);            // [6]
    
}

EarlyReflectionsAudioProcessor::~EarlyReflectionsAudioProcessor()
{
    for(auto param:ParameterID){
        pluginState->removeParameterListener(param, this);
    }
    
    micX.removeListener(this);
    micY.removeListener(this);
    micPolDist.removeListener(this);
    micPolAng.removeListener(this);
    
    sourceX.removeListener(this);
    sourceY.removeListener(this);
    sourcePolDist.removeListener(this);
    sourcePolAng.removeListener(this);
    
    roomX.removeListener(this);
    roomY.removeListener(this);
    roomZ.removeListener(this);
}

//==============================================================================
const juce::String EarlyReflectionsAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EarlyReflectionsAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool EarlyReflectionsAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool EarlyReflectionsAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double EarlyReflectionsAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EarlyReflectionsAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int EarlyReflectionsAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EarlyReflectionsAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String EarlyReflectionsAudioProcessor::getProgramName (int index)
{
    return {};
}

void EarlyReflectionsAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}


void EarlyReflectionsAudioProcessor::setImpulseResponse(const AudioSampleBuffer& impulseResponseBuffer, const juce::String pathToImpulse)
{
    juce::ScopedLock lock(mLoadingLock);
    mImpulseResponseFilePath = pathToImpulse;
    AudioSampleBuffer impulseResponse(impulseResponseBuffer);
    
    if (impulseResponseBuffer.getNumChannels() == 2)
    {
        float *impulseResponseLeft = impulseResponse.getWritePointer(0);
        float *impulseResponseRight = impulseResponse.getWritePointer(1);
        
        normalizeStereoImpulseResponse(impulseResponseLeft, impulseResponseRight, impulseResponse.getNumSamples());
        mConvolutionManager[0].setImpulseResponse(impulseResponseLeft, impulseResponse.getNumSamples());
        mConvolutionManager[1].setImpulseResponse(impulseResponseRight, impulseResponse.getNumSamples());
    }
    else
    {
        float *ir = impulseResponse.getWritePointer(0);
        
        normalizeMonoImpulseResponse(ir, impulseResponse.getNumSamples());
        mConvolutionManager[0].setImpulseResponse(ir, impulseResponse.getNumSamples());
        mConvolutionManager[1].setImpulseResponse(ir, impulseResponse.getNumSamples());
    }
}


//==============================================================================
void EarlyReflectionsAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    // CONV
    mConvolutionManager[0].setBufferSize(samplesPerBlock);
    mConvolutionManager[1].setBufferSize(samplesPerBlock);
    
    
    //FILTER
    
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    reflections.prepare(spec);
    absorption.prepareFilter(spec);
    
    reflections.setSampleRate(sampleRate);
    
    predelayLine.reset();
    predelayLine.prepare(spec);
    
    allPass1.setSampleRate(sampleRate);
    allPass1.prepareFilter(spec);
    allPass2.setSampleRate(sampleRate);
    allPass2.prepareFilter(spec);
    allPass3.setSampleRate(sampleRate);
    allPass3.prepareFilter(spec);
    allPass4.setSampleRate(sampleRate);
    allPass4.prepareFilter(spec);
    allPass5.setSampleRate(sampleRate);
    allPass5.prepareFilter(spec);
    allPass6.setSampleRate(sampleRate);
    allPass6.prepareFilter(spec);
    
    updateMicCartesianCoordinates();
    updateSourceCartesianCoordinates();
    
    scratchBuffer.setSize (getNumInputChannels(), samplesPerBlock);
    
}

void EarlyReflectionsAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EarlyReflectionsAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
    
    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    
    return true;
#endif
}
#endif






void EarlyReflectionsAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    int faces = 6;
    
    for(int i = 0; i<faces; i++){
        outBuffer[i]= AudioBuffer<float>(buffer.getNumChannels(), buffer.getNumSamples());
    }
    
    
    // TO DO - FOR CPU? IF ROOMX IS NOT EQUAL TO SLIDER THEN DO THIS
    reflections.setSpeedOfSound(temp);
    reflections.setSize(roomX.getValue(), roomY.getValue(), roomZ.getValue());
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    
    auto inputBlock = dsp::AudioBlock<float>(buffer);
    
  
    for(int i = 0; i<faces; i++){
        outputBlock[i] = dsp::AudioBlock<float>(outBuffer[i]);
    }
    
    reflections.update(materialFrontBack, materialRightLeft, materialCeilingFloor);
    reflections.processBlock(inputBlock,outputBlock[0], outputBlock[1], outputBlock[2], outputBlock[3], outputBlock[4], outputBlock[5]);
    
    allPass1.updateFilter();
    allPass2.updateFilter();
    allPass3.updateFilter();
    allPass4.updateFilter();
    allPass5.updateFilter();
    allPass6.updateFilter();

    // apf on/off button
    if (apfOnOff){
        allPass1.processBlock(outputBlock[0]);
        allPass2.processBlock(outputBlock[1]);
        allPass3.processBlock(outputBlock[2]);
        allPass4.processBlock(outputBlock[3]);
        allPass5.processBlock(outputBlock[4]);
        allPass6.processBlock(outputBlock[5]);

    } else {
        
    }
    
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel){
        
        // create extra audio buffer
        AudioSampleBuffer tmpBuffer (scratchBuffer.getArrayOfWritePointers(), buffer.getNumChannels(), buffer.getNumSamples());
        
        // fill buffer with tmpbuffer with data from the main buffer
        tmpBuffer.copyFrom(channel, 0, buffer, channel, 0, buffer.getNumSamples());
        
        // create float pointer?? with the channel data from the main buffer
        float*    channelData = buffer.getWritePointer (channel);
        // and with the tmp buffer (should be identical as float* channelData then
         float*    channelDataTemp = tmpBuffer.getWritePointer (channel);
        
        // convolution
        juce::ScopedTryLock tryLock(mLoadingLock);
            
            if (tryLock.isLocked())
            {
                
                // perform convolution
                mConvolutionManager[channel].processInput(channelDataTemp);
                
                // get output from convolution
                const float* y = mConvolutionManager[channel].getOutputBuffer();
                
                // write to the float pointer??
                memcpy(channelDataTemp, y, buffer.getNumSamples() * sizeof(float));
                
            } else{
                buffer.clear();
            }
        


        // sample-by-sample
        for (int sample = 0 ; sample < buffer.getNumSamples(); ++sample){
        
            // set position of source, mic, and calc junctions
            reflections.setPositions(sourceXLim,sourceYLim,micXLim,micYLim);
            
            float tailGain = 1-reflections.sourceMicStereoGain(channel);
            // direct sound on/off button
            if(directSoundOnOff){
                directSound = inputBlock.getSample(channel,sample)*reflections.sourceMicStereoGain(channel);
            } else {
                directSound = 0.f;
            }
            
          
            
            getEarlyReflections(channel, sample);
            
            
          
            // add direct sound with all 6 reflections
            if (erOnOff){
                directAndER =  directSound + frontReflection + backReflection + rightReflection + leftReflection + ceilingReflection + floorReflection;

            } else {
                directAndER =  directSound;

            }
            
            
            
          
                convolutedSignal = tmpBuffer.getSample(channel, sample);

          
            
          
            
            
            
            
            // delay the channelDataTemp signal
             predelayLine.pushSample(channel, convolutedSignal);
             convolutedSignal = predelayLine.popSample(channel, reflections.largestDelay()-reflections.micToSourceDelay);
            
            
            if (tailOnOff){
                directAndERAndTail = directAndER + tailGain*convolutedSignal;;

            } else {
                directAndERAndTail = directAndER;
            }
            // write to the buffer
            buffer.setSample(channel, sample, directAndERAndTail);
            
        }
        
  
        
    }
}


//==============================================================================
bool EarlyReflectionsAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EarlyReflectionsAudioProcessor::createEditor()
{
    return new EarlyReflectionsAudioProcessorEditor (*this);
}

//==============================================================================
void EarlyReflectionsAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // CONVO
    XmlElement xml("STATEINFO");
    xml.setAttribute("impulseResponseFilePath", mImpulseResponseFilePath);
    copyXmlToBinary(xml, destData);
    
}

void EarlyReflectionsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    
    String impulseResponseFilePath = xml->getStringAttribute("impulseResponseFilePath", "");
    juce::File ir(impulseResponseFilePath);
    AudioFormatManager manager;
    manager.registerBasicFormats();
    juce::ScopedPointer<AudioFormatReader> formatReader = manager.createReaderFor(ir);
    AudioSampleBuffer sampleBuffer(formatReader->numChannels, formatReader->lengthInSamples);
    formatReader->read(&sampleBuffer, 0, formatReader->lengthInSamples, 0, 1, 1);
    setImpulseResponse(sampleBuffer, impulseResponseFilePath);}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter(){
    return new EarlyReflectionsAudioProcessor();
}


void EarlyReflectionsAudioProcessor::updateMicPolarCoordinates(){
    //   double mMic = (double)micX.getValue() - 0.5*(double)roomX.getValue();
    // micPolDist.setValue(sqrt(pow(mMic, 2) + pow((double)micY.getValue(), 2)));
    // micPolAng.setValue(std::atan(mMic / (double)micY.getValue()));
}

void EarlyReflectionsAudioProcessor::updateMicCartesianCoordinates(){
    micX.setValue(0.5 * (double)roomX.getValue() + (double)micPolDist.getValue() * std::sin((double)micPolAng.getValue()));
    micY.setValue((double)micPolDist.getValue() * std::cos((double)micPolAng.getValue()));
}

void EarlyReflectionsAudioProcessor::updateSourcePolarCoordinates(){
    double mSource = (double)sourceX.getValue() - 0.5*(double)roomX.getValue();
    sourcePolDist.setValue(sqrt(pow(mSource, 2) + pow((double)sourceY.getValue(), 2)));
    sourcePolAng.setValue(std::atan(mSource / (double)sourceY.getValue()));
}

void EarlyReflectionsAudioProcessor::updateSourceCartesianCoordinates(){
    sourceX.setValue(0.5 * (double)roomX.getValue() + (double)sourcePolDist.getValue() * std::sin((double)sourcePolAng.getValue()));
    sourceY.setValue((double)sourcePolDist.getValue() * std::cos((double)sourcePolAng.getValue()));
}

void EarlyReflectionsAudioProcessor::parameterChanged(const String &parameterID, float newValue){
    
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xMaterialFrontBack))){
        materialFrontBack = newValue;
    }
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xMaterialRightLeft))){
        materialRightLeft = newValue;
    }
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xMaterialCeilingFloor))){
        materialCeilingFloor = newValue;
    }
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xTemp))){
        temp = newValue;
    }
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xRoomX))){
        roomX = newValue;
        //updateSourceCartesianCoordinates();
        // updateMicCartesianCoordinates();
        
    }
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xRoomY))){
        roomY = newValue;
    }
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xRoomZ))){
        roomZ = newValue;
    }
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xMicX))){
        micX = newValue;
    }
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xMicY))){
        micY = newValue;
    }
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xSourceX))){
        sourceX = newValue;
    }
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xSourceY))){
        sourceY = newValue;
    }
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xMicPolDist))){
        updateMicCartesianCoordinates();
    }
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xMicPolAng))){
        updateMicCartesianCoordinates();
    }
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xSourcePolDist))){
        updateSourceCartesianCoordinates();
    }
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xSourcePolAng))){
        updateSourceCartesianCoordinates();
    }
    
    
    
    
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xmButtonChooseIR))){
        if (newValue == 0){
            FileChooser fchooser("Select Impulse Response");
            if (fchooser.browseForFileToOpen())
            {
                File ir = fchooser.getResult();
                FileInputStream irInputStream(ir);
                AudioFormatManager manager;
                manager.registerBasicFormats();
                juce::ScopedPointer<AudioFormatReader> formatReader = manager.createReaderFor(ir);
                AudioSampleBuffer sampleBuffer(formatReader->numChannels, formatReader->lengthInSamples);
                formatReader->read(&sampleBuffer, 0, formatReader->lengthInSamples, 0, 1, 1);
                
                this->setImpulseResponse(sampleBuffer, ir.getFullPathName());
                
            }
            
        }
    }
    
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xDirectSoundButton))){
        if (newValue == 1){
            directSoundOnOff = true;
        } else {
            directSoundOnOff = false;
        }
    }
    
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xAllPassButton))){
        if (newValue == 1){
            apfOnOff = true;
        } else {
            apfOnOff = false;
        }
    }
    
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xFiltersButton))){
        if (newValue == 1){
            reflections.filtersOnOff = true;
        } else {
            reflections.filtersOnOff = false;
        }
    }
    
    sendChangeMessage();
    
    if((double)sourceX.getValue() <= 0.01){
        sourceXLim = 0.01;
    } else if ((double)sourceX.getValue() >= ((double)roomX.getValue()-0.01f)){
        sourceXLim = ((double)roomX.getValue()-0.01f);
    } else {
        sourceXLim = ((double)sourceX.getValue());
    }
    
    if((double)sourceY.getValue() <= 0.01){
        sourceYLim = 0.01;
    } else if ((double)sourceY.getValue() >= ((double)roomY.getValue()-0.01f)){
        sourceYLim = ((double)roomY.getValue()-0.01f);
    } else {
        sourceYLim= ((double)sourceY.getValue());
    }
    
    if((double)micX.getValue() <= 0.01){
        micXLim = (0.01);
    } else if ((double)micX.getValue() >= ((double)roomX.getValue()-0.01f)){
        micXLim = ((double)roomX.getValue()-0.01f);
    } else {
        micXLim = ((double)micX.getValue());
    }
    
    if((double)micY.getValue() <= 0.01){
        micYLim = (0.01);
    } else if ((double)micY.getValue() >= ((double)roomY.getValue()-0.01f)){
        micYLim = ((double)roomY.getValue()-0.01f);
    } else {
        micYLim = ((double)micY.getValue());
    }
    
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xConvolutionOnOff))){
        if (newValue == 1){
            convOnOff = true;
        } else {
            convOnOff = false;
        }
    }
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xEarlyReflectionsButton))){
        if (newValue == 1){
            erOnOff = true;
        } else {
            erOnOff = false;
        }
    }
    
    
    if(parameterID.equalsIgnoreCase(getParameterIdentifier(ParameterIDIndex::xTailButton))){
        if (newValue == 1){
            tailOnOff = true;
        } else {
            tailOnOff = false;
        }
    }
  
}

void EarlyReflectionsAudioProcessor::getEarlyReflections(int channel, int sample){
    frontReflection = outputBlock[0].getSample(channel,sample)*reflections.junctionMicStereoGain(0, channel)/fmax(reflections.getDist(0),0.4);
    
    backReflection = outputBlock[1].getSample(channel,sample)*reflections.junctionMicStereoGain(1, channel)/fmax(reflections.getDist(1),0.4);
    
    rightReflection = outputBlock[2].getSample(channel,sample)*reflections.junctionMicStereoGain(2, channel)/fmax(reflections.getDist(2),0.4);
    
    leftReflection = outputBlock[3].getSample(channel,sample)*reflections.junctionMicStereoGain(3, channel)/fmax(reflections.getDist(3),0.4);
    
    ceilingReflection = outputBlock[4].getSample(channel,sample)*reflections.junctionMicStereoGain(4, channel)/fmax(reflections.getDist(4),0.4);
    
    floorReflection = outputBlock[5].getSample(channel,  sample)*reflections.junctionMicStereoGain(5, channel)/fmax(reflections.getDist(5),0.4);
    
}

void EarlyReflectionsAudioProcessor::valueChanged(Value& sourceValue)
{
    
    
    /*
     if (sourceValue.refersToSameSourceAs(micX) || sourceValue.refersToSameSourceAs(micY))
     {
     updateMicPolarCoordinates();
     }
     
     if (sourceValue.refersToSameSourceAs(sourceX) || sourceValue.refersToSameSourceAs(sourceY))
     {
     updateSourcePolarCoordinates();
     }
     
     if (sourceValue.refersToSameSourceAs(micPolDist) || sourceValue.refersToSameSourceAs(micPolAng))
     {
     updateMicCartesianCoordinates();
     }
     
     if (sourceValue.refersToSameSourceAs(sourcePolDist) || sourceValue.refersToSameSourceAs(sourcePolAng))
     {
     updateSourceCartesianCoordinates();
     }
     
     */
    
}







