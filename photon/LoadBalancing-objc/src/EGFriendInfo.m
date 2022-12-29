/* Exit Games Photon LoadBalancing - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#import "LoadBalancing-objc/inc/EGFriendInfo.h"

@implementation EGFriendInfo
{
@private
	NSString* mName;
	bool mIsOnline;
	NSString* mRoom;
}

@synthesize Name = mName;
@synthesize IsOnline = mIsOnline;
@synthesize Room = mRoom;

- (bool) IsInRoom
{
	return self.Room.length;
}



- (instancetype) init
{
	EG_ASSERT(false, @"not implemented");
	return nil;
}

- (instancetype) initFriendInfo:(NSString*)name
{
	return [self initFriendInfo:name :false :@""];
}

- (instancetype) initFriendInfo:(NSString*)name :(bool)isOnline :(NSString*)room
{
	self = [super init];
	mName = [name copy];
	mIsOnline = isOnline;
	mRoom = [room copy];
	return self;
}

+ (instancetype) new
{
	EG_ASSERT(false, @"not implemented");
	return nil;
}

+ (instancetype) friendInfo:(NSString*)name
{
	return [[[self alloc] initFriendInfo:name] autorelease];
}

+ (instancetype) friendInfo:(NSString*)name :(bool)isOnline :(NSString*)room
{
	return [[[self alloc] initFriendInfo:name :isOnline : room] autorelease];
}

- (NSString*) toString:(bool)withTypes
{
	return [NSString stringWithFormat:@"{%@ %@}", self.Name, self.IsOnline?[NSString stringWithFormat:@"on, %@", self.IsInRoom?[NSString stringWithFormat:@"in room %@", self.Room]:@"not in a room"]:@"off"];
}

- (void) dealloc
{
	[mName release];
	[super dealloc];
}

@end