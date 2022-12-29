/* Exit Games Photon LoadBalancing - C++ Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "Common-objc/inc/EGBase.h"

@interface EGLobbyStatsResponse : EGBase

@property (readonly) NSString* Name;
@property (readonly) nByte Type;
@property (readonly) int PeerCount;
@property (readonly) int RoomCount;

- (instancetype) initLobbyStatsResponse:(NSString*)name;
- (instancetype) initLobbyStatsResponse:(NSString*)name :(nByte)type;
- (instancetype) initLobbyStatsResponse:(NSString*)name :(nByte)type :(int)peerCount;
- (instancetype) initLobbyStatsResponse:(NSString*)name :(nByte)type :(int)peerCount :(int)roomCount NS_DESIGNATED_INITIALIZER;
+ (instancetype) lobbyStatsResponse;
+ (instancetype) lobbyStatsResponse:(NSString*)name;
+ (instancetype) lobbyStatsResponse:(NSString*)name :(nByte)type;
+ (instancetype) lobbyStatsResponse:(NSString*)name :(nByte)type :(int)peerCount;
+ (instancetype) lobbyStatsResponse:(NSString*)name :(nByte)type :(int)peerCount :(int)roomCount;

@end