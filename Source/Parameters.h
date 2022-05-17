
#pragma once

#include <JuceHeader.h>

static StringArray ParameterID {
    
    "materialFrontBack",
    "materialRightLeft",
    "materialCeilingFloor",
    "temp",
    "roomX",
    "roomY",
    "roomZ",
    "micX",
    "micY",
    "sourceX",
    "sourceY",
    "micPolDist",
    "micPolAng",
    "sourcePolDist",
    "sourcePolAng",
    "allPassButton",
    "directSoundButton",
    "filtersButton",
    "mButtonChooseIR",
    "convolutionOnOff",
    "earlyReflectionsButton",
    "tailButton"

};

enum ParameterIDIndex {
    
    xMaterialFrontBack,
    xMaterialRightLeft,
    xMaterialCeilingFloor,
    xTemp,
    xRoomX,
    xRoomY,
    xRoomZ,
    xMicX,
    xMicY,
    xSourceX,
    xSourceY,
    xMicPolDist,
    xMicPolAng,
    xSourcePolDist,
    xSourcePolAng,
    xAllPassButton,
    xDirectSoundButton,
    xFiltersButton,
    xmButtonChooseIR,
    xConvolutionOnOff,
    xEarlyReflectionsButton,
    xTailButton
};

static String getParameterIdentifier(ParameterIDIndex paramIndex){return ParameterID.getReference(paramIndex);}

static AudioProcessorValueTreeState::ParameterLayout getParameterLayout(){
    std::vector<std::unique_ptr<AudioProcessorValueTreeState::Parameter>> parameters;
    
    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xMaterialFrontBack),
                                                "Front/Back Wall Material",
                                                "",
                                                {1.f, 8.f, 1.f},
                                                1.f,
                                                [](float value) -> String{
            if(value<1.5f) return "Carpet: heavy on concrete";
            if(value<2.5f) return "Carpet: heavy on 40-oz hair felt";
            if(value<3.5f) return "Acoustical tile, 3/4-in thick";
            if(value<4.5f) return "Concrete block, coarse";
            if(value<5.5f) return "Wood";
            if(value<6.5f) return "Glass: large panes, heavy glass";
            if(value<7.5f) return "Plywood panel: 3/8-in thick";
            else return "Perforated Panel. Perf: 1.4%";
        
    }, [](String s) -> float {return s.getFloatValue();},
false, true, true, AudioProcessorParameter::Category::genericParameter,false)));
    
    
    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xMaterialRightLeft),
                                                "Right/Left Wall Material",
                                                "",
                                                {1.f, 8.f, 1.f},
                                                1.f,
                                                [](float value) -> String{
            if(value<1.5f) return "Carpet: heavy on concrete";
            if(value<2.5f) return "Carpet: heavy on 40-oz hair felt";
            if(value<3.5f) return "Acoustical tile, 3/4-in thick";
            if(value<4.5f) return "Concrete block, coarse";
            if(value<5.5f) return "Wood";
            if(value<6.5f) return "Glass: large panes, heavy glass";
            if(value<7.5f) return "Plywood panel: 3/8-in thick";
            else return "Perforated Panel. Perf: 1.4%";
        
    }, [](String s) -> float {return s.getFloatValue();},
false, true, true, AudioProcessorParameter::Category::genericParameter,false)));

    
    
    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xMaterialCeilingFloor),
                                                "Ceiling/Floor Material",
                                                "",
                                                {1.f, 8.f, 1.f},
                                                1.f,
                                                [](float value) -> String{
            if(value<1.5f) return "Carpet: heavy on concrete";
            if(value<2.5f) return "Carpet: heavy on 40-oz hair felt";
            if(value<3.5f) return "Acoustical tile, 3/4-in thick";
            if(value<4.5f) return "Concrete block, coarse";
            if(value<5.5f) return "Wood";
            if(value<6.5f) return "Glass: large panes, heavy glass";
            if(value<7.5f) return "Plywood panel: 3/8-in thick";
            else return "Perforated Panel. Perf: 1.4%";
        
    }, [](String s) -> float {return s.getFloatValue();},
