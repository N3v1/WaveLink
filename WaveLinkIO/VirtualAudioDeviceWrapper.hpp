//
//  VirtualAudioDeviceWrapper.hpp
//  WaveLinkIO
//
//  Created by Nevio Hirani on 21.05.24.
//

#ifndef VIRTUAL_AUDIO_DEVICE_WRAPPER_H
#define VIRTUAL_AUDIO_DEVICE_WRAPPER_H

#include <mach/mach_types.h>

#ifdef __cplusplus
extern "C" {
#endif

    struct IOService;

    kern_return_t VirtualAudioDevice_start(struct IOService *provider);
    void VirtualAudioDevice_stop(struct IOService *provider);
    struct IOService* waitForIOService(const char* serviceName);

#ifdef __cplusplus
}
#endif

#endif // VIRTUAL_AUDIO_DEVICE_WRAPPER_H
