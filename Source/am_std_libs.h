/*
  ==============================================================================

    am_std_libs.h
    Created: 12 Jul 2017 9:42:23am
    Author:  Emanuele Parravicini

  ==============================================================================
*/

#pragma once

#include <cstddef>
#include <cmath>
#include <math.h>
#include <ctime>
#include <queue>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <complex>
#include <string>

#ifndef _denormals_
#define _denormals_

#define undenormalise(x) { (x) += 0.1f; (x) -= 0.1f; }

#endif


#ifndef SWAM_BUILD_PLUGIN
    #include "../JuceLibraryCode/JuceHeader.h"
#endif

#define SWAM_FILE_LOG      juce::FileLogger::getSystemLogFileFolder().getChildFile("Audio Modeling").getChildFile("SWAM.log")

class GlobalDebug
{
public:

	static GlobalDebug& getInstance()
	{
		static GlobalDebug instance;
		return instance;
	}

	GlobalDebug()
    {
        // swamLogFile.createDefaultAppLogger((SWAM_FILE_LOG).getFullPathName(), "SWAM.log", "SWAM Logger File");
    };
    
	~GlobalDebug() {};

	float debug1 = 0;
	float debug2 = 0;
	float debug3 = 0;
    
    float sliderDebug1 = 0;
    float sliderDebug2 = 0;
    float sliderDebug3 = 0;
	float sliderDebug4 = 0;
	float sliderDebug5 = 0;
    
    juce::String msg = "";
    
    /**
        - swamLogFile instructions:
     
        [1] in am_Globals.h set CREATE_LOG_FILE 1
        [2] to write -> if(CREATE_LOG_FILE) GlobalDebug::getInstance().swamLogFile.logMessage("msg")
     
        - path:

        On Windows
        c:\\Documents and Settings\\username\\Application Data\\Audio Modeling\\SWAM.log

        On the Mac
        ~/Library/Logs/Audio Modeling/SWAM.log
    */
    
    // juce::FileLogger swamLogFile { SWAM_FILE_LOG, "SWAM Logger File", 1024 };
};
