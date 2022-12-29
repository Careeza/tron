/* Exit Games Photon LoadBalancing - objC Client Lib
* Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
* http://www.photonengine.com
* mailto:developer@photonengine.com
*/

#import <Foundation/NSCoder.h>
#include "Common-cpp/inc/Common.h"
#import "LoadBalancing-objc/inc/EGLoadBalancingRoom.h"
#import "LoadBalancing-objc/inc/Internal/EGLoadBalancingPeer+Internal.h"
#import "LoadBalancing-objc/inc/Internal/EGLoadBalancingPlayer+Internal.h"
#import "LoadBalancing-objc/inc/Protected/EGLoadBalancingPlayer+Protected.h"

/** @file EGLoadBalancingPlayer.h */

using namespace ExitGames::LoadBalancing;
using namespace ExitGames::LoadBalancing::Internal;

@interface EGLoadBalancingPlayer ()

- (NSString*) payloadToString:(bool)withTypes :(bool)withCustomProperties;

@end



@implementation EGLoadBalancingPlayer
{
@protected
	int mNumber;
	NSMutableString* mName;
	NSMutableString* mUserID;
	NSMutableDictionary* mCustomProperties;
	bool mIsInactive;
	const EGLoadBalancingMutableRoom* mRoom;
}

@synthesize Number = mNumber;

- (NSString*) Name
{
	return [[mName copy] autorelease];
}

- (NSString*) UserID
{
	return [[mUserID copy] autorelease];
}

- (NSDictionary*) CustomProperties
{
	return [[mCustomProperties copyDeep] autorelease];
}

- (bool) IsInactive
{
	return mIsInactive;
}

- (bool) IsMasterClient
{
	return mRoom?mNumber==mRoom.MasterClientID:false;
}



- (instancetype) init
{
	EG_ASSERT(false, @"not implemented");
	return nil;
}

- (instancetype) initLoadBalancingPlayer:(int)number :(NSDictionary*)properties :(const EGLoadBalancingMutableRoom* const)room
{
	self = [super init];
	mNumber = number;
	mRoom = room;
	mCustomProperties = [NSMutableDictionary new];
	[self cacheProperties:properties];
	return self;
}

+ (instancetype) new
{
	EG_ASSERT(false, @"not implemented");
	return nil;
}

+ (instancetype) loadBalancingPlayer:(int)number :(NSDictionary*)properties :(const EGLoadBalancingMutableRoom* const)room
{
	return [[[self alloc] initLoadBalancingPlayer:number :properties :room] autorelease];
}

+ (BOOL) supportsSecureCoding
{
	return true;
}

- (void) encodeWithCoder:(NSCoder*)aCoder
{
	[aCoder encodeObject:[NSValue value:&mNumber withObjCType:@encode(int)] forKey:@"number"];
	[aCoder encodeObject:mName forKey:@"name"];
	[aCoder encodeObject:mUserID forKey:@"userID"];
	[aCoder encodeObject:mCustomProperties forKey:@"customProperties"];
	[aCoder encodeObject:[NSValue value:&mIsInactive withObjCType:@encode(bool)] forKey:@"isInactive"];
	[aCoder encodeConditionalObject:mRoom forKey:@"roomWeakReference"];
	[aCoder encodeObject:[NSValue value:&mRoom withObjCType:@encode(size_t)] forKey:@"roomAddress"];
}

