//
//  WaveLinkIO.c
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
 * @file VirtualAudioDriver.c
 * @brief Kernel module start/stop functions.
 */

#include <mach/mach_types.h>
#include <IOKit/IOLib.h>
#include "VirtualAudioDeviceWrapper.hpp"

/**
 * @brief The start function.
 * @param ki Pointer to the kernel module information.
 * @param d Pointer to the module-specific data.
 * @return KERN_SUCCESS on success, KERN_FAILURE on failure.
 */
kern_return_t WaveLinkIO_start(kmod_info_t * ki, void *d) {
    IOLog("WaveLinkIO: Loading\n");
    struct IOService *service = waitForIOService("IOResources");
    if (service) {
        kern_return_t result = VirtualAudioDevice_start(service);
        if (result == KERN_SUCCESS) {
            IOLog("WaveLinkIO: Successfully loaded\n");
        } else {
            IOLog("WaveLinkIO: Failed to start VirtualAudioDevice\n");
        }
        return result;
    }
    IOLog("WaveLinkIO: IOResources service not found\n");
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
    struct IOService *service = waitForIOService("IOResources");
    if (service) {
        VirtualAudioDevice_stop(service);
        IOLog("WaveLinkIO: Successfully unloaded\n");
    } else {
        IOLog("WaveLinkIO: IOResources service not found\n");
    }
    return KERN_SUCCESS;
}

// Define the kernel module start/stop functions
KMOD_EXPLICIT_DECL(com.example.WaveLinkIO, "1.0", WaveLinkIO_start, WaveLinkIO_stop)
__attribute__((visibility("default"))) kmod_start_func_t *_realmain = WaveLinkIO_start;
__attribute__((visibility("default"))) kmod_stop_func_t *_antimain = WaveLinkIO_stop;
__attribute__((visibility("default"))) int _kext_apple_cc = __APPLE_CC__;
