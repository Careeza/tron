/* Exit Games Photon LoadBalancing - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "LoadBalancing-objc/inc/EGLoadBalancingPlayer.h"

@interface EGLoadBalancingPlayer ()

- (instancetype) initLoadBalancingPlayer:(int)number :(NSDictionary*)properties :(const EGLoadBalancingMutableRoom*)room;
+ (instancetype) loadBalancingPlayer:(int)number :(NSDictionary*)properties :(const EGLoadBalancingMutableRoom*)room;

@end



@interface EGLoadBalancingMutablePlayer ()
- (instancetype) initLoadBalancingPlayer:(int)number :(NSDictionary*)properties :(const EGLoadBalancingMutableRoom*)room NS_UNAVAILABLE;
+ (instancetype) loadBalancingPlayer:(int)number :(NSDictionary*)properties :(const EGLoadBalancingMutableRoom*)room NS_UNAVAILABLE;
- (instancetype) initLoadBalancingPlayer:(int)number :(NSDictionary*)properties :(const EGLoadBalancingMutableRoom*)client :(EGLoadBalancingClient*)client;
+ (instancetype) loadBalancingPlayer:(int)number :(NSDictionary*)properties :(const EGLoadBalancingMutableRoom*)client :(EGLoadBalancingClient*)client;

@end