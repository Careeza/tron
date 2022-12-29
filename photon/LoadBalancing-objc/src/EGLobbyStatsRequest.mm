/* Exit Games Photon LoadBalancing - objC Client Lib
 * Copyright (C) 2004-2013 by Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#include "LoadBalancing-cpp/inc/Enums/LobbyType.h"
#import "LoadBalancing-objc/inc/EGLobbyStatsRequest.h"

@implementation EGLobbyStatsRequest
{
@private
	NSString* mName;
	nByte mType;
}

@synthesize Name = mName;
@synthesize Type = mType;



- (instancetype) init
{
	return [self initLobbyStatsRequest:@""];
}

- (instancetype) initLobbyStatsRequest:(NSString*)name
{
	return [self initLobbyStatsRequest:name :ExitGames::LoadBalancing::LobbyType::DEFAULT];
}

- (instancetype) initLobbyStatsRequest:(NSString*)name :(nByte)type
{
	self = [super init];
    mName = [name copy];
    mType = type;
	return self;
}

+ (instancetype) lobbyStatsRequest
{
	return [[self new] autorelease];
}

+ (instancetype) lobbyStatsRequest:(NSString*)name
{
	return [[[self alloc] initLobbyStatsRequest:name] autorelease];
}

+ (instancetype) lobbyStatsRequest:(NSString*)name :(nByte)type
{
	return [[[self alloc] initLobbyStatsRequest:name :type] autorelease];
}

- (NSString*) toString:(bool)withTypes
{
	return [NSString stringWithFormat:@"{%@/%d}", mName, mType];
}

- (void) dealloc
{
	[mName release];
	[super dealloc];
}

@end