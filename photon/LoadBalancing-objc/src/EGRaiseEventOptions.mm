/* Exit Games Photon LoadBalancing - objC Client Lib
* Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
* http://www.photonengine.com
* mailto:developer@photonengine.com
*/

#include "Photon-cpp/inc/Enums/EventCache.h"
#include "Photon-cpp/inc/Enums/ReceiverGroup.h"
#import "LoadBalancing-objc/inc/EGRaiseEventOptions.h"

/** @file EGRaiseEventOptions.h */

namespace EGLITE = ExitGames::Lite;

@implementation EGRaiseEventOptions
{
@protected
	nByte mChannelID;
	nByte mEventCaching;
	EGArray* mTargetPlayers;
	nByte mReceiverGroup;
	nByte mInterestGroup;
	bool mForwardToWebhook;
	int mCacheSliceIndex;
}

@synthesize ChannelID = mChannelID;
@synthesize EventCaching = mEventCaching;

- (EGArray*) TargetPlayers
{
	return [[mTargetPlayers copy] autorelease];
}

@synthesize ReceiverGroup = mReceiverGroup;
@synthesize InterestGroup = mInterestGroup;
@synthesize ForwardToWebhook = mForwardToWebhook;
@synthesize CacheSliceIndex = mCacheSliceIndex;

- (instancetype) init
{
	return [self initRaiseEventOptions:0];
}

- (instancetype) initRaiseEventOptions:(nByte)channelID
{
	return [self initRaiseEventOptions:channelID :EGLITE::EventCache::DO_NOT_CACHE];
}

- (instancetype) initRaiseEventOptions:(nByte)channelID :(nByte)eventCaching
{
	return [self initRaiseEventOptions:channelID :eventCaching :nil];
}

- (instancetype) initRaiseEventOptions:(nByte)channelID :(nByte)eventCaching :(EGArray*)targetPlayers
{
	return [self initRaiseEventOptions:channelID :eventCaching :targetPlayers :EGLITE::ReceiverGroup::OTHERS];
}

- (instancetype) initRaiseEventOptions:(nByte)channelID :(nByte)eventCaching :(EGArray*)targetPlayers :(nByte)receiverGroup
{
	return [self initRaiseEventOptions:channelID :eventCaching :targetPlayers :receiverGroup :0];
}

- (instancetype) initRaiseEventOptions:(nByte)channelID :(nByte)eventCaching :(EGArray*)targetPlayers :(nByte)receiverGroup :(nByte)interestGroup
{
	return [self initRaiseEventOptions:channelID :eventCaching :targetPlayers :receiverGroup :interestGroup :false];
}

- (instancetype) initRaiseEventOptions:(nByte)channelID :(nByte)eventCaching :(EGArray*)targetPlayers :(nByte)receiverGroup :(nByte)interestGroup :(bool)forwardToWebhook
{
	return [self initRaiseEventOptions:channelID :eventCaching :targetPlayers :receiverGroup :interestGroup :forwardToWebhook :0];
}

- (instancetype) initRaiseEventOptions:(nByte)channelID :(nByte)eventCaching :(EGArray*)targetPlayers :(nByte)receiverGroup :(nByte)interestGroup :(bool)forwardToWebhook :(int)cacheSliceIndex
{
	self = [super init];

	mChannelID = channelID;
	mEventCaching = eventCaching;
	mTargetPlayers = [targetPlayers copy];
	mReceiverGroup = receiverGroup;
	mInterestGroup = interestGroup;
	mForwardToWebhook = forwardToWebhook;
	mCacheSliceIndex = cacheSliceIndex;
	return self;
}

+ (instancetype) raiseEventOptions
{
	return [[self new] autorelease];
}

+ (instancetype) raiseEventOptions:(nByte)channelID
{
	return [[[self alloc] initRaiseEventOptions:channelID] autorelease];
}

+ (instancetype) raiseEventOptions:(nByte)channelID :(nByte)eventCaching
{
	return [[[self alloc] initRaiseEventOptions:channelID :eventCaching] autorelease];
}

