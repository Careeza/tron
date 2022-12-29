/* Exit Games Photon LoadBalancing - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "LoadBalancing-objc/inc/EGLoadBalancingClient.h"

@interface EGLoadBalancingClient ()

- (id) createMutablePlayer:(int)number :(NSDictionary*)properties;
- (id) createRoom:(NSString*)name :(NSDictionary*)properties;
- (id) createMutableRoom:(NSString*)name :(NSDictionary*)properties :(EGArray*)propsListedInLobby :(int)playerTtl :(int)emptyRoomTtl :(bool)suppressRoomEvents :(EGArray*)plugins :(bool)publishUserID;

@end