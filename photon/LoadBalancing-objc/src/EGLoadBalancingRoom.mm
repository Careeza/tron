/* Exit Games Photon LoadBalancing - objC Client Lib
* Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
* http://www.photonengine.com
* mailto:developer@photonengine.com
*/

#import <Foundation/NSCoder.h>
#include "LoadBalancing-cpp/inc/Internal/Enums/Properties/Room.h"
#import "LoadBalancing-objc/inc/Internal/EGLoadBalancingPeer+Internal.h"
#import "LoadBalancing-objc/inc/Internal/EGLoadBalancingRoom+Internal.h"
#import "LoadBalancing-objc/inc/Protected/EGLoadBalancingPlayer+Protected.h"
#import "LoadBalancing-objc/inc/Protected/EGLoadBalancingRoom+Protected.h"

/** @file EGLoadBalancingRoom.h */

using namespace ExitGames::LoadBalancing;
using namespace ExitGames::LoadBalancing::Internal;

@interface EGLoadBalancingRoom ()

- (NSString*) payloadToString:(bool)withTypes :(bool)withCustomProperties;

@end



@implementation EGLoadBalancingRoom
{
@protected
	NSString* mName;
	nByte mPlayerCount;
	nByte mMaxPlayers;
	bool mIsOpen;
	NSMutableDictionary* mCustomProperties;
}

@synthesize Name = mName;
@synthesize PlayerCount = mPlayerCount;
@synthesize MaxPlayers = mMaxPlayers;
@synthesize IsOpen = mIsOpen;

- (NSDictionary*) CustomProperties
{
	return [[mCustomProperties copyDeep] autorelease];
}



- (instancetype) init
{
	EG_ASSERT(false, @"not implemented");
	return nil;
}

- (instancetype) initLoadBalancingRoom:(NSString*)name :(NSDictionary*)properties
{
	self = [super init];
	mName = [name retain];
	mIsOpen = true;
	mCustomProperties = [NSMutableDictionary new];
	[self cacheProperties:properties];
	return self;
}

+ (instancetype) new
{
	EG_ASSERT(false, @"not implemented");
	return nil;
}

+ (instancetype) loadBalancingRoom:(NSString*)name :(NSDictionary*)properties
{
	return [[[self alloc] initLoadBalancingRoom:name :properties] autorelease];
}

+ (BOOL) supportsSecureCoding
{
	return true;
}

- (void) encodeWithCoder:(NSCoder*)aCoder
{
	[aCoder encodeObject:mName forKey:@"name"];
	[aCoder encodeObject:[NSValue value:&mPlayerCount withObjCType:@encode(nByte)] forKey:@"playerCount"];
	[aCoder encodeObject:[NSValue value:&mMaxPlayers withObjCType:@encode(nByte)] forKey:@"maxPlayers"];
	[aCoder encodeObject:[NSValue value:&mIsOpen withObjCType:@encode(bool)] forKey:@"isOpen"];
	[aCoder encodeObject:mCustomProperties forKey:@"customProperties"];
}

- (instancetype) initWithCoder:(NSCoder*)aDecoder
{
	self = [super init];
	[mName release];
	mName = [[aDecoder decodeObjectOfClass:[NSString class] forKey:@"name"] retain];
	[[aDecoder decodeObjectOfClass:[NSValue class] forKey:@"playerCount"] getValue:&mPlayerCount];
	[[aDecoder decodeObjectOfClass:[NSValue class] forKey:@"maxPlayers"] getValue:&mMaxPlayers];
	[[aDecoder decodeObjectOfClass:[NSValue class] forKey:@"isOpen"] getValue:&mIsOpen];
	[mCustomProperties release];
	mCustomProperties = [[aDecoder decodeObjectOfClass:[NSDictionary class] forKey:@"customProperties"] retain];
	return self;
}

+ (instancetype) arrayWithCoder:(NSCoder*)aDecoder
{
	return [[[self alloc] initWithCoder:aDecoder] autorelease];
}

