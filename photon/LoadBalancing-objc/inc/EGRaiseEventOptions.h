/* Exit Games Photon LoadBalancing - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "Common-objc/inc/EGArray.h"

@interface EGRaiseEventOptions : EGBase <NSCopying, NSMutableCopying>

@property (readonly) nByte ChannelID;
@property (readonly) nByte EventCaching;
@property (readonly, copy) EGArray* TargetPlayers;
@property (readonly) nByte ReceiverGroup;
@property (readonly) nByte InterestGroup;
@property (readonly) bool ForwardToWebhook;
@property (readonly) int CacheSliceIndex;

- (instancetype) initRaiseEventOptions:(nByte)channelID;
- (instancetype) initRaiseEventOptions:(nByte)channelID :(nByte)eventCaching;
- (instancetype) initRaiseEventOptions:(nByte)channelID :(nByte)eventCaching :(EGArray*)targetPlayers;
- (instancetype) initRaiseEventOptions:(nByte)channelID :(nByte)eventCaching :(EGArray*)targetPlayers :(nByte)receiverGroup;
- (instancetype) initRaiseEventOptions:(nByte)channelID :(nByte)eventCaching :(EGArray*)targetPlayers :(nByte)receiverGroup :(nByte)interestGroup;
- (instancetype) initRaiseEventOptions:(nByte)channelID :(nByte)eventCaching :(EGArray*)targetPlayers :(nByte)receiverGroup :(nByte)interestGroup :(bool)forwardToWebhook;
- (instancetype) initRaiseEventOptions:(nByte)channelID :(nByte)eventCaching :(EGArray*)targetPlayers :(nByte)receiverGroup :(nByte)interestGroup :(bool)forwardToWebhook :(int)cacheSliceIndex NS_DESIGNATED_INITIALIZER;
+ (instancetype) raiseEventOptions;
+ (instancetype) raiseEventOptions:(nByte)channelID;
+ (instancetype) raiseEventOptions:(nByte)channelID :(nByte)eventCaching;
+ (instancetype) raiseEventOptions:(nByte)channelID :(nByte)eventCaching :(EGArray*)targetPlayers;
+ (instancetype) raiseEventOptions:(nByte)channelID :(nByte)eventCaching :(EGArray*)targetPlayers :(nByte)receiverGroup;
+ (instancetype) raiseEventOptions:(nByte)channelID :(nByte)eventCaching :(EGArray*)targetPlayers :(nByte)receiverGroup :(nByte)interestGroup;
+ (instancetype) raiseEventOptions:(nByte)channelID :(nByte)eventCaching :(EGArray*)targetPlayers :(nByte)receiverGroup :(nByte)interestGroup :(bool)forwardToWebhook;
+ (instancetype) raiseEventOptions:(nByte)channelID :(nByte)eventCaching :(EGArray*)targetPlayers :(nByte)receiverGroup :(nByte)interestGroup :(bool)forwardToWebhook :(int)cacheSliceIndex;

@end



@interface EGMutableRaiseEventOptions : EGRaiseEventOptions

@property (readwrite) nByte ChannelID;
@property (readwrite) nByte EventCaching;
@property (readwrite, copy) EGArray* TargetPlayers;
@property (readwrite) nByte ReceiverGroup;
@property (readwrite) nByte InterestGroup;
@property (readwrite) bool ForwardToWebhook;
@property (readwrite) int CacheSliceIndex;

@end