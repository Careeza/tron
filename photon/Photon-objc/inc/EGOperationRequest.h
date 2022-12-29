/* Exit Games Photon - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "Common-objc/inc/EGArray.h"
#import "Common-objc/inc/EGDictionary.h"

@interface EGOperationRequest : NSObject

@property (readonly) nByte OperationCode;
@property (readonly) NSDictionary* Parameters;

- (instancetype) init NS_UNAVAILABLE;
- (EGOperationRequest*) initWithOperationCode:(nByte)operationCode;
- (EGOperationRequest*) initWithOperationCode:(nByte)operationCode :(EGDictionary*)parameters NS_DESIGNATED_INITIALIZER;
+ (instancetype) new NS_UNAVAILABLE;
+ (EGOperationRequest*) operationRequestWithOperationCode:(nByte)operationCode;
+ (EGOperationRequest*) operationRequestWithOperationCode:(nByte)operationCode :(EGDictionary*)parameters;
- (EGArray*) allKeys;
- (EGArray*) allValues;
- (NSString*) toString; // = false, = false
- (NSString*) toString:(bool)withParameters; // = false
- (NSString*) toString:(bool)withParameters :(bool)withParameterTypes;
- (id) objectForKey:(id)key;

@end