- (instancetype) initWithCoder:(NSCoder*)aDecoder
{
	self = [super init];
	[[aDecoder decodeObjectOfClass:[NSValue class] forKey:@"number"] getValue:&mNumber];
	[mName release];
	mName = [[aDecoder decodeObjectOfClass:[NSString class] forKey:@"name"] retain];
	[mUserID release];
	mUserID = [[aDecoder decodeObjectOfClass:[NSString class] forKey:@"userID"] retain];
	[mCustomProperties release];
	mCustomProperties = [[aDecoder decodeObjectOfClass:[NSDictionary class] forKey:@"customProperties"] retain];
	[[aDecoder decodeObjectOfClass:[NSValue class] forKey:@"isInactive"] getValue:&mIsInactive];
	if(!(mRoom=[aDecoder decodeObjectOfClass:[EGLoadBalancingMutableRoom class] forKey:@"roomWeakReference"])) // the weak reference to the room is only !nil if the Player has been encoded as part of the also encoded owning room
		[[aDecoder decodeObjectOfClass:[NSValue class] forKey:@"roomAddress"] getValue:&mRoom]; // the direct address to the owning room is only still valid after decoding the player, if the player has been encoded on its own, without also encoding the owning room
	return self;
}

+ (instancetype) arrayWithCoder:(NSCoder*)aDecoder
{
	return [[[self alloc] initWithCoder:aDecoder] autorelease];
}

- (instancetype) cacheProperties:(NSDictionary*)properties
{
	if([properties objectForKey:[NSValue value:&Properties::Player::PLAYERNAME withObjCType:@encode(nByte)]])
	{
		[mName release];
		mName = [[properties objectForKey:[NSValue value:&Properties::Player::PLAYERNAME withObjCType:@encode(nByte)]] retain];
	}
	id isInactiveObj = [properties objectForKey:[NSValue value:&Properties::Player::IS_INACTIVE withObjCType:@encode(nByte)]];
	if(isInactiveObj)
		[isInactiveObj getValue:&mIsInactive];
	if([properties objectForKey:[NSValue value:&Properties::Player::USER_ID withObjCType:@encode(nByte)]])
	{
		[mUserID release];
		mUserID = [[properties objectForKey:[NSValue value:&Properties::Player::USER_ID withObjCType:@encode(nByte)]] retain];
	}
	[mCustomProperties addEntriesFromDictionary:[EGLoadBalancingPeer stripToCustomProperties:properties]];
	mCustomProperties = [[EGLoadBalancingPeer stripKeysWithNullValues:[mCustomProperties autorelease]] retain];
	return self;
}

- (instancetype) setIsInactive:(bool)isInactive
{
	mIsInactive = isInactive;
	return self;
}

- (instancetype) setMutableRoom:(EGLoadBalancingMutableRoom*)room
{
	mRoom = room;
	return self;
}

- (NSString*) toString:(bool)withTypes
{
	return [self toString:withTypes :false];
}

- (NSString*) toString:(bool)withTypes :(bool)withCustomProperties
{
	return [NSString stringWithFormat:@"%d={%@}", mNumber, [self payloadToString:withTypes :withCustomProperties]];
}

- (NSString*) payloadToString:(bool)withTypes :(bool)withCustomProperties
{
	NSString* res = [NSString stringWithFormat:@"num: %d name: %@, userID: %@", mNumber, mName, mUserID];
	if(withCustomProperties && mCustomProperties.count)
		res = [res stringByAppendingFormat:@", props: %@", [mCustomProperties toString:withTypes]];
	return res;
}

- (BOOL) isEqual:(id)object
{
	return [object isKindOfClass:[EGLoadBalancingPlayer class]] && self.Number == ((EGLoadBalancingPlayer*)object).Number;
}

- (NSUInteger)hash
{
	return self.Number;
}

- (id) copyWithZone:(NSZone*)zone
{
	NSMutableDictionary* props = [NSMutableDictionary dictionaryWithDictionary:self.CustomProperties];
	[props setObject:self.Name forKey:[NSValue value:&Properties::Player::PLAYERNAME withObjCType:@encode(nByte)]];
	[props setObject:[NSValue value:&mIsInactive withObjCType:@encode(bool)] forKey:[NSValue value:&Properties::Player::IS_INACTIVE withObjCType:@encode(nByte)]];
	return [[[self class] alloc] initLoadBalancingPlayer:self.Number :props :mRoom];
}