+ (instancetype) raiseEventOptions:(nByte)channelID :(nByte)eventCaching :(EGArray*)targetPlayers
{
	return [[[self alloc] initRaiseEventOptions:channelID :eventCaching :targetPlayers] autorelease];
}

+ (instancetype) raiseEventOptions:(nByte)channelID :(nByte)eventCaching :(EGArray*)targetPlayers :(nByte)receiverGroup
{
	return [[[self alloc] initRaiseEventOptions:channelID :eventCaching :targetPlayers :receiverGroup] autorelease];
}

+ (instancetype) raiseEventOptions:(nByte)channelID :(nByte)eventCaching :(EGArray*)targetPlayers :(nByte)receiverGroup :(nByte)interestGroup
{
	return [[[self alloc] initRaiseEventOptions:channelID :eventCaching :targetPlayers :receiverGroup :interestGroup] autorelease];
}

+ (instancetype) raiseEventOptions:(nByte)channelID :(nByte)eventCaching :(EGArray*)targetPlayers :(nByte)receiverGroup :(nByte)interestGroup :(bool)forwardToWebhook
{
	return [[[self alloc] initRaiseEventOptions:channelID :eventCaching :targetPlayers :receiverGroup :interestGroup :forwardToWebhook] autorelease];
}

+ (instancetype) raiseEventOptions:(nByte)channelID :(nByte)eventCaching :(EGArray*)targetPlayers :(nByte)receiverGroup :(nByte)interestGroup :(bool)forwardToWebhook :(int)cacheSliceIndex
{
	return [[[self alloc] initRaiseEventOptions:channelID :eventCaching :targetPlayers :receiverGroup :interestGroup :forwardToWebhook :cacheSliceIndex] autorelease];
}

- (NSString*) toString:(bool)withTypes
{
	return [NSString stringWithFormat:@"{channelID=%hhu, eventCaching=%hhu, targetPlayers=%@, receiverGroup=%hhu, interestGroup=%hhu, forwardToWebhook=%@, cacheSliceIndex=%d}", self.ChannelID, self.EventCaching, [self.TargetPlayers toString], self.ReceiverGroup, self.InterestGroup, self.ForwardToWebhook?@"true":@"false", self.CacheSliceIndex];
}

- (id) copyWithZone:(NSZone*)zone
{
	return [self retain];
}

- (id) mutableCopyWithZone:(NSZone*)zone
{
	return [[EGMutableRaiseEventOptions alloc] initRaiseEventOptions:self.ChannelID :self.EventCaching :self.TargetPlayers :self.ReceiverGroup :self.InterestGroup :self.ForwardToWebhook :self.CacheSliceIndex];
}

- (void) dealloc
{
	[mTargetPlayers release];
	[super dealloc];
}

@end



@implementation EGMutableRaiseEventOptions

@dynamic ChannelID;

- (void) setChannelID:(nByte)channelID
{
	mChannelID = channelID;
}

@dynamic EventCaching;

- (void) setEventCaching:(nByte)eventCaching
{
	mEventCaching = eventCaching;
}

@dynamic TargetPlayers;

- (void) setTargetPlayers:(EGArray*)targetPlayers
{
	[mTargetPlayers release];
	mTargetPlayers = [targetPlayers copy];
}

@dynamic ReceiverGroup;

- (void) setReceiverGroup:(nByte)receiverGroup
{
	mReceiverGroup = receiverGroup;
}

@dynamic InterestGroup;

- (void) setInterestGroup:(nByte)interestGroup
{
	mInterestGroup = interestGroup;
}

@dynamic ForwardToWebhook;

- (void) setForwardToWebhook:(bool)forwardToWebhook
{
	mForwardToWebhook = forwardToWebhook;
}

@dynamic CacheSliceIndex;

- (void) setCacheSliceIndex:(int)cacheSliceIndex
{
	mCacheSliceIndex = cacheSliceIndex;
}

- (id) copyWithZone:(NSZone*)zone
{
	return [[[self superclass] alloc] initRaiseEventOptions:self.ChannelID :self.EventCaching :self.TargetPlayers :self.ReceiverGroup :self.InterestGroup :self.ForwardToWebhook :self.CacheSliceIndex];
}

@end