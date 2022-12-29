/* Exit Games Photon - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "Common-objc/inc/EGBase.h"

@interface EGTrafficStats : NSObject

@property (readonly) int PackageHeaderSize;
@property (readonly) int ReliableCommandCount;
@property (readonly) int UnreliableCommandCount;
@property (readonly) int FragmentCommandCount;
@property (readonly) int ControlCommandCount;
@property (readonly) int TotalPacketCount;
@property (readonly) int TotalCommandsInPackets;
@property (readonly) int ReliableCommandBytes;
@property (readonly) int UnreliableCommandBytes;
@property (readonly) int FragmentCommandBytes;
@property (readonly) int ControlCommandBytes;
@property (readonly) int TotalCommandCount;
@property (readonly) int TotalCommandBytes;
@property (readonly) int TotalPacketBytes;
@property (readonly) int TimestampOfLastAck;
@property (readonly) int TimestampOfLastReliableCommand;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;
- (NSString*) toString;

@end