- (instancetype) cacheProperties:(NSDictionary*)properties
{
	if([properties objectForKey:[NSValue value:&Properties::Room::MAX_PLAYERS withObjCType:@encode(nByte)]]) [[properties objectForKey:[NSValue value:&Properties::Room::MAX_PLAYERS withObjCType:@encode(nByte)]] getValue:&mMaxPlayers];
	if([properties objectForKey:[NSValue value:&Properties::Room::IS_OPEN withObjCType:@encode(nByte)]]) [[properties objectForKey:[NSValue value:&Properties::Room::IS_OPEN withObjCType:@encode(nByte)]] getValue:&mIsOpen];
	if([properties objectForKey:[NSValue value:&Properties::Room::PLAYER_COUNT withObjCType:@encode(nByte)]]) [[properties objectForKey:[NSValue value:&Properties::Room::PLAYER_COUNT withObjCType:@encode(nByte)]] getValue:&mPlayerCount];
	[mCustomProperties addEntriesFromDictionary:[EGLoadBalancingPeer stripToCustomProperties:properties]];
	mCustomProperties = [[EGLoadBalancingPeer stripKeysWithNullValues:[mCustomProperties autorelease]] retain];
	return self;
}

- (NSString*) toString:(bool)withTypes
{
	return [self toString:withTypes :false];
}

- (NSString*) toString:(bool)withTypes :(bool)withCustomProperties
{
	return [NSString stringWithFormat:@"%@={%@}", mName, [self payloadToString:withTypes :withCustomProperties]];
}

- (NSString*) payloadToString:(bool)withTypes :(bool)withCustomProperties
{
	NSString* res = [NSString stringWithFormat:@"pl: %d, max: %d, open: %@", mPlayerCount, mMaxPlayers, mIsOpen?@"true":@"false"];
	if(withCustomProperties && mCustomProperties.count)
		res = [res stringByAppendingFormat:@", props: %@", [mCustomProperties toString:withTypes]];
	return res;
}

- (BOOL) isEqual:(id)object
{
	return [object isKindOfClass:[EGLoadBalancingRoom class]] && [self.Name compare:((EGLoadBalancingRoom*)object).Name] == NSOrderedSame;
}

- (NSUInteger)hash
{
	return [self.Name hash];
}

- (id) copyWithZone:(NSZone*)zone
{
	NSMutableDictionary* props = [NSMutableDictionary dictionaryWithDictionary:self.CustomProperties];
	[props setObject:[NSValue value:&mMaxPlayers withObjCType:@encode(bool)] forKey:[NSValue value:&Properties::Room::MAX_PLAYERS withObjCType:@encode(nByte)]];
	[props setObject:[NSValue value:&mIsOpen withObjCType:@encode(bool)] forKey:[NSValue value:&Properties::Room::IS_OPEN withObjCType:@encode(nByte)]];
	[props setObject:[NSValue value:&mPlayerCount withObjCType:@encode(bool)] forKey:[NSValue value:&Properties::Room::PLAYER_COUNT withObjCType:@encode(nByte)]];
	return [[[self class] alloc] initLoadBalancingRoom:self.Name :props];
}

- (void) dealloc
{
	[mCustomProperties release];
	[mName release];
	[super dealloc];
}

@end



@interface EGLoadBalancingMutableRoom ()

- (NSString*) payloadToString:(bool)withTypes :(bool)withCustomProperties :(bool)withPlayers;

@end



@implementation EGLoadBalancingMutableRoom
{
@private
	EGLoadBalancingClient* mLoadBalancingClient;
	bool mIsVisible;
	EGMutableArray* mPlayers;
	int mMasterClientID;
	EGMutableArray* mPropsListedInLobby;
	int mPlayerTtl;
	int mEmptyRoomTtl;
	bool mSuppressRoomEvents;
	EGArray* mPlugins;
	bool mPublishUserID;
}

- (nByte) PlayerCount
{
	return self.PlayersNoCopy.count;
}

- (nByte) MaxPlayers
{
	return super.MaxPlayers;
}

- (void) setMaxPlayers:(nByte)maxPlayers
{
	[mLoadBalancingClient opSetPropertiesOfRoom:[NSDictionary dictionaryWithObject:[NSValue value:&(mMaxPlayers=maxPlayers) withObjCType:@encode(nByte)] forKey:[NSValue value:&Properties::Room::MAX_PLAYERS withObjCType:@encode(nByte)]]];
}

- (nByte) MaxPlayersWithWebForward
{
	return super.MaxPlayers;
}

