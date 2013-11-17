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

#ifndef __DESCRIPTORS_H__
#define __DESCRIPTORS_H__

#include <LUFA/Drivers/USB/USB.h>

#define IMUCO_CDC_NOTIFICATION_EPADDR        (ENDPOINT_DIR_IN  | 2)
#define IMUCO_CDC_TX_EPADDR                  (ENDPOINT_DIR_IN  | 3)
#define IMUCO_CDC_RX_EPADDR                  (ENDPOINT_DIR_OUT | 4)

#define IMUCO_CDC_NOTIFICATION_EPSIZE        8
#define IMUCO_CDC_TXRX_EPSIZE                16

typedef struct {
    USB_Descriptor_Configuration_Header_t    Config;

    // CDC Control Interface
    USB_Descriptor_Interface_t               CDC_CCI_Interface;
    USB_CDC_Descriptor_FunctionalHeader_t    CDC_Functional_Header;
    USB_CDC_Descriptor_FunctionalACM_t       CDC_Functional_ACM;
    USB_CDC_Descriptor_FunctionalUnion_t     CDC_Functional_Union;
    USB_Descriptor_Endpoint_t                CDC_NotificationEndpoint;

    // CDC Data Interface
    USB_Descriptor_Interface_t               CDC_DCI_Interface;
    USB_Descriptor_Endpoint_t                CDC_DataOutEndpoint;
    USB_Descriptor_Endpoint_t                CDC_DataInEndpoint;
} USB_Descriptor_Configuration_t;

uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue, const uint8_t wIndex, const void** const DescriptorAddress)
	ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif /* __DESCRIPTORS_H__ */

