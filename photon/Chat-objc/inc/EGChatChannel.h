/* Exit Games Photon Chat - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "Common-objc/inc/EGArray.h"

@interface EGChatChannel : EGBase

@property (readonly) NSString* Name;
@property (readonly) NSUInteger MessageCount;
@property (readonly) EGArray* Senders;
@property (readonly) EGArray* Messages;
@property (readonly) bool IsPrivate;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;
- (void) clearMessages;

@end