- (void) dealloc
{
	[mCustomProperties release];
	[mName release];
	[super dealloc];
}

@end



@implementation EGLoadBalancingMutablePlayer

- (NSString*) Name
{
	return [[mName copy] autorelease];
}

- (void) setName:(NSMutableString*)name
{
	if([mName isEqualToString:name])
		return;
	[mName release];
	[mLoadBalancingClient opSetPropertiesOfPlayer:mNumber :[NSDictionary dictionaryWithObject:mName=[name?:@"" copy] forKey:[NSValue value:&Properties::Player::PLAYERNAME withObjCType:@encode(nByte)]]];
}



- (instancetype) initLoadBalancingPlayer:(int)number :(NSDictionary*)properties :(const EGLoadBalancingMutableRoom* const)room
{
	EG_ASSERT(false, @"not implemented");
	return nil;
}

- (instancetype) initLoadBalancingPlayer:(int)number :(NSDictionary*)properties :(const EGLoadBalancingMutableRoom* const)room :(EGLoadBalancingClient*)client
{
	self = [super initLoadBalancingPlayer:number :properties: room];
	mLoadBalancingClient = client;
	return self;
}

+ (instancetype) loadBalancingPlayer:(int)number :(NSDictionary*)properties :(const EGLoadBalancingMutableRoom* const)room
{
	EG_ASSERT(false, @"not implemented");
	return nil;
}

+ (instancetype) loadBalancingPlayer:(int)number :(NSDictionary*)properties :(const EGLoadBalancingMutableRoom* const)room :(EGLoadBalancingClient*)client
{
	return [[[self alloc] initLoadBalancingPlayer:number :properties :room :client] autorelease];
}

- (void) encodeWithCoder:(NSCoder*)aCoder
{
	[super encodeWithCoder:aCoder];
	[aCoder encodeObject:[NSValue value:&mLoadBalancingClient withObjCType:@encode(size_t)] forKey:@"client"];
}

- (instancetype) initWithCoder:(NSCoder*)aDecoder
{
	self = [super initWithCoder:aDecoder];
	[[aDecoder decodeObjectOfClass:[NSValue class] forKey:@"client"] getValue:&mLoadBalancingClient];
	return self;
}

- (void) mergeCustomProperties:(NSDictionary*)customProperties
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
		[mLoadBalancingClient opSetPropertiesOfPlayer:mNumber :stripDict];	
}

- (void) addCustomProperty:(NSString*)key :(id)value
{
	[self addCustomProperties:[NSDictionary dictionaryWithObject:value forKey:key]];
}

- (void) addCustomProperties:(NSDictionary*)customProperties
{
	[self mergeCustomProperties:[EGLoadBalancingPeer stripKeysWithNullValues:customProperties]];
}

- (void) removeCustomProperty:(NSString*)key
{
	[self removeCustomProperties:&key :1];
}

- (void) removeCustomProperties:(NSString**)keys :(NSUInteger)count
{
	NSNull** vals = new NSNull*[count];
	for(NSUInteger i=0; i<count; i++)
		vals[i] = [NSNull null];
	[self mergeCustomProperties:[NSDictionary dictionaryWithObjects:vals forKeys:keys count:count]];
	delete[] vals;
}

- (void) cleanCustomProperties
{
	[mCustomProperties removeAllObjects];
}

- (id) copyWithZone:(NSZone*)zone
{
	NSMutableDictionary* props = [NSMutableDictionary dictionaryWithDictionary:self.CustomProperties];
	[props setObject:self.Name forKey:[NSValue value:&Properties::Player::PLAYERNAME withObjCType:@encode(nByte)]];
	[props setObject:[NSValue value:&mIsInactive withObjCType:@encode(bool)] forKey:[NSValue value:&Properties::Player::IS_INACTIVE withObjCType:@encode(nByte)]];
	return [[[self class] alloc] initLoadBalancingPlayer:self.Number :props :mRoom :mLoadBalancingClient];
}

@end