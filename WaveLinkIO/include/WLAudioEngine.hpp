//
//  WLAudioEngine.hpp
//  WaveLinkIO Kernel
//
//  Copyright (c) 2024 NH. All rights reserved.
//
//  @LICENSE_HEADER_START@
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
//  @LICENSE_HEADER_END@
//

#ifndef WL_AUDIO_ENGINE_H
#define WL_AUDIO_ENGINE_H

#include "IOAudioEngine.h" // Include the header file of the base class
#include "VirtualAudioDeviceWrapper.hpp"

class WLAudioEngine : public IOAudioEngine {
public:
    // Constructor
    WLAudioEngine();

    // Destructor
    virtual ~WLAudioEngine();

    // Override the base class functions
    virtual IOReturn resetAudioEngineState() override;
    virtual IOReturn clipOutputSamples(const void *mixBuf, void *sampleBuf, UInt32 firstSampleFrame, UInt32 numSampleFrames, const IOAudioStreamFormat *streamFormat) override;
    virtual IOReturn convertInputSamples(const void *sampleBuf, void *destBuf, UInt32 firstSampleFrame, UInt32 numSampleFrames, const IOAudioStreamFormat *streamFormat) override;
};

#endif // WL_AUDIO_ENGINE_H
