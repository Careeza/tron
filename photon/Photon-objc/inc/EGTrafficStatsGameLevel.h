/* Exit Games Photon - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "Common-objc/inc/EGBase.h"

@interface EGTrafficStatsGameLevel : EGBase

@property (readonly) int OperationByteCount;
@property (readonly) int OperationCount;
@property (readonly) int ResultByteCount;
@property (readonly) int ResultCount;
@property (readonly) int EventByteCount;
@property (readonly) int EventCount;
@property (readonly) int LongestOpResponseCallback;
@property (readonly) nByte LongestOpResponseCallbackOpCode;
@property (readonly) int LongestEventCallback;
@property (readonly) nByte LongestEventCallbackCode;
@property (readonly) int LongestDeltaBetweenDispatching;
@property (readonly) int LongestDeltaBetweenSending;
@property (readonly) int DispatchIncomingCommandsCalls;
@property (readonly) int SendOutgoingCommandsCalls;
@property (readonly) int TotalByteCount;
@property (readonly) int TotalMessageCount;
@property (readonly) int TotalIncomingByteCount;
@property (readonly) int TotalIncomingMessageCount;
@property (readonly) int TotalOutgoingByteCount;
@property (readonly) int TotalOutgoingMessageCount;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;
- (NSString*) toString;
- (NSString*) toStringVitalStats;

@end