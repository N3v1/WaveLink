//
//  VirtualAudioDevice.hpp
//  WaveLinkIO
//
//  Created by Nevio Hirani on 21.05.24.
//

#ifndef VIRTUALAUDIODEVICE_HPP
#define VIRTUALAUDIODEVICE_HPP

#include <IOKit/audio/IOAudioDevice.h>
#include <IOKit/audio/IOAudioEngine.h>

class VirtualAudioEngine;

class VirtualAudioDevice : public IOAudioDevice {
    OSDeclareDefaultStructors(VirtualAudioDevice)

public:
    bool initHardware(IOService *provider) override;
};

class VirtualAudioEngine : public IOAudioEngine {
    OSDeclareDefaultStructors(VirtualAudioEngine)

public:
    bool initHardware(IOService *provider) override;
    IOReturn performAudioEngineStart() override;
    IOReturn performAudioEngineStop() override;
    void free() override;
};

#endif // VIRTUALAUDIODEVICE_HPP
