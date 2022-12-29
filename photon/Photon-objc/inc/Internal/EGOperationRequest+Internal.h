/* Exit Games Photon - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#include "Photon-cpp/inc/OperationRequest.h"
#import "Photon-objc/inc/EGOperationRequest.h"

@interface EGOperationRequest (Internal)

- (ExitGames::Photon::OperationRequest*) toCPP;

@end