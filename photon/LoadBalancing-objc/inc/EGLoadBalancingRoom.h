/* Exit Games Photon LoadBalancing - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "Common-objc/inc/EGArray.h"
#import "LoadBalancing-objc/inc/EGLoadBalancingPlayer.h"

@interface EGLoadBalancingRoom : EGBase <NSCopying, NSSecureCoding>

@property (readonly, retain) NSString* Name;
@property (readonly) nByte PlayerCount;
@property (readonly) nByte MaxPlayers;
@property (readonly) bool IsOpen;
@property (readonly, copy) NSDictionary* CustomProperties;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;
- (NSString*) toString:(bool)withTypes :(bool)withCustomProperties;

@end



@interface EGLoadBalancingMutableRoom : EGLoadBalancingRoom

@property (readwrite) nByte MaxPlayers;
@property (readwrite) nByte MaxPlayersWithWebForward;
@property (readwrite) bool IsOpen;
@property (readwrite) bool IsOpenWithWebForward;
@property (readwrite) bool IsVisible;
@property (readwrite) bool IsVisibleWithWebForward;
@property (readonly, copy) EGArray* Players;
@property (readonly) int MasterClientID;
@property (readwrite, copy) EGArray* PropsListedInLobby;
@property (readwrite, copy) EGArray* PropsListedInLobbyWithWebForward;
@property (readonly) int PlayerTtl;
@property (readonly) int EmptyRoomTtl;
@property (readonly) bool SuppressRoomEvents;
@property (readonly, copy) EGArray* Plugins;
@property (readonly) bool PublishUserID;

- (EGLoadBalancingPlayer*) getPlayerForNumber:(int)playerNumber;
- (void) mergeCustomProperties:(NSDictionary*)customProperties; // = false
- (void) mergeCustomProperties:(NSDictionary*)customProperties :(bool)webForward;
- (void) addCustomProperty:(NSString*)key :(id)value; // = false
- (void) addCustomProperty:(NSString*)key :(id)value :(bool)webForward;
- (void) addCustomProperties:(NSDictionary*)customProperties; // = false
- (void) addCustomProperties:(NSDictionary*)customProperties :(bool)webForward;
- (void) removeCustomProperty:(NSString*)key; // = false
- (void) removeCustomProperty:(NSString*)key :(bool)webForward;
- (void) removeCustomProperties:(NSString**)keys :(NSUInteger)count; // = false
- (void) removeCustomProperties:(NSString**)keys :(NSUInteger)count :(bool)webForward;
- (NSString*) toString:(bool)withTypes :(bool)withCustomProperties :(bool)withPlayers;

@end