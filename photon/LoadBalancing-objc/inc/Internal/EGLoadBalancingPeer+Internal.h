/* Exit Games Photon LoadBalancing - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "LoadBalancing-objc/inc/EGLoadBalancingPeer.h"

@interface EGLoadBalancingPeer ()

+ (NSMutableDictionary*) stripToCustomProperties:(NSDictionary*)properties;
+ (NSMutableDictionary*) stripKeysWithNullValues:(NSDictionary*)orig;
- (EGMutableDictionary*) opCreateRoomImplementation:(NSString*)gameID :(EGRoomOptions*)options :(NSDictionary*)customLocalPlayerProperties;
- (EGMutableDictionary*) opJoinRoomImplementation:(NSString*)gameID :(EGRoomOptions*)options :(NSDictionary*)customLocalPlayerProperties :(bool)createIfNotExists :(int)playerNumber :(int)cacheSliceIndex;
- (EGMutableDictionary*) opJoinRandomRoomImplementation:(NSString*)gameID :(EGRoomOptions*)options :(bool)createIfNotExists :(NSDictionary*)customRoomProperties :(nByte)maxPlayers :(nByte)matchmakingMode :(NSString*)lobbyName :(nByte)lobbyType :(NSString*)sqlLobbyFilter;

@end