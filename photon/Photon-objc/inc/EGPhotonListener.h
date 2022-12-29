/* Exit Games Photon - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "Common-objc/inc/EGBaseListener.h"
#import "Photon-objc/inc/EGEventData.h"
#import "Photon-objc/inc/EGOperationResponse.h"

@protocol EGPhotonListener <EGBaseListener>

- (void) onOperationResponse:(EGOperationResponse*)operationResponse;
- (void) onStatusChanged:(int)statusCode;
- (void) onEvent:(EGEventData*)eventData;



@optional

- (void) onPingResponse:(NSString*)address :(unsigned int)pingResult;

@end

/** @file */