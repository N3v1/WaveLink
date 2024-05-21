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
 *
 * This file contains the declarations for the VirtualAudioDevice and VirtualAudioEngine
 * classes, which are used to create a virtual audio device and its associated audio
 * engine for macOS using the IOKit framework.
 */

#ifndef VIRTUALAUDIODEVICE_HPP
#define VIRTUALAUDIODEVICE_HPP

#include <IOKit/audio/IOAudioDevice.h>
#include <IOKit/audio/IOAudioEngine.h>
#include <IOKit/audio/IOAudioStream.h>

/**
 * @class VirtualAudioDevice
 * @brief Represents the virtual audio device.
 *
 * The VirtualAudioDevice class is responsible for initializing and managing
 * the virtual audio device. It extends the IOAudioDevice class provided by IOKit.
 */
class VirtualAudioDevice : public IOAudioDevice {
    OSDeclareDefaultStructors(VirtualAudioDevice)

public:
    /**
     * @brief Initializes the hardware for the virtual audio device.
     *
     * This method is called to initialize the hardware for the virtual audio device.
     * It sets up the audio engine and attaches it to the device.
     *
     * @param provider The IOService provider for the device.
     * @return true if the hardware was successfully initialized, false otherwise.
     */
    bool initHardware(IOService *provider) override;
};

/**
 * @class VirtualAudioEngine
 * @brief Represents the virtual audio engine.
 *
 * The VirtualAudioEngine class is responsible for handling the audio processing
 * for the virtual audio device. It extends the IOAudioEngine class provided by IOKit.
 */
class VirtualAudioEngine : public IOAudioEngine {
    OSDeclareDefaultStructors(VirtualAudioEngine)

public:
    /**
     * @brief Initializes the hardware for the virtual audio engine.
     *
     * This method is called to initialize the hardware for the virtual audio engine.
     * It sets up the audio format and buffer size for the engine.
     *
     * @param provider The IOService provider for the engine.
     * @return true if the hardware was successfully initialized, false otherwise.
     */
    bool initHardware(IOService *provider) override;

    /**
     * @brief Starts the audio engine.
     *
     * This method is called to start the audio engine and begin audio processing.
     *
     * @return kIOReturnSuccess if the engine started successfully, an error code otherwise.
     */
    IOReturn performAudioEngineStart() override;

    /**
     * @brief Stops the audio engine.
     *
     * This method is called to stop the audio engine and cease audio processing.
     *
     * @return kIOReturnSuccess if the engine stopped successfully, an error code otherwise.
     */
    IOReturn performAudioEngineStop() override;

    /**
     * @brief Frees the resources used by the audio engine.
     *
     * This method is called to free any resources allocated by the audio engine.
     */
    void free() override;

    /**
     * @brief Resets the state of the audio engine.
     *
     * This method is called to reset the state of the audio engine.
     *
     * @return kIOReturnSuccess if the engine state was reset successfully, an error code otherwise.
     */
    virtual IOReturn resetAudioEngineState() /*override*/;

    /**
     * @brief Gets the current sample frame.
     *
     * This method returns the current sample frame being processed by the audio engine.
     *
     * @return The current sample frame.
     */
    virtual UInt32 getCurrentSampleFrame() override;

    /**
     * @brief Clips the output samples.
     *
     * This method is called to clip the output samples before they are sent to the output device.
     *
     * @param mixBuf The buffer containing the mixed audio samples.
     * @param sampleBuf The buffer where the clipped audio samples will be stored.
     * @param firstSampleFrame The first sample frame to process.
     * @param numSampleFrames The number of sample frames to process.
     * @param streamFormat The format of the audio stream.
     * @return kIOReturnSuccess if the samples were clipped successfully, an error code otherwise.
     */
    virtual IOReturn clipOutputSamples(const void *mixBuf, void *sampleBuf, UInt32 firstSampleFrame, UInt32 numSampleFrames, const IOAudioStreamFormat *streamFormat) /*override*/;

    /**
     * @brief Converts the input samples.
     *
     * This method is called to convert the input samples before they are processed by the audio engine.
     *
     * @param sampleBuf The buffer containing the input audio samples.
     * @param destBuf The buffer where the converted audio samples will be stored.
     * @param firstSampleFrame The first sample frame to process.
     * @param numSampleFrames The number of sample frames to process.
     * @param streamFormat The format of the audio stream.
     * @return kIOReturnSuccess if the samples were converted successfully, an error code otherwise.
     */
    virtual IOReturn convertInputSamples(const void *sampleBuf, void *destBuf, UInt32 firstSampleFrame, UInt32 numSampleFrames, const IOAudioStreamFormat *streamFormat) /*override*/;
};

extern "C" kern_return_t VirtualAudioDevice_start(IOService *provider);
extern "C" void VirtualAudioDevice_stop(IOService *provider);

#endif // VIRTUALAUDIODEVICE_HPP
