//
//  VirtualAudioDevice.cpp
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
 * @file VirtualAudioDevice.cpp
 * @brief Implementation of the VirtualAudioDevice and VirtualAudioEngine classes.
 */

#include "VirtualAudioDevice.hpp"
#include <IOKit/IOLib.h>

#define super IOAudioDevice
OSDefineMetaClassAndStructors(VirtualAudioDevice, IOAudioDevice)

bool VirtualAudioDevice::initHardware(IOService *provider) {
    if (!super::initHardware(provider)) {
        return false;
    }

    VirtualAudioEngine *audioEngine = new VirtualAudioEngine;
    if (!audioEngine || !audioEngine->init(nullptr)) {
        if (audioEngine) {
            audioEngine->release();
        }
        return false;
    }

    audioEngine->attach(this);
    audioEngine->start(this);
    activateAudioEngine(audioEngine);
    audioEngine->release();

    return true;
}

#define super IOAudioEngine
OSDefineMetaClassAndStructors(VirtualAudioEngine, IOAudioEngine)

bool VirtualAudioEngine::initHardware(IOService *provider) {
    if (!super::initHardware(provider)) {
        return false;
    }

    // Define the audio stream format for 16 channels
    IOAudioStreamFormat format = {
        .fNumChannels = 16,
        .fSampleFormat = kIOAudioStreamSampleFormatLinearPCM,
        .fNumericRepresentation = kIOAudioStreamNumericRepresentationSignedInt,
        .fBitDepth = 16,
        .fBitWidth = 16,
        .fAlignment = kIOAudioStreamAlignmentHighByte,
        .fByteOrder = kIOAudioStreamByteOrderBigEndian,
        .fIsMixable = true,
        .fDriverTag = 0
    };

    IOAudioSampleRate sampleRate;
    sampleRate.whole = 44100;
    sampleRate.fraction = 0;

    setSampleRate(&sampleRate);
    setNumSampleFramesPerBuffer(512); // Set buffer size

    IOAudioStream *audioStream = new IOAudioStream;
    if (!audioStream || !audioStream->initWithAudioEngine(this, kIOAudioStreamDirectionOutput, 1)) {
        if (audioStream) {
            audioStream->release();
        }
        return false;
    }

    audioStream->setFormat(&format, false);
    addAudioStream(audioStream);
    audioStream->release();

    return true;
}

IOReturn VirtualAudioEngine::performAudioEngineStart() {
    // Start audio processing
    return kIOReturnSuccess;
}

IOReturn VirtualAudioEngine::performAudioEngineStop() {
    // Stop audio processing
    return kIOReturnSuccess;
}

void VirtualAudioEngine::free() {
    // Free resources
    super::free();
}

IOReturn VirtualAudioEngine::resetAudioEngineState() {
    // Reset the state of the audio engine
    return kIOReturnSuccess;
}

UInt32 VirtualAudioEngine::getCurrentSampleFrame() {
    // Return the current sample frame
    return 0;
}

IOReturn VirtualAudioEngine::clipOutputSamples(const void *mixBuf, void *sampleBuf, UInt32 firstSampleFrame, UInt32 numSampleFrames, const IOAudioStreamFormat *streamFormat) {
    // Clip output samples before sending to the output device
    return kIOReturnSuccess;
}

IOReturn VirtualAudioEngine::convertInputSamples(const void *sampleBuf, void *destBuf, UInt32 firstSampleFrame, UInt32 numSampleFrames, const IOAudioStreamFormat *streamFormat) {
    // Convert input samples before processing by the audio engine
    return kIOReturnSuccess;
}

extern "C" kern_return_t VirtualAudioDevice_start(IOService *provider) {
    VirtualAudioDevice *audioDevice = new VirtualAudioDevice;
    if (audioDevice && audioDevice->init(nullptr)) { // Call init without arguments
        audioDevice->attach(provider);
        audioDevice->start(provider);
        return KERN_SUCCESS;
    }

    if (audioDevice) {
        audioDevice->release();
    }

    return KERN_FAILURE;
}

extern "C" void VirtualAudioDevice_stop(IOService *provider) {
    VirtualAudioDevice *audioDevice = OSDynamicCast(VirtualAudioDevice, IOService::getMatchingServices(IOService::serviceMatching("VirtualAudioDevice")));
    if (audioDevice) {
        audioDevice->stop(provider);
        audioDevice->detach(provider);
        audioDevice->release();
    }
}
