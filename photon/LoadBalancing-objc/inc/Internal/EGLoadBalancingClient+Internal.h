/* Exit Games Photon LoadBalancing - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "LoadBalancing-objc/inc/EGLoadBalancingClient.h"

@interface EGLoadBalancingClient ()

- (bool) opSetPropertiesOfPlayer:(int)playerNr :(NSDictionary*)properties;
- (bool) opSetPropertiesOfRoom:(NSDictionary*)properties;
- (bool) opSetPropertiesOfRoom:(NSDictionary*)properties :(bool)webForward;

@end