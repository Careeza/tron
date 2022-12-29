/* Exit Games Photon - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "Photon-objc/inc/EGPhotonPeer.h"

@interface EGLitePeer : EGPhotonPeer
{
}

- (instancetype) init NS_UNAVAILABLE;
- (instancetype) initWithPhotonListener:(id<EGPhotonListener>)listener; // = ConnectionProtocol::UDP
- (instancetype) initWithPhotonListener:(id<EGPhotonListener>)listener :(nByte)connectionProtocol NS_DESIGNATED_INITIALIZER;
- (instancetype) initWithPhotonListener:(id<EGPhotonListener>)listener :(nByte)connectionProtocol :(bool)useLitePeer NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;
- (bool) opRaiseEvent:(bool)reliable :(id<NSObject>)parameters :(nByte)eventCode; // = 0
- (bool) opRaiseEvent:(bool)reliable :(id<NSObject>)parameters :(nByte)eventCode :(nByte)channelID; // = EventCache::DO_NOT_CACHE
- (bool) opRaiseEvent:(bool)reliable :(id<NSObject>)parameters :(nByte)eventCode :(nByte)channelID :(nByte)eventCaching; // = NULL, = 0
- (bool) opRaiseEvent:(bool)reliable :(id<NSObject>)parameters :(nByte)eventCode :(nByte)channelID :(nByte)eventCaching :(int*)targetPlayers :(short)numTargetPlayers; // = ReceiverGroup::OTHERS
- (bool) opRaiseEvent:(bool)reliable :(id<NSObject>)parameters :(nByte)eventCode :(nByte)channelID :(nByte)eventCaching :(int*)targetPlayers :(short)numTargetPlayers :(nByte)receiverGroup;
- (bool) opJoin:(NSString*)gameid; // = NULL, = NULL, = false
- (bool) opJoin:(NSString*)gameId :(NSDictionary*)gameProperties :(NSDictionary*)actorProperties :(bool)broadcastActorProperties;
- (bool) opLeave;
- (bool) opSetPropertiesOfActor:(int)actorNr :(NSDictionary*)properties :(bool)broadcast; // = 0
- (bool) opSetPropertiesOfActor:(int)actorNr :(NSDictionary*)properties :(bool)broadcast :(nByte)channelID;
- (bool) opSetPropertiesOfGame:(NSDictionary*)properties :(bool)broadcast; // = 0
- (bool) opSetPropertiesOfGame:(NSDictionary*)properties :(bool)broadcast :(nByte)channelID;
- (bool) opGetProperties; // = 0
- (bool) opGetProperties:(nByte)channelID;
- (bool) opGetPropertiesOfActorByStringKeys:(NSString**)properties :(short)numProperties :(int*)actorNrList :(short)numActors; // = 0
- (bool) opGetPropertiesOfActorByStringKeys:(NSString**)properties :(short)numProperties :(int*)actorNrList :(short)numActors :(nByte)channelID;
- (bool) opGetPropertiesOfActorByByteKeys:(nByte*)properties :(short)numProperties :(int*)actorNrList :(short)numActors; // = 0
- (bool) opGetPropertiesOfActorByByteKeys:(nByte*)properties :(short)numProperties :(int*)actorNrList :(short)numActors :(nByte)channelID;
- (bool) opGetPropertiesOfGameByStringKeys:(NSString**)properties :(short)numProperties; // = 0
- (bool) opGetPropertiesOfGameByStringKeys:(NSString**)properties :(short)numProperties :(nByte)channelID;
- (bool) opGetPropertiesOfGameByByteKeys:(nByte*)properties :(short)numProperties; // = 0
- (bool) opGetPropertiesOfGameByByteKeys:(nByte*)properties :(short)numProperties :(nByte)channelID;
@end