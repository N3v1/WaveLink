//
//  VirtualAudioDeviceWrapper.cpp
//  WaveLinkIO
//
//  Created by Nevio Hirani on 21.05.24.
//

#include <IOKit/IOLib.h>
//#include <IOKit/IOService.h>
#include "VirtualAudioDevice.hpp"

extern "C" {
    kern_return_t VirtualAudioDevice_start(IOService *provider) {
        VirtualAudioDevice *audioDevice = new VirtualAudioDevice;
        if (audioDevice && audioDevice->init(nullptr)) {
            audioDevice->attach(provider);
            audioDevice->start(provider);
            return KERN_SUCCESS;
        }
        if (audioDevice) {
            audioDevice->release(); // Use release instead of delete
        }
        return KERN_FAILURE;
    }

    void VirtualAudioDevice_stop(IOService *provider) {
        // Implement the stop logic if needed
        // Normally, you would call a stop method on the VirtualAudioDevice and release it
    }

    IOService* waitForIOService(const char* serviceName) {
        return IOService::waitForService(IOService::serviceMatching(serviceName));
    }
}