- (void) setMaxPlayersWithWebForward:(nByte)maxPlayers
{
	[mLoadBalancingClient opSetPropertiesOfRoom:[NSDictionary dictionaryWithObject:[NSValue value:&(mMaxPlayers=maxPlayers) withObjCType:@encode(nByte)] forKey:[NSValue value:&Properties::Room::MAX_PLAYERS withObjCType:@encode(nByte)]] :true];
}

- (bool) IsOpen
{
	return super.IsOpen;
}

- (void) setIsOpen:(bool)isOpen
{
	[mLoadBalancingClient opSetPropertiesOfRoom:[NSDictionary dictionaryWithObject:[NSValue value:&(mIsOpen=isOpen) withObjCType:@encode(bool)] forKey:[NSValue value:&Properties::Room::IS_OPEN withObjCType:@encode(nByte)]]];
}

- (bool) IsOpenWithWebForward
{
	return super.IsOpen;
}

- (void) setIsOpenWithWebForward:(bool)isOpen
{
	[mLoadBalancingClient opSetPropertiesOfRoom:[NSDictionary dictionaryWithObject:[NSValue value:&(mIsOpen=isOpen) withObjCType:@encode(bool)] forKey:[NSValue value:&Properties::Room::IS_OPEN withObjCType:@encode(nByte)]] :true];
}

- (bool) IsVisible
{
	return mIsVisible;
}

- (void) setIsVisible:(bool)isVisible
{
	[mLoadBalancingClient opSetPropertiesOfRoom:[NSDictionary dictionaryWithObject:[NSValue value:&(mIsVisible=isVisible) withObjCType:@encode(bool)] forKey:[NSValue value:&Properties::Room::IS_VISIBLE withObjCType:@encode(nByte)]]];
}

- (bool) IsVisibleWithWebForward
{
	return mIsVisible;
}

- (void) setIsVisibleWithWebForward:(bool)isVisible
{
	[mLoadBalancingClient opSetPropertiesOfRoom:[NSDictionary dictionaryWithObject:[NSValue value:&(mIsVisible=isVisible) withObjCType:@encode(bool)] forKey:[NSValue value:&Properties::Room::IS_VISIBLE withObjCType:@encode(nByte)]] :true];
}

- (EGArray*) Players
{
	return [[mPlayers copyDeep] autorelease];
}

- (EGArray*) PlayersNoCopy
{
	return mPlayers;
}

- (void) setPlayers:(EGArray*)players
{
	[mPlayers release];
	mPlayers = [players mutableCopyDeep];
}

@synthesize MasterClientID = mMasterClientID;

- (EGArray*) PropsListedInLobby
{
	return self.PropsListedInLobbyWithWebForward;
}

- (void) setPropsListedInLobby:(EGArray*)propsListedInLobby
{
	if(mPropsListedInLobby != propsListedInLobby && ![mPropsListedInLobby isEqual:propsListedInLobby])
	{
		[mPropsListedInLobby release];
		[mLoadBalancingClient opSetPropertiesOfRoom:[NSDictionary dictionaryWithObject:mPropsListedInLobby=[propsListedInLobby.Type isEqual:NSStringFromClass([NSString class])]?[[propsListedInLobby copy] autorelease]:[EGArray arrayWithType:NSStringFromClass([NSString class])] forKey:[NSValue value:&Properties::Room::PROPS_LISTED_IN_LOBBY withObjCType:@encode(nByte)]]];
	}
}

- (EGArray*) PropsListedInLobbyWithWebForward
{
	return [[mPropsListedInLobby copyDeep] autorelease];
}

- (void) setPropsListedInLobbyWithWebForward:(EGArray*)propsListedInLobby
{
	if(mPropsListedInLobby != propsListedInLobby && ![mPropsListedInLobby isEqual:propsListedInLobby])
	{
		[mPropsListedInLobby release];
		[mLoadBalancingClient opSetPropertiesOfRoom:[NSDictionary dictionaryWithObject:mPropsListedInLobby=[propsListedInLobby.Type isEqual:NSStringFromClass([NSString class])]?[[propsListedInLobby copyDeep] autorelease]:[EGArray arrayWithType:NSStringFromClass([NSString class])] forKey:[NSValue value:&Properties::Room::PROPS_LISTED_IN_LOBBY withObjCType:@encode(nByte)]] :true];
	}
}

