/* Exit Games Photon - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "Common-objc/inc/EGDictionary.h"

@interface EGEventData : NSObject

@property (readonly) nByte Code;
@property (readonly) EGDictionary* Parameters;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;
- (NSArray*) allKeys;
- (NSArray*) allValues;
- (NSString*) toString; // = false, = false
- (NSString*) toString:(bool)withParameters; // = false
- (NSString*) toString:(bool)withParameters :(bool)withParameterTypes;
- (id) objectForKey:(id)key;

@end