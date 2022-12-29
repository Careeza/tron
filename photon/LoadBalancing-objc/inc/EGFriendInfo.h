/* Exit Games Photon LoadBalancing - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "Common-objc/inc/EGBase.h"

@interface EGFriendInfo : EGBase

@property (readonly) NSString* Name;
@property (readonly) bool IsOnline;
@property (readonly) NSString* Room;
@property (readonly) bool IsInRoom;

- (instancetype) init NS_UNAVAILABLE;
- (instancetype) initFriendInfo:(NSString*)name;
- (instancetype) initFriendInfo:(NSString*)name :(bool)isOnline :(NSString*)room NS_DESIGNATED_INITIALIZER;
+ (instancetype) new NS_UNAVAILABLE;
+ (instancetype) friendInfo:(NSString*)name;
+ (instancetype) friendInfo:(NSString*)name :(bool)isOnline :(NSString*)room;

@end