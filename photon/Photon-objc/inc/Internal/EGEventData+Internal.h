/* Exit Games Photon - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#include "Photon-cpp/inc/EventData.h"
#import "Photon-objc/inc/EGEventData.h"

@interface EGEventData (Internal)

- (EGEventData*) initWithCppEventData:(const ExitGames::Photon::EventData&)eventData;
+ (EGEventData*) eventDataWithCppEventData:(const ExitGames::Photon::EventData&)eventData;

@end