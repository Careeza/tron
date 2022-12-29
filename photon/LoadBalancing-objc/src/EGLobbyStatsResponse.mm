/* Exit Games Photon LoadBalancing - objC Client Lib
 * Copyright (C) 2004-2013 by Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#include "LoadBalancing-cpp/inc/Enums/LobbyType.h"
#import "LoadBalancing-objc/inc/EGLobbyStatsResponse.h"

@implementation EGLobbyStatsResponse
{
@private
	NSString* mName;
	nByte mType;
	int mPeerCount;
	int mRoomCount;
}

@synthesize Name = mName;
@synthesize Type = mType;
@synthesize PeerCount = mPeerCount;
@synthesize RoomCount = mRoomCount;



- (instancetype) init
{
	return [self initLobbyStatsResponse:@""];
}

- (instancetype) initLobbyStatsResponse:(NSString*)name
{
	return [self initLobbyStatsResponse:name :ExitGames::LoadBalancing::LobbyType::DEFAULT];
}

- (instancetype) initLobbyStatsResponse:(NSString*)name :(nByte)type
{
	return [self initLobbyStatsResponse:name :type :0];
}

- (instancetype) initLobbyStatsResponse:(NSString*)name :(nByte)type :(int)peerCount
{
	return [self initLobbyStatsResponse:name :type :peerCount :0];
}

- (instancetype) initLobbyStatsResponse:(NSString*)name :(nByte)type :(int)peerCount :(int)roomCount
{
    self = [super init];
    mName = [name copy];
    mType = type;
    mPeerCount = peerCount;
    mRoomCount = roomCount;
	return self;
}

+ (instancetype) lobbyStatsResponse
{
	return [[self new] autorelease];
}

+ (instancetype) lobbyStatsResponse:(NSString*)name
{
	return [[[self alloc] initLobbyStatsResponse:name] autorelease];
}

+ (instancetype) lobbyStatsResponse:(NSString*)name :(nByte)type
{
	return [[[self alloc] initLobbyStatsResponse:name :type] autorelease];
}

+ (instancetype) lobbyStatsResponse:(NSString*)name :(nByte)type :(int)peerCount
{
	return [[[self alloc] initLobbyStatsResponse:name :type :peerCount] autorelease];
}

+ (instancetype) lobbyStatsResponse:(NSString*)name :(nByte)type :(int)peerCount :(int)roomCount
{
	return [[[self alloc] initLobbyStatsResponse:name :type :peerCount :roomCount] autorelease];
}

- (NSString*) toString:(bool)withTypes
{
	return [NSString stringWithFormat:@"{%@/%d: peers=%d, rooms=%d}", mName, mType, mPeerCount, mRoomCount];
}

- (void) dealloc
{
	[mName release];
	[super dealloc];
}

@end