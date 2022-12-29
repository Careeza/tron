/* Exit Games Photon Chat - objC Client Lib
* Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
* http://www.photonengine.com
* mailto:developer@photonengine.com
*/

#import <Foundation/NSData.h>
#include "Chat-cpp/inc/Internal/Enums/OperationCode.h"
#include "Chat-cpp/inc/Internal/Enums/ParameterCode.h"
#include "Chat-cpp/inc/Internal/Enums/OperationCode.h"
#include "Chat-cpp/inc/Enums/CustomAuthenticationType.h"
#import "Common-objc/inc/EGDictionary.h"
#import "Photon-objc/inc/Protected/EGPhotonPeer+Protected.h"
#import "Chat-objc/inc/EGChatPeer.h"
#import "Chat-objc/inc/EGChatChannel.h"

/** @file EGChatPeer.h */

using namespace ExitGames::Chat;
using namespace ExitGames::Chat::Internal;

@interface EGChatPeer ()

- (bool) sendChannelOperation:(EGArray* const)channels :(nByte)operation :(int)messagesFromHistory;

@end



@implementation EGChatPeer

- (bool) opAuthenticateOnNameServer:(NSString* const)appID :(NSString* const)appVersion :(NSString* const)region :(const EGAuthenticationValues* const)authenticationValues;
{
	EGMutableDictionary* op = [EGMutableDictionary dictionaryWithKeyType:[NSString stringWithUTF8String:@encode(nByte)] valueType:NSStringFromClass([NSObject class])];
	[op setObject:appID forKey:[NSValue value:&ParameterCode::APPLICATION_ID withObjCType:@encode(nByte)]];
	[op setObject:appVersion forKey:[NSValue value:&ParameterCode::APP_VERSION withObjCType:@encode(nByte)]];
	[op setObject:region forKey:[NSValue value:&ParameterCode::REGION withObjCType:@encode(nByte)]];
	if(authenticationValues.UserID)
		[op setObject:authenticationValues.UserID forKey:[NSValue value:&ParameterCode::USER_ID withObjCType:@encode(nByte)]];
	if(authenticationValues.Type != CustomAuthenticationType::NONE)
	{
		nByte type = authenticationValues.Type;
		[op setObject:[NSValue value:&type withObjCType:@encode(typeof(type))] forKey:[NSValue value:&ParameterCode::CLIENT_AUTHENTICATION_TYPE withObjCType:@encode(nByte)]];
		if(authenticationValues.Secret)
			[op setObject:authenticationValues.Secret forKey:[NSValue value:&ParameterCode::SECRET withObjCType:@encode(nByte)]];
		else
		{
			if(authenticationValues.Parameters)
				[op setObject:authenticationValues.Parameters forKey:[NSValue value:&ParameterCode::CLIENT_AUTHENTICATION_PARAMETERS withObjCType:@encode(nByte)]];
			if(authenticationValues.Data)
			{
				EGMutableArray* data = [EGMutableArray arrayWithCapacityAndCType:authenticationValues.Data.length :@encode(nByte)];
				for(int i=0; i<authenticationValues.Data.length; ++i)
					[data addObject:[NSValue value:((nByte*)authenticationValues.Data.bytes)+i withObjCType:@encode(nByte)]];
				[op setObject:data forKey:[NSValue value:&ParameterCode::CLIENT_AUTHENTICATION_DATA withObjCType:@encode(nByte)]];
			}
		}
	}
	
	EGLOG(ExitGames::Common::DebugLevel::INFO, [[EGOperationRequest operationRequestWithOperationCode:OperationCode::AUTHENTICATE :op] toString:true].UTF32String);
	return [super opCustom:[EGOperationRequest operationRequestWithOperationCode:OperationCode::AUTHENTICATE :op] :true :0 :true];
}

- (bool) opAuthenticateOnFrontEnd:(NSString* const)secret
{
	EGMutableDictionary* op = [EGMutableDictionary dictionaryWithKeyType:[NSString stringWithUTF8String:@encode(nByte)] valueType:NSStringFromClass([NSObject class])];
	[op setObject:secret forKey:[NSValue value:&ParameterCode::SECRET withObjCType:@encode(nByte)]];
	EGLOG(ExitGames::Common::DebugLevel::INFO, [[EGOperationRequest operationRequestWithOperationCode:OperationCode::AUTHENTICATE :op] toString:true].UTF32String);
	// TODO: use isEncryptionAvailable
	return [super opCustom:[EGOperationRequest operationRequestWithOperationCode:OperationCode::AUTHENTICATE :op] :true];
}

