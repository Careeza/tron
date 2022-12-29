/* Exit Games Photon LoadBalancing - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import <Foundation/Foundation.h>
#import "Common-objc/inc/EGArray.h"
#import "Common-objc/inc/EGBaseListener.h"
#import "Common-objc/inc/EGDictionary.h"

@class EGLoadBalancingPlayer;
@class EGArray;

@protocol EGLoadBalancingListener <NSObject, EGBaseListener>

// implement your error-handling here
- (void) connectionErrorReturn:(int)errorCode;
- (void) clientErrorReturn:(int)errorCode;
- (void) warningReturn:(int)warningCode;
- (void) serverErrorReturn:(int)errorCode;

// events, triggered by certain operations of all players in the same room
- (void) joinRoomEventAction:(int)playerNr :(EGArray*)playernrs :(const EGLoadBalancingPlayer*)player;
- (void) leaveRoomEventAction:(int)playerNr :(bool)isInactive;

- (void) customEventAction:(int)playerNr :(nByte)eventCode :(const NSObject*)eventContent;

// callbacks for operations on server
- (void) connectReturn:(int)errorCode :(NSString*)errorString :(NSString*)region :(NSString*)cluster;
- (void) disconnectReturn;
- (void) leaveRoomReturn:(int)errorCode :(NSString*)errorString;



@optional

// callbacks for operations on server
- (void) createRoomReturn:(int)localPlayerNr :(NSDictionary*)roomProperties :(NSDictionary*)playerProperties :(int)errorCode :(NSString*)errorString;
- (void) joinOrCreateRoomReturn:(int)localPlayerNr :(NSDictionary*)roomProperties :(NSDictionary*)playerProperties :(int)errorCode :(NSString*)errorString;
- (void) joinRandomOrCreateRoomReturn:(int)localPlayerNr :(NSDictionary*)roomProperties :(NSDictionary*)playerProperties :(int)errorCode :(NSString*)errorString;
- (void) joinRoomReturn:(int)localPlayerNr :(NSDictionary*)roomProperties :(NSDictionary*)playerProperties :(int)errorCode :(NSString*)errorString;
- (void) joinRandomRoomReturn:(int)localPlayerNr :(NSDictionary*)roomProperties :(NSDictionary*)playerProperties :(int)errorCode :(NSString*)errorString;
- (void) joinLobbyReturn;
- (void) leaveLobbyReturn;
- (void) onFindFriendsResponse;
- (void) onLobbyStatsResponse:(EGArray*)lobbyStats;
- (void) webRpcReturn:(int)errorCode :(NSString*)errorString :(NSString*)uriPath :(int)resultCode :(NSDictionary*)returnData;

// info, that the values of certain properties have been updated
- (void) onRoomListUpdate;
- (void) onRoomPropertiesChange:(NSDictionary*)changes;
- (void) onPlayerPropertiesChange:(int)playerNr :(NSDictionary*)changes;
- (void) onAppStatsUpdate; 
- (void) onLobbyStatsUpdate:(EGArray*)lobbyStats; // array of EGLobbyStats
- (void) onCacheSliceChanged:(int)cacheSliceIndex;

// custom authentication
- (void) onCustomAuthenticationIntermediateStep:(EGDictionary*)customResponseData;
// receive available server regions during connect workflow (if you have specified in the constructor, not to use the default region)
- (void) onAvailableRegions:(EGArray*)availableRegions :(EGArray*)availableRegionServers;
- (void) onSecretReceival:(NSString*)secret;

@end

/** @file */