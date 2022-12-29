/* Exit Games Photon Chat - objC Client Lib
* Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
* http://www.photonengine.com
* mailto:developer@photonengine.com
*/

#import "Chat-objc/inc/Internal/EGChatChannel+Internal.h"

/** @file EGChatChannel.h */

@implementation EGChatChannel
{
@private
	NSString* mName;
	bool mIsPrivate;
	EGMutableArray* mSenders;
	EGMutableArray* mMessages;
}

@synthesize Name = mName;

- (NSUInteger) MessageCount
{
	return mMessages.count;
}

- (EGArray* const) Senders
{
	return mSenders;
}

- (EGArray* const) Messages
{
	return mMessages;
}

@synthesize IsPrivate = mIsPrivate;



- (instancetype) init
{
	EG_ASSERT(false, @"not implemented");
	return nil;
}

- (instancetype) initChannel:(NSString*)name :(bool)isPrivate
{
	self = [super init];
	mName = [name copy];
	mIsPrivate = isPrivate;
	mSenders = [[[EGMutableArray alloc] initWithType:NSStringFromClass([NSString class])] retain];
	mMessages = [[[EGMutableArray alloc] initWithType:NSStringFromClass([NSObject class])] retain];
	return self;
}

+ (instancetype) new
{
	EG_ASSERT(false, @"not implemented");
	return nil;
}

+ (instancetype) channel:(NSString*)name :(bool)isPrivate
{
	return [[[self alloc] initChannel:name :isPrivate] autorelease];
}

- (void) addMessage:(NSString* const)sender :(id<NSObject>)message
{
	[mSenders addObject:sender];
	[mMessages addObject:message];
}

- (void) addMessages:(EGArray* const)senders :(EGArray* const)messages
{
	for(int i = 0;i < senders.count;i++)
	{
		[mSenders addObject:senders[i]];
		[mMessages addObject:messages[i]];
	}
}

- (void) clearMessages
{
	[mSenders removeAllObjects];
	[mMessages removeAllObjects];
}

- (NSString*) toString:(bool)withTypes
{
	return [NSString stringWithFormat:@"{%@ %@}", self.Name, self.IsPrivate?@"(private)":@""];
}

- (void) dealloc
{
	[mName release];
	[mSenders release];
	[mMessages release];
	[super dealloc];
}

@end