- (bool) sendChannelOperation:(EGArray* const)channels :(nByte)operation :(int)messagesFromHistory
{
	EGMutableDictionary* op = [EGMutableDictionary dictionaryWithKeyType:[NSString stringWithUTF8String:@encode(nByte)] valueType:NSStringFromClass([NSObject class])];
	[op setObject:channels forKey:[NSValue value:&ParameterCode::CHANNELS withObjCType:@encode(nByte)]];
	if(messagesFromHistory)
		[op setObject:[NSValue value:&messagesFromHistory withObjCType:@encode(int)] forKey:[NSValue value:&ParameterCode::HISTORY_LENGTH withObjCType:@encode(nByte)]];
	return [super opCustom:[EGOperationRequest operationRequestWithOperationCode:operation :op] :true];
}

- (bool) opSubscribe:(EGArray*)channels
{
	return [self sendChannelOperation:channels :OperationCode::SUBSCRIBE :0];
}

- (bool) opSubscribe:(EGArray*)channels :(int)messagesFromHistory
{
	return [self sendChannelOperation:channels :OperationCode::SUBSCRIBE :messagesFromHistory];
}

- (bool) opUnsubscribe:(EGArray*)channels
{
	return [self sendChannelOperation:channels :OperationCode::UNSUBSCRIBE :0];
}

- (bool) opPublishMessage:(NSString*)channelName :(id<NSObject>)message
{
	EGMutableDictionary* op = [EGMutableDictionary dictionaryWithKeyType:[NSString stringWithUTF8String:@encode(nByte)] valueType:NSStringFromClass([NSObject class])];
	[op setObject:channelName forKey:[NSValue value:&ParameterCode::CHANNEL withObjCType:@encode(nByte)]];
	[op setObject:message forKey:[NSValue value:&ParameterCode::MESSAGE withObjCType:@encode(nByte)]];
	return [super opCustom:[EGOperationRequest operationRequestWithOperationCode:OperationCode::PUBLISH :op] :true];
}

- (bool) opSendPrivateMessage:(NSString*)target :(id<NSObject>)message
{
	return [self opSendPrivateMessage:target :message :false];
}

- (bool) opSendPrivateMessage:(NSString*)target :(id<NSObject>)message :(bool)encrypt
{
	EGMutableDictionary* op = [EGMutableDictionary dictionaryWithKeyType:[NSString stringWithUTF8String:@encode(nByte)] valueType:NSStringFromClass([NSObject class])];
	[op setObject:target forKey:[NSValue value:&ParameterCode::USER_ID withObjCType:@encode(nByte)]];
	[op setObject:message forKey:[NSValue value:&ParameterCode::MESSAGE withObjCType:@encode(nByte)]];
	return [super opCustom:[EGOperationRequest operationRequestWithOperationCode:OperationCode::SEND_PRIVATE :op] :true :0 :encrypt];
}

- (bool) opSetOnlineStatus:(int)status :message :(bool)skipMessage
{
	EGMutableDictionary* op = [EGMutableDictionary dictionaryWithKeyType:[NSString stringWithUTF8String:@encode(nByte)] valueType:NSStringFromClass([NSObject class])];
	[op setObject:[NSValue value:&status withObjCType:@encode(int)] forKey:[NSValue value:&ParameterCode::STATUS withObjCType:@encode(nByte)]];
	if(skipMessage)
		[op setObject:[NSValue value:&skipMessage withObjCType:@encode(bool)] forKey:[NSValue value:&ParameterCode::SKIP_MESSAGE withObjCType:@encode(nByte)]];
	else
		[op setObject:(message?:NSNull.null) forKey:[NSValue value:&ParameterCode::MESSAGE withObjCType:@encode(nByte)]];
	return [super opCustom:[EGOperationRequest operationRequestWithOperationCode:OperationCode::UPDATE_STATUS :op] :true];
}

- (bool) opAddFriends:(EGArray*)userIDs
{
	EGMutableDictionary* op = [EGMutableDictionary dictionaryWithKeyType:[NSString stringWithUTF8String:@encode(nByte)] valueType:NSStringFromClass([NSObject class])];
	[op setObject:userIDs forKey:[NSValue value:&ParameterCode::FRIENDS withObjCType:@encode(nByte)]];
	return [super opCustom:[EGOperationRequest operationRequestWithOperationCode:OperationCode::ADD_FRIENDS :op] :true];
}

- (bool) opRemoveFriends:(EGArray*)userIDs
{
	EGMutableDictionary* op = [EGMutableDictionary dictionaryWithKeyType:[NSString stringWithUTF8String:@encode(nByte)] valueType:NSStringFromClass([NSObject class])];
	[op setObject:userIDs forKey:[NSValue value:&ParameterCode::FRIENDS withObjCType:@encode(nByte)]];
	return [super opCustom:[EGOperationRequest operationRequestWithOperationCode:OperationCode::REMOVE_FRIENDS :op] :true];
}

@end