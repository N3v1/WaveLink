//
//  WaveLinkIO.c
//  WaveLinkIO
//
//  Created by NH on 21.05.24.
//

/**
 * @file VirtualAudioDriver.c
 * @brief Kernel module start/stop functions.
 */

#include <mach/mach_types.h>
#include <IOKit/IOLib.h>
#include <IOKit/IOService.h>

class VirtualAudioDevice;
extern "C" {
    kern_return_t VirtualAudioDevice_start(IOService *provider);
    void VirtualAudioDevice_stop(IOService *provider);
}

/**
 * @brief The start function.
 * @param ki Pointer to the kernel module information.
 * @param d Pointer to the module-specific data.
 * @return KERN_SUCCESS on success, KERN_FAILURE on failure.
 */
kern_return_t WaveLinkIO_start(kmod_info_t * ki, void *d) {
    IOLog("WaveLinkIO: Loading\n");
    IOService *service = IOService::waitForService(IOService::serviceMatching("IOResources"));
    if (service) {
        return VirtualAudioDevice_start(service);
    }
    return KERN_FAILURE;
}

/**
 * @brief The stop function.
 * @param ki Pointer to the kernel module information.
 * @param d Pointer to the module-specific data.
 * @return KERN_SUCCESS on success.
 */
kern_return_t WaveLinkIO_stop(kmod_info_t *ki, void *d) {
    IOLog("WaveLinkIO: Unloading\n");
    IOService *service = IOService::waitForService(IOService::serviceMatching("IOResources"));
    if (service) {
        VirtualAudioDevice_stop(service);
    }
    return KERN_SUCCESS;
}

// Define the kernel module start/stop functions
KMOD_EXPLICIT_DECL(com.example.WaveLinkIO, "1.0", WaveLinkIO_start, WaveLinkIO_stop)
__attribute__((visibility("default"))) kmod_start_func_t *_realmain = WaveLinkIO_start;
__attribute__((visibility("default"))) kmod_stop_func_t *_antimain = WaveLinkIO_stop;
__attribute__((visibility("default"))) int _kext_apple_cc = __APPLE_CC__;
