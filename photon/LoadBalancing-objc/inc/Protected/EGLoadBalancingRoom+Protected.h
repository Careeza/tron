/* Exit Games Photon LoadBalancing - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "LoadBalancing-objc/inc/EGLoadBalancingRoom.h"

@interface EGLoadBalancingRoom ()

- (instancetype) initLoadBalancingRoom:(NSString*)name :(NSDictionary*)properties;
+ (instancetype) loadBalancingRoom:(NSString*)name :(NSDictionary*)properties;

@end



@interface EGLoadBalancingMutableRoom ()

- (instancetype) initLoadBalancingRoom:(NSString*)name :(NSDictionary*)properties NS_UNAVAILABLE;
+ (instancetype) loadBalancingRoom:(NSString*)name :(NSDictionary*)properties NS_UNAVAILABLE;
- (instancetype) initLoadBalancingRoom:(NSString*)name :(NSDictionary*)properties :(EGLoadBalancingClient*)client :(EGArray*)propsListedInLobby :(int)playerTtl :(int)emptyRoomTtl :(bool)suppressRoomEvents :(EGArray*)plugins :(bool)publishUserID;
+ (instancetype) loadBalancingRoom:(NSString*)name :(NSDictionary*)properties :(EGLoadBalancingClient*)client :(EGArray*)propsListedInLobby :(int)playerTtl :(int)emptyRoomTtl :(bool)suppressRoomEvents :(EGArray*)plugins :(bool)publishUserID;
- (EGLoadBalancingPlayer*) createPlayer:(int)number :(NSDictionary*)properties;

@end