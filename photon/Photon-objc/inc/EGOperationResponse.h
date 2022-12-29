/* Exit Games Photon - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "Common-objc/inc/EGArray.h"

@interface EGOperationResponse : NSObject

@property (readonly) nByte OperationCode;
@property (readonly) short ReturnCode;
@property (readonly) NSString* DebugMessage;
@property (readonly) EGDictionary* Parameters;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;
- (NSArray*) allKeys;
- (NSArray*) allValues;
- (NSString*) toString; // = false, = false, = false
- (NSString*) toString:(bool)withDebugMessage; // = false, = false
- (NSString*) toString:(bool)withDebugMessage :(bool)withParameters; // = false
- (NSString*) toString:(bool)withDebugMessage :(bool)withParameters :(bool)withParameterTypes;
- (id) objectForKey:(id)key;

@end