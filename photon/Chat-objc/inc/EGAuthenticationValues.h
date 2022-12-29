/* Exit Games Photon Chat - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import <Foundation/NSData.h>
#import "Common-objc/inc/EGBase.h"

@interface EGAuthenticationValues : EGBase

@property (readonly) nByte Type;
@property (readonly) NSString* Parameters;
@property (readonly) NSData* Data;
@property (readonly) NSString* Secret;
@property (readonly) NSString* UserID;

- (instancetype) initWithAuthenticationValues:(EGAuthenticationValues*)authenticationValues;
+ (instancetype) authenticationValues;
+ (instancetype) authenticationValuesWithAuthenticationValues:(EGAuthenticationValues*)authenticationValues;

@end



@interface EGMutableAuthenticationValues : EGAuthenticationValues

@property (readwrite) nByte Type;
@property (readwrite, copy) NSString* Parameters;
@property (readwrite, copy) NSData* Data;
@property (readwrite, copy) NSString* UserID;

@end