@synthesize PlayerTtl = mPlayerTtl;
@synthesize EmptyRoomTtl = mEmptyRoomTtl;
@synthesize SuppressRoomEvents = mSuppressRoomEvents;

- (EGArray*) Plugins
{
	return [[mPlugins copy] autorelease];
}

@synthesize PublishUserID = mPublishUserID;



- (instancetype) initLoadBalancingRoom:(NSString*)name :(NSDictionary*)properties
{
	EG_ASSERT(false, @"not implemented");
	return nil;
}

- (instancetype) initLoadBalancingRoom:(NSString*)name :(NSDictionary*)properties :(EGLoadBalancingClient*)client :(EGArray*)propsListedInLobby :(int)playerTtl :(int)emptyRoomTtl :(bool)suppressRoomEvents :(EGArray*)plugins :(bool)publishUserID
{
	self = [super initLoadBalancingRoom:name :properties];
	mLoadBalancingClient = client;
	mIsVisible = true;
	mPlayers = [[EGMutableArray alloc] initWithType:NSStringFromClass([EGLoadBalancingPlayer class])];
	mMasterClientID = 0;
	mPropsListedInLobby = [propsListedInLobby mutableCopyDeep];
	mEmptyRoomTtl = emptyRoomTtl;
	mPlayerTtl = playerTtl;
	mSuppressRoomEvents = suppressRoomEvents;
	mPlugins = [plugins copy];
	mPublishUserID = publishUserID;
	return self;
}

+ (instancetype) loadBalancingRoom:(NSString*)name :(NSDictionary*)properties
{
	EG_ASSERT(false, @"not implemented");
	return nil;
}

+ (instancetype) loadBalancingRoom:(NSString*)name :(NSDictionary*)properties :(EGLoadBalancingClient*)client :(EGArray*)propsListedInLobby :(int)playerTtl :(int)emptyRoomTtl :(bool)suppressRoomEvents :(EGArray*)plugins :(bool)publishUserID
{
	return [[[self alloc] initLoadBalancingRoom:name :properties :client :propsListedInLobby :playerTtl :emptyRoomTtl :suppressRoomEvents :plugins :publishUserID] autorelease];
}

- (void) encodeWithCoder:(NSCoder*)aCoder
{
	[super encodeWithCoder:aCoder];
	[aCoder encodeObject:[NSValue value:&mLoadBalancingClient withObjCType:@encode(size_t)] forKey:@"client"];
	[aCoder encodeObject:[NSValue value:&mIsVisible withObjCType:@encode(bool)] forKey:@"isVisible"];
	[aCoder encodeObject:mPlayers forKey:@"players"];
	[aCoder encodeObject:[NSValue value:&mMasterClientID withObjCType:@encode(int)] forKey:@"masterClientID"];
	[aCoder encodeObject:mPropsListedInLobby forKey:@"propsListedInLobby"];
	[aCoder encodeObject:[NSValue value:&mPlayerTtl withObjCType:@encode(int)] forKey:@"playerTtl"];
	[aCoder encodeObject:[NSValue value:&mEmptyRoomTtl withObjCType:@encode(int)] forKey:@"emptyRoomTtl"];
	[aCoder encodeObject:[NSValue value:&mSuppressRoomEvents withObjCType:@encode(bool)] forKey:@"suppressRoomEvents"];
	[aCoder encodeObject:mPlugins forKey:@"plugins"];
	[aCoder encodeObject:[NSValue value:&mPublishUserID withObjCType:@encode(bool)] forKey:@"publishUserID"];
}

