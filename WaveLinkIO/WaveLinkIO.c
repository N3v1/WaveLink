//
//  WaveLinkIO.c
//  WaveLinkIO
//
//  Created by Nevio Hirani on 21.05.24.
//

#include <mach/mach_types.h>
#include <IOKit/IOLib.h>
#include <IOKit/IOService.h>

class VirtualAudioDevice;
extern "C" {
    kern_return_t VirtualAudioDevice_start(IOService *provider);
    void VirtualAudioDevice_stop(IOService *provider);
}

// The start function
kern_return_t WaveLinkIO_start(kmod_info_t * ki, void *d) {
    IOLog("WaveLinkIO: Loading\n");
    IOService *service = IOService::waitForService(IOService::serviceMatching("IOResources"));
    if (service) {
        return VirtualAudioDevice_start(service);
    }
    return KERN_FAILURE;
}

// The stop function
kern_return_t WaveLinkIO_stop(kmod_info_t *ki, void *d) {
    IOLog("WaveLinkIO: Unloading\n");
    IOService *service = IOService::waitForService(IOService::serviceMatching("IOResources"));
    if (service) {
        VirtualAudioDevice_stop(service);
    }
    return KERN_SUCCESS;
}

// Define the kernel module start/stop functions
KMOD_EXPLICIT_DECL(com.nhsystems.WaveLinkIO, "1.0", WaveLinkIO_start, WaveLinkIO_stop)
__attribute__((visibility("default"))) kmod_start_func_t *_realmain = WaveLinkIO_start;
__attribute__((visibility("default"))) kmod_stop_func_t *_antimain = WaveLinkIO_stop;
__attribute__((visibility("default"))) int _kext_apple_cc = __APPLE_CC__;
