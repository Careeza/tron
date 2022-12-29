/* Exit Games Photon LoadBalancing - C++ Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "Common-objc/inc/EGBase.h"

@interface EGLobbyStatsRequest : EGBase

@property (readonly) NSString* Name;
@property (readonly) nByte Type;

- (instancetype) initLobbyStatsRequest:(NSString*)name;
- (instancetype) initLobbyStatsRequest:(NSString*)name :(nByte)type NS_DESIGNATED_INITIALIZER;
+ (instancetype) lobbyStatsRequest;
+ (instancetype) lobbyStatsRequest:(NSString*)name;
+ (instancetype) lobbyStatsRequest:(NSString*)name :(nByte)type;

@end