- (instancetype) initWithCoder:(NSCoder*)aDecoder
{
	self = [super initWithCoder:aDecoder];
	[[aDecoder decodeObjectOfClass:[NSValue class] forKey:@"client"] getValue:&mLoadBalancingClient];
	[[aDecoder decodeObjectOfClass:[NSValue class] forKey:@"isVisible"] getValue:&mIsVisible];
	[mPlayers release];
	mPlayers = [[aDecoder decodeObjectOfClass:[EGArray class] forKey:@"players"] retain];
	for(NSUInteger i=0; i<mPlayers.count; ++i)
		[[mPlayers objectAtIndex:i] setMutableRoom:self];
	[[aDecoder decodeObjectOfClass:[NSValue class] forKey:@"masterClientID"] getValue:&mMasterClientID];
	[mPropsListedInLobby release];
	mPropsListedInLobby = [[aDecoder decodeObjectOfClass:[EGArray class] forKey:@"propsListedInLobby"] retain];
	[[aDecoder decodeObjectOfClass:[NSValue class] forKey:@"playerTtl"] getValue:&mPlayerTtl];
	[[aDecoder decodeObjectOfClass:[NSValue class] forKey:@"emptyRoomTtl"] getValue:&mEmptyRoomTtl];
	[[aDecoder decodeObjectOfClass:[NSValue class] forKey:@"suppressRoomEvents"] getValue:&mSuppressRoomEvents];
	mPlugins = [[aDecoder decodeObjectOfClass:[EGArray class] forKey:@"plugins"] retain];
	[[aDecoder decodeObjectOfClass:[NSValue class] forKey:@"publishUserID"] getValue:&mPublishUserID];
	return self;
}

- (instancetype) cacheProperties:(NSDictionary*)properties
{
	if([properties objectForKey:[NSValue value:&Properties::Room::IS_VISIBLE withObjCType:@encode(nByte)]]) [[properties objectForKey:[NSValue value:&Properties::Room::IS_VISIBLE withObjCType:@encode(nByte)]] getValue:&mIsVisible];
	return [super cacheProperties:properties];
}

- (EGLoadBalancingPlayer*) getPlayerForNumber:(int)playerNumber
{
	for(unsigned i=0; i<mPlayers.count; i++)
		if(((EGLoadBalancingPlayer*)[mPlayers objectAtIndex:i]).Number == playerNumber)
			return [mPlayers objectAtIndex:i];
	return nil;
}

- (void) mergeCustomProperties:(NSDictionary*)customProperties
{
	[self mergeCustomProperties:customProperties :false];
}

- (void) mergeCustomProperties:(NSDictionary*)customProperties :(bool)webForward
{
	if(mCustomProperties == customProperties)
		return;
	NSDictionary* stripDict = [EGLoadBalancingPeer stripToCustomProperties:customProperties];
	if(!stripDict.count)
		return;
	NSDictionary* oldDict = [[mCustomProperties copyDeep] autorelease];
	[mCustomProperties addEntriesFromDictionary:stripDict];
	mCustomProperties = [[EGLoadBalancingPeer stripKeysWithNullValues:[mCustomProperties autorelease]] retain];
	if(![mCustomProperties isEqual:oldDict])
		[mLoadBalancingClient opSetPropertiesOfRoom:stripDict];	
}

- (void) addCustomProperty:(NSString*)key :(id)value
{
	[self addCustomProperty:key :value :false];
}

- (void) addCustomProperty:(NSString*)key :(id)value :(bool)webForward
{
	[self addCustomProperties:[NSDictionary dictionaryWithObject:value forKey:key] : webForward];
}

- (void) addCustomProperties:(NSDictionary*)customProperties
{
	[self addCustomProperties:customProperties :false];
}

- (void) addCustomProperties:(NSDictionary*)customProperties :(bool)webForward
{
	[self mergeCustomProperties:[EGLoadBalancingPeer stripKeysWithNullValues:customProperties] :webForward];
}

- (void) removeCustomProperty:(NSString*)key
{
	[self removeCustomProperty:key :false];
}

- (void) removeCustomProperty:(NSString*)key :(bool)webForward
{
	[self removeCustomProperties:&key :1 :webForward];
}

- (void) removeCustomProperties:(NSString**)keys :(NSUInteger)count
{
	[self removeCustomProperties:keys :count :false];
}

- (void) removeCustomProperties:(NSString**)keys :(NSUInteger)count :(bool)webForward
{
	NSNull** vals = new NSNull*[count];
	for(NSUInteger i=0; i<count; i++)
		vals[i] = [NSNull null];
	[self mergeCustomProperties:[NSDictionary dictionaryWithObjects:vals forKeys:keys count:count] :webForward];
	delete[] vals;
}

- (void) removeAllPlayers
{
	[mPlayers removeAllObjects];
}

