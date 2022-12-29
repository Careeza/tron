/* Exit Games Photon Chat - objC Client Lib
* Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
* http://www.photonengine.com
* mailto:developer@photonengine.com
*/

#import <Foundation/NSData.h>
#include "Chat-cpp/inc/Enums/CustomAuthenticationType.h"
#import "Chat-objc/inc/Internal/EGAuthenticationValues+Internal.h"

/** @file EGAuthenticationValues.h */

@implementation EGAuthenticationValues
{
@protected
	nByte mType;
	NSString* mParameters;
	NSData* mData;
	NSString* mSecret;
	NSString* mUserID;
}

- (nByte) Type
{
	return mType;
}

- (NSString*) Parameters
{
	return mParameters;
}

- (NSData*) Data
{
	return mData;
}

- (NSString*) Secret
{
	return mSecret;
}

- (NSString*) UserID
{
	return mUserID;
}



- (instancetype) initWithAuthenticationValues:(EGAuthenticationValues*)authenticationValues
{
	[self release];
	return self = [authenticationValues copy];
}

+ (instancetype) authenticationValues
{
	return [[self new] autorelease];
}

+ (instancetype) authenticationValuesWithAuthenticationValues:(EGAuthenticationValues*)authenticationValues
{
	return [[[self alloc] initWithAuthenticationValues:authenticationValues] autorelease];
}

- (NSString*) toString:(bool)withTypes
{
	return [NSString stringWithFormat:@"{%d %@ %@ %@ %@}", (int)self.Type, [self.Parameters toString], [self.Data toString], [self.Secret toString], [self.UserID toString]];
}

- (id) copyWithZone:(NSZone*)zone
{
	return [self retain];
}

- (id) mutableCopyWithZone:(NSZone*)zone
{
	EGMutableAuthenticationValues* retVal = [EGMutableAuthenticationValues alloc];
	retVal.Type = self.Type;
	retVal.Parameters = self.Parameters;
	retVal.Data = self. Data;
	retVal.Secret = self.Secret;
	retVal.UserID = self.UserID;
	return retVal;
}

- (void) dealloc
{
	[mUserID release];
	[mSecret release];
	[mData release];
	[mParameters release];
	[super dealloc];
}

@end



@implementation EGMutableAuthenticationValues
{
}

@dynamic Type;

- (void) setType:(nByte)type
{
	mType = type;
}

@dynamic Parameters;

- (void) setParameters:(NSString*)parameters
{
	[mParameters release];
	mParameters = [parameters copy];
}

@dynamic Data;

- (void) setData:(NSData*)data
{
	[mData release];
	mData = [data copy];
}

@dynamic Secret;

- (void) setSecret:(NSString*)secret
{
	[mSecret release];
	mSecret = [secret copy];
}

@dynamic UserID;

- (void) setUserID:(NSString*)userID
{
	[mUserID release];
	mUserID = [userID copy];
}



- (instancetype) initWithAuthenticationValues:(EGAuthenticationValues*)authenticationValues
{
	[self release];
	return self = [authenticationValues mutableCopy];
}

- (id) copyWithZone:(NSZone*)zone
{
	EGAuthenticationValues* retVal = [[self superclass] alloc];
	retVal->mType = self.Type;
	retVal->mParameters = self.Parameters;
	retVal->mData = self. Data;
	retVal->mSecret = self.Secret;
	retVal->mUserID = self.UserID;
	return retVal;
}

@end