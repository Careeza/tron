/* Exit Games Photon - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#include "Photon-cpp/inc/TrafficStatsGameLevel.h"
#import "Photon-objc/inc/EGTrafficStatsGameLevel.h"

@interface EGTrafficStatsGameLevel ()

- (instancetype) initWithCppTrafficStatsGameLevel:(const ExitGames::Photon::TrafficStatsGameLevel&)ts NS_DESIGNATED_INITIALIZER;
+ (instancetype) trafficStatsGameLevelWithCppTrafficStatsGameLevel:(const ExitGames::Photon::TrafficStatsGameLevel&)ts;

@end