//
//  VirtualAudioDevice.hpp
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

/**
 * @file VirtualAudioDevice.hpp
 * @brief Declaration of the VirtualAudioDevice and VirtualAudioEngine classes.
 */

#ifndef VIRTUALAUDIODEVICE_HPP
#define VIRTUALAUDIODEVICE_HPP

#include <IOKit/audio/IOAudioDevice.h>
#include <IOKit/audio/IOAudioEngine.h>

class VirtualAudioEngine;

/**
 * @class VirtualAudioDevice
 * @brief Represents the virtual audio device.
 */
class VirtualAudioDevice : public IOAudioDevice {
    OSDeclareDefaultStructors(VirtualAudioDevice)
    
public:
    /**
     * @brief Initializes the hardware.
     * @param provider The service provider.
     * @return True if successful, false otherwise.
     */
    bool initHardware(IOService *provider) override;
};

/**
 * @class VirtualAudioEngine
 * @brief Represents the virtual audio engine.
 */
class VirtualAudioEngine : public IOAudioEngine {
    OSDeclareDefaultStructors(VirtualAudioEngine)

public:
    /**
     * @brief Initializes the hardware.
     * @param provider The service provider.
     * @return True if successful, false otherwise.
     */
    bool initHardware(IOService *provider) override;
    IOReturn performAudioEngineStart() override;
    IOReturn performAudioEngineStop() override;
    void free() override;

    IOReturn resetAudioEngineState() /*override*/;
    UInt32 getCurrentSampleFrame() override;
    IOReturn clipOutputSamples(const void *mixBuf, void *sampleBuf, UInt32 firstSampleFrame, UInt32 numSampleFrames, const IOAudioStreamFormat *streamFormat) /*override*/;
    IOReturn convertInputSamples(const void *sampleBuf, void *destBuf, UInt32 firstSampleFrame, UInt32 numSampleFrames, const IOAudioStreamFormat *streamFormat) /*override*/;
};

#endif // VIRTUALAUDIODEVICE_HPP
