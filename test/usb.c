/*
 * Copyright (c) 2013, Henrik Brix Andersen <henrik@brixandersen.dk>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>

#include <LUFA/Drivers/Board/LEDs.h>
#include <LUFA/Drivers/USB/USB.h>

#include "descriptors.h"

USB_ClassInfo_CDC_Device_t imuco_cdc_interface = {
	.Config = {
            .ControlInterfaceNumber   = 0,
            .DataINEndpoint           = {
                .Address          = IMUCO_CDC_TX_EPADDR,
                .Size             = IMUCO_CDC_TXRX_EPSIZE,
                .Banks            = 1,
        },
            .DataOUTEndpoint = {
                .Address          = IMUCO_CDC_RX_EPADDR,
                .Size             = IMUCO_CDC_TXRX_EPSIZE,
                .Banks            = 1,
        },
            .NotificationEndpoint = {
                .Address          = IMUCO_CDC_NOTIFICATION_EPADDR,
                .Size             = IMUCO_CDC_NOTIFICATION_EPSIZE,
                .Banks            = 1,
        },
    },
};

void
usb_init(void) {
    LEDs_Init();
    USB_Init();
    CDC_Device_CreateBlockingStream(&imuco_cdc_interface, stdout);
}

void
EVENT_CDC_Device_ControLineStateChanged(USB_ClassInfo_CDC_Device_t *const CDCInterfaceInfo)
{
    if (CDCInterfaceInfo->State.ControlLineStates.HostToDevice & CDC_CONTROL_LINE_OUT_DTR) {
        LEDs_TurnOnLEDs(LEDS_LED1);
    } else {
        LEDs_TurnOffLEDs(LEDS_LED1);
    }
}

void
EVENT_USB_Device_ConfigurationChanged(void)
{
    if (!CDC_Device_ConfigureEndpoints(&imuco_cdc_interface))
        USB_ResetInterface();
}

void
EVENT_USB_Device_ControlRequest(void)
{
    CDC_Device_ProcessControlRequest(&imuco_cdc_interface);
}