false, true, true, AudioProcessorParameter::Category::genericParameter,false)));

    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xTemp),
                                                "Temperature",
                                                "Celcius",
                                                {-40.f, 100.f, 1.f},
                                                20.f,
                                                [](float value) -> String{
    return String(value,0);
        
    }, [](String s) -> float {return s.getFloatValue();},
false, true, true, AudioProcessorParameter::Category::genericParameter,false)));
    
    
    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xRoomX),
                                                "Room x (width)",
                                                "m",
                                                {0.3f, 15.f, 0.01f},
                                                10.f,
                                                [](float value) -> String{
    
        return String(value,0);
        
    }, [](String s) -> float {return s.getFloatValue();},
false, true, false, AudioProcessorParameter::Category::genericParameter,false)));
    
    
    
    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xRoomY),
                                                "Room z (depth)",
                                                "",
                                                {0.3f, 15.f, 0.01f},
                                                10.f,
                                                [](float value) -> String{
    
        return String(value,2);
        
    }, [](String s) -> float {return s.getFloatValue();},
    false, true, false, AudioProcessorParameter::Category::genericParameter,false)));
    

    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xRoomZ),
                                                "Room y (height)",
                                                "",
                                                {1.1f, 15.f, 0.01f},
                                                5.f,
                                                [](float value) -> String{
        return String(value,2);
        
    }, [](String s) -> float {return s.getFloatValue();},
    false, true, false, AudioProcessorParameter::Category::genericParameter,false)));
    
    
    
    
    
    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xMicX),
                                                "Mic x",
                                                "",
                                                {0.01f, 15.f, 0.01f},
                                                2.f,
                                                [](float value) -> String{
        return String(value,2);
        
    }, [](String s) -> float {return s.getFloatValue();},
    false, true, false, AudioProcessorParameter::Category::genericParameter,false)));
    
    
    
    
    
    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xMicY),
                                                "Mic y",
                                                "",
                                                {0.01f, 15.f, 0.01f},
                                                4.f,
                                                [](float value) -> String{
        return String(value,2);
        
    }, [](String s) -> float {return s.getFloatValue();},
    false, true, false, AudioProcessorParameter::Category::genericParameter,false)));
    
    
    
    
    
    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xSourceX),
                                                "Source x",
                                                "",
                                                {0.01f, 15.f, 0.01f},
                                                7.f,
                                                [](float value) -> String{
        return String(value,2);
        
    }, [](String s) -> float {return s.getFloatValue();},
    false, true, false, AudioProcessorParameter::Category::genericParameter,false)));
    
    
    
    
    
    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xSourceY),
                                                "Source y",
                                                "",
                                                {0.01f, 15.f, 0.01f},
                                                5.f,
                                                [](float value) -> String{
        return String(value,2);
        
    }, [](String s) -> float {return s.getFloatValue();},
    false, true, false, AudioProcessorParameter::Category::genericParameter,false)));
    
    
    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xMicPolDist),
                                                "Mic Polar Distance",
                                                "",
                                                {0.01f, 50.f, 0.01f},
                                                5.f, //default value should be calculated based on value of the other slider
                                                [](float value) -> String{
        return String(value,2);
        
    }, [](String s) -> float {return s.getFloatValue();},
    false, true, false, AudioProcessorParameter::Category::genericParameter,false)));
    
    
    
    
    
    
    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xMicPolAng),
                                                "Mic Polar Angle",
                                                "",
                                                {-MathConstants<float>::halfPi+0.01, MathConstants<float>::halfPi-0.01, 0.01f},
                                                0.0f, //default value should be calculated based on value of the other slider
                                                [](float value) -> String{
        return String(value,2);
        
    }, [](String s) -> float {return s.getFloatValue();},
    false, true, false, AudioProcessorParameter::Category::genericParameter,false)));
    
    
    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xSourcePolDist),
                                                "Source Polar Distance",
                                                "",
                                                {0.01f, 50.f, 0.01f},
                                                20.f, //default value should be calculated based on value of the other slider
                                                [](float value) -> String{
        return String(value,2);
        
    }, [](String s) -> float {return s.getFloatValue();},
    false, true, false, AudioProcessorParameter::Category::genericParameter,false)));
    
    
    
    
    
    
    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xSourcePolAng),
                                                "Source Polar Angle",
                                                "",
                                                {-MathConstants<float>::halfPi+0.01, MathConstants<float>::halfPi-0.01, 0.01f},
                                                0, //default value should be calculated based on value of the other slider
                                                [](float value) -> String{
        return String(value,2);
        
    }, [](String s) -> float {return s.getFloatValue();},
    false, true, false, AudioProcessorParameter::Category::genericParameter,false)));
    
    
    
    
    //toggle switches
    
    
    
    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xAllPassButton),
                                                "All-pass on/off",
                                                "",
                                                {0.f, 1.f,1.f},
                                                1, //default value should be calculated based on value of the other slider
                                                [](float value) -> String{return String(value,1);}
                                                , [](String s) -> float {return s.getFloatValue();},
    false, true, true, AudioProcessorParameter::Category::genericParameter,true)));
    
    
    
    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xDirectSoundButton),
                                                "Direct sound on/off",
                                                "",
                                                {0.f, 1.f,1.f},
                                                1, //default value should be calculated based on value of the other slider
                                                [](float value) -> String{return String(value,1);}
                                                , [](String s) -> float {return s.getFloatValue();},
    false, true, true, AudioProcessorParameter::Category::genericParameter,true)));
    
    
    
    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xFiltersButton),
                                                "Filters on/off",
                                                "",
                                                {0.f, 1.f,1.f},
                                                1, //default value should be calculated based on value of the other slider
                                                [](float value) -> String{return String(value,1);}
                                                , [](String s) -> float {return s.getFloatValue();},
    false, true, true, AudioProcessorParameter::Category::genericParameter,true)));
    
    
    
    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xmButtonChooseIR),
                                                "Select room tail",
                                                "",
                                                {0.f, 1.f,1.f},
                                                1, //default value should be calculated based on value of the other slider
                                                [](float value) -> String{return String(value,1);}
                                                , [](String s) -> float {return s.getFloatValue();},
    false, true, true, AudioProcessorParameter::Category::genericParameter,true)));
    
    
    
    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xConvolutionOnOff),
                                                "Tail on/off",
                                                "",
                                                {0.f, 1.f,1.f},
                                                1, //default value should be calculated based on value of the other slider
                                                [](float value) -> String{return String(value,1);}
                                                , [](String s) -> float {return s.getFloatValue();},
    false, true, true, AudioProcessorParameter::Category::genericParameter,true)));
    

    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xEarlyReflectionsButton),
                                                "ER",
                                                "",
                                                {0.f, 1.f,1.f},
                                                1, //default value should be calculated based on value of the other slider
                                                [](float value) -> String{return String(value,1);}
                                                , [](String s) -> float {return s.getFloatValue();},
    false, true, true, AudioProcessorParameter::Category::genericParameter,true)));
    
    
    parameters.push_back(std::unique_ptr<AudioProcessorValueTreeState::Parameter>(new AudioProcessorValueTreeState::Parameter(getParameterIdentifier(xTailButton),
                                                "Tail",
                                                "",
                                                {0.f, 1.f,1.f},
                                                1, //default value should be calculated based on value of the other slider
                                                [](float value) -> String{return String(value,1);}
                                                , [](String s) -> float {return s.getFloatValue();},
    false, true, true, AudioProcessorParameter::Category::genericParameter,true)));
    
    
    
    return AudioProcessorValueTreeState::ParameterLayout(parameters.begin(),parameters.end());
    
}