- (void) addPlayer:(EGLoadBalancingPlayer*)player
{
	[mPlayers addObject:player];
	if(!mMasterClientID || player.Number < mMasterClientID)
		mMasterClientID = player.Number;
}

- (void) addPlayer:(int)number :(NSDictionary*)properties
{
	[self addPlayer:[self createPlayer:number :properties]];
}

- (bool) removePlayer:(int)number
{
	bool retVal = false;
	for(unsigned int i=0; i<mPlayers.count; ++i)
	{
		if([[mPlayers objectAtIndex:i] Number] == number)
		{
			[mPlayers removeObjectAtIndex:i];
			retVal = true;
		}
	}

	if(number == mMasterClientID)
	{
		mMasterClientID = mPlayers.count?[[mPlayers objectAtIndex:0] Number]:0;
		for(unsigned int i=1; i<mPlayers.count; ++i)
			if([[mPlayers objectAtIndex:i] Number] < mMasterClientID)
				mMasterClientID = [[mPlayers objectAtIndex:i] Number];
	}
	return retVal;
}

- (EGLoadBalancingPlayer*) createPlayer:(int)number :(NSDictionary*)properties
{
	return [EGLoadBalancingPlayer loadBalancingPlayer:number :properties :self];
}

- (NSString*) toString:(bool)withTypes :(bool)withCustomProperties :(bool)withPlayers
{
	return [NSString stringWithFormat:@"%@={%@}", mName, [self payloadToString:withTypes :withCustomProperties :withPlayers]];
}

- (NSString*) payloadToString:(bool)withTypes :(bool)withCustomProperties :(bool)withPlayers
{
	NSMutableString* res = [NSMutableString stringWithFormat:@"%@, visible: %@, masterClient: %d", [super payloadToString:false :false], mIsVisible?@"true":@"false", mMasterClientID];
	if(mPropsListedInLobby.count)
		[res appendFormat:@", propsListedInLobby: %@", [mPropsListedInLobby toString:withTypes]];
	if(withCustomProperties && mCustomProperties.count)
		[res appendFormat:@", props: %@", [mCustomProperties toString:withTypes]];
	if(withPlayers && mPlayers.count)
	{
		[res appendFormat:@", players:"];
		for(NSUInteger i=0; i<mPlayers.count; ++i)
			[res appendFormat:@" %@%@", [[mPlayers objectAtIndex:i] toString:withTypes :withCustomProperties], i<mPlayers.count-1?@",":@""];
	}
	return res;
}

- (id) copyWithZone:(NSZone*)zone
{
	NSMutableDictionary* props = [NSMutableDictionary dictionaryWithDictionary:self.CustomProperties];
	[props setObject:[NSValue value:&mMaxPlayers withObjCType:@encode(bool)] forKey:[NSValue value:&Properties::Room::MAX_PLAYERS withObjCType:@encode(nByte)]];
	[props setObject:[NSValue value:&mIsOpen withObjCType:@encode(bool)] forKey:[NSValue value:&Properties::Room::IS_OPEN withObjCType:@encode(nByte)]];
	[props setObject:[NSValue value:&mPlayerCount withObjCType:@encode(bool)] forKey:[NSValue value:&Properties::Room::PLAYER_COUNT withObjCType:@encode(nByte)]];
	[props setObject:[NSValue value:&mIsVisible withObjCType:@encode(bool)] forKey:[NSValue value:&Properties::Room::IS_VISIBLE withObjCType:@encode(nByte)]];
	EGLoadBalancingMutableRoom* retVal = [[[self class] alloc] initLoadBalancingRoom:self.Name :props :mLoadBalancingClient :self.PropsListedInLobby :self.PlayerTtl :self.EmptyRoomTtl :self.SuppressRoomEvents :self.Plugins :self.PublishUserID];
	retVal.Players = self.Players;
	for(NSUInteger i=0; i<retVal.PlayersNoCopy.count; ++i)
		[[retVal.PlayersNoCopy objectAtIndex:i] setMutableRoom:retVal];
	retVal->mMasterClientID = self.MasterClientID;
	return retVal;
}

- (void) dealloc
{
	[mPlugins release];
	[mPropsListedInLobby release];
	[mPlayers release];
	[super dealloc];
}

@end