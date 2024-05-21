//
//  VirtualAudioDeviceWrapper.cpp
//  WaveLinkIO
//
//  Created by Nevio Hirani on 21.05.24.
//

// VirtualAudioDeviceWrapper.cpp
#include <IOKit/IOLib.h>
#include <IOKit/IOService.h>
#include "VirtualAudioDevice.hpp"

extern "C" {
    kern_return_t VirtualAudioDevice_start(struct IOService* provider) {
        VirtualAudioDevice *audioDevice = new VirtualAudioDevice;
        if (audioDevice && audioDevice->init(nullptr)) {
            audioDevice->attach(provider);
            audioDevice->start(provider);
            return KERN_SUCCESS;
        }
        delete audioDevice;
        return KERN_FAILURE;
    }

    void VirtualAudioDevice_stop(struct IOService* provider) {
        // Implement the stop logic if needed
    }

    struct IOService* waitForIOService(const char* serviceName) {
        return IOService::waitForService(IOService::serviceMatching(serviceName));
    }
}
