/* Exit Games Photon LoadBalancing - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#include "LoadBalancing-cpp/inc/Internal/Enums/Properties/Player.h"
#import "LoadBalancing-objc/inc/EGLoadBalancingPlayer.h"

@interface EGLoadBalancingPlayer ()

- (instancetype) cacheProperties:(NSDictionary*)properties;
- (instancetype) setIsInactive:(bool)isInactive;
- (instancetype) setMutableRoom:(EGLoadBalancingMutableRoom*)room;

@end



@interface EGLoadBalancingMutablePlayer ()

- (void) cleanCustomProperties;

@end