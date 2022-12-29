/* Exit Games Photon LoadBalancing - objC Client Lib
* Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
* http://www.photonengine.com
* mailto:developer@photonengine.com
*/

#include "Photon-cpp/inc/Enums/EventCache.h"
#include "Photon-cpp/inc/Enums/ReceiverGroup.h"
#include "LoadBalancing-cpp/inc/Enums/LobbyType.h"
#include "LoadBalancing-cpp/inc/Enums/MatchmakingMode.h"
#include "LoadBalancing-cpp/inc/Internal/Enums/JoinMode.h"
#include "LoadBalancing-cpp/inc/Internal/Enums/JoinType.h"
#include "LoadBalancing-cpp/inc/Internal/Enums/OperationCode.h"
#include "LoadBalancing-cpp/inc/Internal/Enums/ParameterCode.h"
#include "LoadBalancing-cpp/inc/Internal/Enums/Properties/Room.h"
#include "LoadBalancing-cpp/inc/Internal/Enums/Properties/Player.h"
#import "Photon-objc/inc/Protected/EGPhotonPeer+Protected.h"
#import "LoadBalancing-objc/inc/Internal/EGLoadBalancingPeer+Internal.h"

/** @file EGLoadBalancingPeer.h */

namespace EGLB = ExitGames::LoadBalancing::Internal;
namespace EGLITE = ExitGames::Lite;

@interface EGLoadBalancingPeer ()

- (EGMutableDictionary*) enterRoomImplementation:(EGRoomOptions**)pOptions :(NSDictionary*)customLocalPlayerProperties;

@end

@implementation EGLoadBalancingPeer

- (bool) opJoinLobby
{
	return [self opJoinLobby:nil];
}

- (bool) opJoinLobby:(NSString*)lobbyName
{
	return [self opJoinLobby:lobbyName :ExitGames::LoadBalancing::LobbyType::DEFAULT];
}

- (bool) opJoinLobby:(NSString*)lobbyName :(nByte)lobbyType
{
	EGMutableDictionary* op = [EGMutableDictionary dictionaryWithKeyType:[NSString stringWithUTF8String:@encode(nByte)] valueType:NSStringFromClass([NSObject class])];
    if(lobbyName)
    {
        [op setObject:lobbyName forKey:[NSValue value:&EGLB::ParameterCode::LOBBY_NAME withObjCType:@encode(nByte)]];
        if(lobbyType != ExitGames::LoadBalancing::LobbyType::DEFAULT)
            [op setObject:[NSValue value:&lobbyType withObjCType:@encode(typeof(lobbyType))] forKey:[NSValue value:&EGLB::ParameterCode::LOBBY_TYPE withObjCType:@encode(nByte)]];
    }
	return [super opCustom:[EGOperationRequest operationRequestWithOperationCode:EGLB::OperationCode::JOIN_LOBBY :op] :true];
}

- (bool) opLeaveLobby
{
	return [super opCustom:[EGOperationRequest operationRequestWithOperationCode:EGLB::OperationCode::LEAVE_LOBBY] :true];
}

- (bool) opCreateRoom
{
	return [self opCreateRoom:nil];
}

- (bool) opCreateRoom:(NSString*)gameID
{
	return [self opCreateRoom:gameID :nil];
}

- (bool) opCreateRoom:(NSString*)gameID :(EGRoomOptions*)options
{
	return [self opCreateRoom:gameID :options];
}

- (bool) opCreateRoom:(NSString*)gameID :(EGRoomOptions*)options :(NSDictionary*)customLocalPlayerProperties
{
	return [self opCustom:[EGOperationRequest operationRequestWithOperationCode:EGLB::OperationCode::CREATE_ROOM :[self opCreateRoomImplementation:gameID :options :customLocalPlayerProperties]] :true];
}

- (bool) opJoinRoom:(NSString*)gameID
{
	return [self opJoinRoom:gameID :nil];
}

- (bool) opJoinRoom:(NSString*)gameID :(EGRoomOptions*)options
{
	return [self opJoinRoom:gameID :options :nil];
}

- (bool) opJoinRoom:(NSString*)gameID :(EGRoomOptions*)options :(NSDictionary*)customLocalPlayerProperties
{
	return [self opJoinRoom:gameID :options :customLocalPlayerProperties :false];
}

- (bool) opJoinRoom:(NSString*)gameID :(EGRoomOptions*)options :(NSDictionary*)customLocalPlayerProperties :(bool)createIfNotExists
{
	return [self opJoinRoom:gameID :options :customLocalPlayerProperties :createIfNotExists :0];
}

- (bool) opJoinRoom:(NSString*)gameID :(EGRoomOptions*)options :(NSDictionary*)customLocalPlayerProperties :(bool)createIfNotExists :(int)playerNumber
{
	return [self opJoinRoom:gameID :options :customLocalPlayerProperties :createIfNotExists :playerNumber :0];
}

- (bool) opJoinRoom:(NSString*)gameID :(EGRoomOptions*)options :(NSDictionary*)customLocalPlayerProperties :(bool)createIfNotExists :(int)playerNumber :(int)cacheSliceIndex
{
	return gameID?[super opCustom:[EGOperationRequest operationRequestWithOperationCode:EGLB::OperationCode::JOIN_ROOM :[self opJoinRoomImplementation:gameID :options :customLocalPlayerProperties :createIfNotExists :playerNumber :cacheSliceIndex]] :true]:false;
}

- (bool) opJoinRandomRoom
{
	return [self opJoinRandomRoom:nil];
}

- (bool) opJoinRandomRoom:(NSString*)gameID
{
	return [self opJoinRandomRoom:gameID :nil];
}

- (bool) opJoinRandomRoom:(NSString*)gameID :(EGRoomOptions*)options
{
	return [self opJoinRandomRoom:gameID :options :false];
}

- (bool) opJoinRandomRoom:(NSString*)gameID :(EGRoomOptions*)options :(bool)createIfNotExists
{
	return [self opJoinRandomRoom:gameID :options :createIfNotExists :nil];
}

- (bool) opJoinRandomRoom:(NSString*)gameID :(EGRoomOptions*)options :(bool)createIfNotExists :(NSDictionary*)customRoomProperties
{
	return [self opJoinRandomRoom:gameID :options :createIfNotExists :customRoomProperties :0];
}

- (bool) opJoinRandomRoom:(NSString*)gameID :(EGRoomOptions*)options :(bool)createIfNotExists :(NSDictionary*)customRoomProperties :(nByte)maxPlayers
{
	return [self opJoinRandomRoom:gameID :options :createIfNotExists :customRoomProperties :maxPlayers :ExitGames::LoadBalancing::MatchmakingMode::FILL_ROOM];
}

- (bool) opJoinRandomRoom:(NSString*)gameID :(EGRoomOptions*)options :(bool)createIfNotExists :(NSDictionary*)customRoomProperties :(nByte)maxPlayers :(nByte)matchmakingMode
{
	return [self opJoinRandomRoom:gameID :options :createIfNotExists :customRoomProperties :maxPlayers :matchmakingMode :nil];
}

- (bool) opJoinRandomRoom:(NSString*)gameID :(EGRoomOptions*)options :(bool)createIfNotExists :(NSDictionary*)customRoomProperties :(nByte)maxPlayers :(nByte)matchmakingMode :(NSString*)lobbyName
{
    return [self opJoinRandomRoom:gameID :options :createIfNotExists :customRoomProperties :maxPlayers :matchmakingMode :lobbyName :ExitGames::LoadBalancing::LobbyType::DEFAULT];
}

- (bool) opJoinRandomRoom:(NSString*)gameID :(EGRoomOptions*)options :(bool)createIfNotExists :(NSDictionary*)customRoomProperties :(nByte)maxPlayers :(nByte)matchmakingMode :(NSString*)lobbyName :(nByte)lobbyType
{
	return [self opJoinRandomRoom:gameID :options :createIfNotExists :customRoomProperties :maxPlayers :matchmakingMode :lobbyName :lobbyType :nil];
}

- (bool) opJoinRandomRoom:(NSString*)gameID :(EGRoomOptions*)options :(bool)createIfNotExists :(NSDictionary*)customRoomProperties :(nByte)maxPlayers :(nByte)matchmakingMode :(NSString*)lobbyName :(nByte)lobbyType :(NSString*)sqlLobbyFilter
{
	return [self opCustom:[EGOperationRequest operationRequestWithOperationCode:EGLB::OperationCode::JOIN_RANDOM_ROOM :[self opJoinRandomRoomImplementation:gameID :options :createIfNotExists :customRoomProperties :maxPlayers :matchmakingMode :lobbyName :lobbyType :sqlLobbyFilter]] :true];
}

- (bool) opLeaveRoom
{
	return [self opLeaveRoom:false];
}

- (bool) opLeaveRoom:(bool)willComeBack
{
	EGMutableDictionary* op = [EGMutableDictionary dictionaryWithKeyType:[NSString stringWithUTF8String:@encode(nByte)] valueType:NSStringFromClass([NSObject class])];
	if(willComeBack)
		[op setObject:[NSValue value:&willComeBack withObjCType:@encode(typeof(willComeBack))] forKey:[NSValue value:&EGLB::ParameterCode::IS_COMING_BACK withObjCType:@encode(nByte)]];
	return [super opCustom:[EGOperationRequest operationRequestWithOperationCode:EGLB::OperationCode::LEAVE :op] :true];
}

- (bool) opRaiseEvent:(bool)reliable :(id<NSObject>)parameters :(nByte)eventCode
{
	return [self opRaiseEvent:reliable :parameters :eventCode :nil];
}

- (bool) opRaiseEvent:(bool)reliable :(id<NSObject>)parameters :(nByte)eventCode :(EGRaiseEventOptions*)options
{
	EGMutableDictionary* op = [EGMutableDictionary dictionaryWithKeyType:[NSString stringWithUTF8String:@encode(nByte)] valueType:NSStringFromClass([NSObject class])];
	nByte eventCaching = options.EventCaching;
	if(eventCaching == EGLITE::EventCache::SLICE_INC_INDEX || eventCaching == EGLITE::EventCache::SLICE_SET_INDEX || eventCaching == EGLITE::EventCache::SLICE_PURGE_INDEX || eventCaching == EGLITE::EventCache::SLICE_PURGE_UP_TO_INDEX)
	{
		[op setObject:[NSValue value:&eventCaching withObjCType:@encode(typeof(eventCaching))]forKey:[NSValue value:&EGLB::ParameterCode::CACHE_SLICE_INDEX withObjCType:@encode(nByte)]];
		int cacheSliceIndex = options.CacheSliceIndex;
		if(eventCaching != EGLITE::EventCache::SLICE_INC_INDEX)
			[op setObject:[NSValue value:&cacheSliceIndex withObjCType:@encode(typeof(cacheSliceIndex))]forKey:[NSValue value:&EGLITE::ParameterCode::CACHE withObjCType:@encode(nByte)]];

		return [super opCustom:[EGOperationRequest operationRequestWithOperationCode:EGLB::OperationCode::RAISE_EVENT :op] :true :options.ChannelID];
	}

	[op setObject:parameters forKey:[NSValue value:&EGLB::ParameterCode::DATA withObjCType:@encode(nByte)]];
	[op setObject:[NSValue value:&eventCode withObjCType:@encode(typeof(eventCode))] forKey:[NSValue value:&EGLB::ParameterCode::CODE withObjCType:@encode(nByte)]];
	if(eventCaching != EGLITE::EventCache::DO_NOT_CACHE)
		[op setObject:[NSValue value:&eventCaching withObjCType:@encode(typeof(eventCaching))] forKey:[NSValue value:&EGLITE::ParameterCode::CACHE withObjCType:@encode(nByte)]];
	if(options.TargetPlayers)
		[op setObject:options.TargetPlayers forKey:[NSValue value:&EGLB::ParameterCode::PLAYER_LIST withObjCType:@encode(nByte)]];
	nByte receiverGroup = options.ReceiverGroup;
	if(receiverGroup != EGLITE::ReceiverGroup::OTHERS)
		[op setObject:[NSValue value:&receiverGroup withObjCType:@encode(typeof(receiverGroup))] forKey:[NSValue value:&EGLITE::ParameterCode::RECEIVER_GROUP withObjCType:@encode(nByte)]];
	nByte interestGroup = options.InterestGroup;
	if(interestGroup)
		[op setObject:[NSValue value:&interestGroup withObjCType:@encode(typeof(interestGroup))] forKey:[NSValue value:&EGLITE::ParameterCode::GROUP withObjCType:@encode(nByte)]];
	bool forwardToWebhook = options.ForwardToWebhook;
	if(forwardToWebhook)
		[op setObject:[NSValue value:&forwardToWebhook withObjCType:@encode(typeof(forwardToWebhook))] forKey:[NSValue value:&EGLB::ParameterCode::EVENT_FORWARD withObjCType:@encode(nByte)]];

	return [super opCustom:[EGOperationRequest operationRequestWithOperationCode:EGLB::OperationCode::RAISE_EVENT :op] :reliable :options.ChannelID];
}

- (bool) opAuthenticate:(NSString*)appID :(NSString*)appVersion :(bool)encrypted
{
	return [self opAuthenticate:appID :appVersion :encrypted :nil];
}

- (bool) opAuthenticate:(NSString*)appID :(NSString*)appVersion :(bool)encrypted :(EGAuthenticationValues*)authenticationValues
{
	return [self opAuthenticate:appID :appVersion :encrypted :authenticationValues : false];
}

- (bool) opAuthenticate:(NSString*)appID :(NSString*)appVersion :(bool)encrypted :(EGAuthenticationValues*)authenticationValues :(bool)lobbyStats
{
	return [self opAuthenticate:appID :appVersion :encrypted :authenticationValues :lobbyStats :nil];
}

- (bool) opAuthenticate:(NSString*)appID :(NSString*)appVersion :(bool)encrypted :(EGAuthenticationValues*)authenticationValues :(bool)lobbyStats :(NSString* const)regionCode
{
	EGMutableDictionary* op = [EGMutableDictionary dictionaryWithKeyType:[NSString stringWithUTF8String:@encode(nByte)] valueType:NSStringFromClass([NSObject class])];
	[op setObject:appID forKey:[NSValue value:&EGLB::ParameterCode::APPLICATION_ID withObjCType:@encode(nByte)]];
	[op setObject:appVersion forKey:[NSValue value:&EGLB::ParameterCode::APP_VERSION withObjCType:@encode(nByte)]];
	if(authenticationValues.UserID)
		[op setObject:authenticationValues.UserID forKey:[NSValue value:&EGLB::ParameterCode::USER_ID withObjCType:@encode(nByte)]];
	if(authenticationValues)
	{
		nByte type = authenticationValues.Type;
		[op setObject:[NSValue value:&type withObjCType:@encode(typeof(type))]  forKey:[NSValue value:&EGLB::ParameterCode::CLIENT_AUTHENTICATION_TYPE withObjCType:@encode(nByte)]];
		if(authenticationValues.Secret)
			[op setObject:authenticationValues.Secret forKey:[NSValue value:&EGLB::ParameterCode::SECRET withObjCType:@encode(nByte)]];
		else
		{
			if(authenticationValues.Parameters)
				[op setObject:authenticationValues.Parameters forKey:[NSValue value:&EGLB::ParameterCode::CLIENT_AUTHENTICATION_PARAMETERS withObjCType:@encode(nByte)]];
			if(authenticationValues.Data)
			{
				EGMutableArray* data = [EGMutableArray arrayWithCapacityAndCType:authenticationValues.Data.length :@encode(nByte)];
				for(int i=0; i<authenticationValues.Data.length; ++i)
					[data addObject:[NSValue value:((nByte*)authenticationValues.Data.bytes)+i withObjCType:@encode(nByte)]];
				[op setObject:data forKey:[NSValue value:&EGLB::ParameterCode::CLIENT_AUTHENTICATION_DATA withObjCType:@encode(nByte)]];
			}
		}
	}
	if(lobbyStats)
		[op setObject:[NSValue value:&lobbyStats withObjCType:@encode(bool)] forKey:[NSValue value:&EGLB::ParameterCode::LOBBY_STATS withObjCType:@encode(nByte)]];
	if(regionCode)
		[op setObject:regionCode forKey:[NSValue value:&EGLB::ParameterCode::REGION withObjCType:@encode(nByte)]];

	EGLOG(ExitGames::Common::DebugLevel::INFO, [[EGOperationRequest operationRequestWithOperationCode:EGLB::OperationCode::AUTHENTICATE :op] toString:true].UTF32String);
	return [super opCustom:[EGOperationRequest operationRequestWithOperationCode:EGLB::OperationCode::AUTHENTICATE :op] :true :0 :encrypted];
}

- (bool) opFindFriends:(EGArray*)friendsToFind
{
	if(!friendsToFind || ![friendsToFind.Type isEqualToString:NSStringFromClass([NSString class])])
		return false;
	EGMutableDictionary* op = [EGMutableDictionary dictionaryWithKeyType:[NSString stringWithUTF8String:@encode(nByte)] valueType:NSStringFromClass([NSObject class])];
	[op setObject:friendsToFind forKey:[NSValue value:&EGLB::ParameterCode::FIND_FRIENDS_REQUEST_LIST  withObjCType:@encode(nByte)]];
	return [super opCustom:[EGOperationRequest operationRequestWithOperationCode:EGLB::OperationCode::FIND_FRIENDS :op] :true];
}

- (bool) opChangeGroups:(EGArray*)groupsToRemove :(EGArray*)groupsToAdd
{
	EGMutableDictionary* op = [EGMutableDictionary dictionaryWithKeyType:[NSString stringWithUTF8String:@encode(nByte)] valueType:NSStringFromClass([NSObject class])];
	if(groupsToRemove)
		[op setObject:groupsToRemove forKey:[NSValue value:&EGLB::ParameterCode::ADD withObjCType:@encode(nByte)]];
	if(groupsToAdd)
		[op setObject:groupsToAdd forKey:[NSValue value:&EGLB::ParameterCode::ADD withObjCType:@encode(nByte)]];
	return [super opCustom:[EGOperationRequest operationRequestWithOperationCode:EGLB::OperationCode::CHANGE_GROUPS :op] :true];
}

- (bool) opLobbyStats
{
	return [self opLobbyStats:nil];
}

- (bool) opLobbyStats:(EGArray* const)lobbiesToQuery
{    
	EGMutableDictionary* op = [EGMutableDictionary dictionaryWithKeyType:[NSString stringWithUTF8String:@encode(nByte)] valueType:NSStringFromClass([NSObject class])];
	if(lobbiesToQuery)
	{
		EGMutableArray* names = [EGMutableArray arrayWithCapacity:lobbiesToQuery.count :NSStringFromClass([NSString class])];
		EGMutableArray* types = [EGMutableArray arrayWithCapacityAndCType:lobbiesToQuery.count :@encode(nByte)];

		for(unsigned int i=0; i<lobbiesToQuery.count; ++i)
		{
			EGLobbyStatsRequest* s = [lobbiesToQuery objectAtIndex:i];
			[names addObject:s.Name];
			nByte t = s.Type;
			[types addObject:[NSValue value:&t withObjCType:@encode(nByte)]];
		}

		[op setObject:names forKey:[NSValue value:&EGLB::ParameterCode::LOBBY_NAME withObjCType:@encode(nByte)]];
		[op setObject:types forKey:[NSValue value:&EGLB::ParameterCode::LOBBY_TYPE withObjCType:@encode(nByte)]];
	}
	return [super opCustom:[EGOperationRequest operationRequestWithOperationCode:EGLB::OperationCode::LOBBY_STATS :op] :true];
}

- (bool) opWebRpc:(NSString* const)uriPath
{
	return [self opWebRpc:uriPath :nil];
}

- (bool) opWebRpc:(NSString* const)uriPath :(id<NSObject>)parameters
{
	EGMutableDictionary* op = [EGMutableDictionary dictionaryWithKeyType:[NSString stringWithUTF8String:@encode(nByte)] valueType:NSStringFromClass([NSObject class])];
	[op setObject:uriPath forKey:[NSValue value:&EGLB::ParameterCode::URI_PATH withObjCType:@encode(nByte)]];
	[op setObject:parameters?:NSNull.null forKey:[NSValue value:&EGLB::ParameterCode::RPC_CALL_PARAMS withObjCType:@encode(nByte)]];
	return [super opCustom:[EGOperationRequest operationRequestWithOperationCode:EGLB::OperationCode::RPC :op] :true];
}

- (bool) opGetRegions:(bool)encrypted :(NSString* const)appID
{
	EGMutableDictionary* op = [EGMutableDictionary dictionaryWithKeyType:[NSString stringWithUTF8String:@encode(nByte)] valueType:NSStringFromClass([NSObject class])];
	if(appID)
		[op setObject:appID forKey:[NSValue value:&EGLB::ParameterCode::APPLICATION_ID withObjCType:@encode(nByte)]];
	return [super opCustom:[EGOperationRequest operationRequestWithOperationCode:EGLB::OperationCode::GET_REGIONS :op] :true :0 :encrypted];
}

- (bool) opSetPropertiesOfPlayer:(int)playerNr :(NSDictionary*)properties
{
	EGMutableDictionary* op = [EGMutableDictionary dictionaryWithKeyType:[NSString stringWithUTF8String:@encode(nByte)] valueType:NSStringFromClass([NSObject class])];
	[op setObject:properties forKey:[NSValue value:&EGLB::ParameterCode::PROPERTIES withObjCType:@encode(nByte)]];
	[op setObject:[NSValue value:&playerNr withObjCType:@encode(typeof(playerNr))] forKey:[NSValue value:&EGLB::ParameterCode::PLAYERNR withObjCType:@encode(nByte)]];
	bool broadcast = true;
	[op setObject:[NSValue value:&broadcast withObjCType:@encode(typeof(broadcast))] forKey:[NSValue value:&EGLB::ParameterCode::BROADCAST withObjCType:@encode(nByte)]];

	return [super opCustom:[EGOperationRequest operationRequestWithOperationCode:EGLB::OperationCode::SET_PROPERTIES :op] :true];
}

- (bool) opSetPropertiesOfRoom:(NSDictionary*)properties
{
	return [self opSetPropertiesOfRoom:properties :false];
}

- (bool) opSetPropertiesOfRoom:(NSDictionary*)properties :(bool)webForward
{
	EGMutableDictionary* op = [EGMutableDictionary dictionaryWithKeyType:[NSString stringWithUTF8String:@encode(nByte)] valueType:NSStringFromClass([NSObject class])];
	[op setObject:properties forKey:[NSValue value:&EGLB::ParameterCode::PROPERTIES withObjCType:@encode(nByte)]];
	if(webForward)
		[op setObject:[NSValue value:&webForward withObjCType:@encode(typeof(webForward))] forKey:[NSValue value:&EGLB::ParameterCode::EVENT_FORWARD withObjCType:@encode(nByte)]];
	bool broadcast = true;
	[op setObject:[NSValue value:&broadcast withObjCType:@encode(typeof(broadcast))] forKey:[NSValue value:&EGLB::ParameterCode::BROADCAST withObjCType:@encode(nByte)]];
	
	return [super opCustom:[EGOperationRequest operationRequestWithOperationCode:EGLB::OperationCode::SET_PROPERTIES :op] :true];
}

+ (NSMutableDictionary*) stripToCustomProperties:(NSDictionary*)properties
{
	NSArray* keys = properties&&properties.count?[NSArray arrayWithArray:properties.allKeys]:nil;
	NSMutableDictionary* retVal = [NSMutableDictionary dictionary];
	for(NSUInteger i=0; i<properties.count; i++)
	{
		id key = [keys objectAtIndex:i];
		if([key isKindOfClass:[NSString class]])
		{
			id val = [properties objectForKey:key];
			[retVal setObject:[[val respondsToSelector:@selector(copyDeep)]?[val copyDeep]:[val copy] autorelease] forKey:key];
		}
	}
	return retVal;
}

+ (NSMutableDictionary*) stripKeysWithNullValues:(NSDictionary*)orig
{
	NSMutableDictionary* stripped = [[orig mutableCopyDeep] autorelease];
	NSArray* keys = orig.allKeys;
	for(NSUInteger i=0; i<keys.count; i++)
		if([[stripped objectForKey:[keys objectAtIndex:i]] isEqual:NSNull.null])
			[stripped removeObjectForKey:[keys objectAtIndex:i]];
	return stripped;
}

- (EGMutableDictionary*) opCreateRoomImplementation:(NSString*)gameID :(EGRoomOptions*)options :(NSDictionary*)customLocalPlayerProperties
{
	EGMutableDictionary* op = [self enterRoomImplementation:&options :customLocalPlayerProperties];
	if(gameID)
		[op setObject:gameID forKey:[NSValue value:&EGLB::ParameterCode::ROOM_NAME withObjCType:@encode(nByte)]];

	return op;
}

- (EGMutableDictionary*) opJoinRoomImplementation:(NSString*)gameID :(EGRoomOptions*)options :(NSDictionary*)customLocalPlayerProperties :(bool)createIfNotExists :(int)playerNumber :(int)cacheSliceIndex
{
	EGMutableDictionary* op = [self enterRoomImplementation:createIfNotExists?&options:nil :customLocalPlayerProperties];
	[op setObject:gameID forKey:[NSValue value:&EGLB::ParameterCode::ROOM_NAME withObjCType:@encode(nByte)]];

	if(createIfNotExists)
		[op setObject:[NSValue value:&EGLB::JoinMode::CREATE_IF_NOT_EXISTS withObjCType:@encode(typeof(EGLB::JoinMode::CREATE_IF_NOT_EXISTS))] forKey:[NSValue value:&EGLB::ParameterCode::JOIN_MODE withObjCType:@encode(nByte)]];
	else
	{
		if(playerNumber)
		{
			[op setObject:[NSValue value:&EGLB::JoinMode::REJOIN_ONLY withObjCType:@encode(typeof(EGLB::JoinMode::REJOIN_ONLY))] forKey:[NSValue value:&EGLB::ParameterCode::JOIN_MODE withObjCType:@encode(nByte)]];
			[op setObject:[NSValue value:&playerNumber withObjCType:@encode(typeof(playerNumber))] forKey:[NSValue value:&EGLB::ParameterCode::PLAYERNR withObjCType:@encode(nByte)]];
		}
		if(cacheSliceIndex > 0)
			[op setObject:[NSValue value:&cacheSliceIndex withObjCType:@encode(typeof(cacheSliceIndex))] forKey:[NSValue value:&EGLB::ParameterCode::CACHE_SLICE_INDEX withObjCType:@encode(nByte)]];
	}

	return op;
}

- (EGMutableDictionary*) opJoinRandomRoomImplementation:(NSString*)gameID :(EGRoomOptions*)options :(bool)createIfNotExists :(NSDictionary*)customRoomProperties :(nByte)maxPlayers :(nByte)matchmakingMode :(NSString*)lobbyName :(nByte)lobbyType :(NSString*)sqlLobbyFilter;
{
	EGMutableDictionary* op = [self enterRoomImplementation:createIfNotExists?&options:nil :nil];
	if(gameID)
		[op setObject:gameID forKey:[NSValue value:&EGLB::ParameterCode::ROOM_NAME withObjCType:@encode(nByte)]];
	if(createIfNotExists)
		[op setObject:[NSValue value:&EGLB::JoinMode::CREATE_IF_NOT_EXISTS withObjCType:@encode(typeof(EGLB::JoinMode::CREATE_IF_NOT_EXISTS))] forKey:[NSValue value:&EGLB::ParameterCode::JOIN_MODE withObjCType:@encode(nByte)]];

	NSMutableDictionary* roomProps = [EGLoadBalancingPeer stripToCustomProperties:customRoomProperties];
	if(maxPlayers)
		[roomProps setObject:[NSValue value:&maxPlayers withObjCType:@encode(nByte)] forKey:[NSValue value:&EGLB::Properties::Room::MAX_PLAYERS withObjCType:@encode(nByte)]];
	if(roomProps.count)
		[op setObject:roomProps forKey:[NSValue value:&EGLB::ParameterCode::ROOM_PROPERTIES withObjCType:@encode(nByte)]];

	if(matchmakingMode != ExitGames::LoadBalancing::MatchmakingMode::FILL_ROOM)
		[op setObject:[NSValue value:&matchmakingMode withObjCType:@encode(nByte)] forKey:[NSValue value:&EGLB::ParameterCode::DATA withObjCType:@encode(nByte)]];
	if(lobbyName)
	{
		[op setObject:lobbyName forKey:[NSValue value:&EGLB::ParameterCode::LOBBY_NAME withObjCType:@encode(nByte)]];
		if(lobbyType != ExitGames::LoadBalancing::LobbyType::DEFAULT)
			[op setObject:[NSValue value:&lobbyType withObjCType:@encode(typeof(lobbyType))] forKey:[NSValue value:&EGLB::ParameterCode::LOBBY_TYPE withObjCType:@encode(nByte)]];
	}
	if(sqlLobbyFilter)
		[op setObject:sqlLobbyFilter forKey:[NSValue value:&EGLB::ParameterCode::DATA withObjCType:@encode(nByte)]];

	return op;
}

- (EGMutableDictionary*) enterRoomImplementation:(EGRoomOptions**)pOptions :(NSDictionary*)customLocalPlayerProperties
{
	EGMutableDictionary* op = [EGMutableDictionary dictionaryWithKeyType:[NSString stringWithUTF8String:@encode(nByte)] valueType:NSStringFromClass([NSObject class])];

	NSMutableDictionary* playerProps = [EGLoadBalancingPeer stripToCustomProperties:customLocalPlayerProperties];
	if(playerProps.count)
		[op setObject:playerProps forKey:[NSValue value:&EGLB::ParameterCode::PLAYER_PROPERTIES withObjCType:@encode(nByte)]];
	bool broadcast = true;
	[op setObject:[NSValue value:&broadcast withObjCType:@encode(bool)] forKey:[NSValue value:&EGLB::ParameterCode::BROADCAST withObjCType:@encode(nByte)]];

	if(pOptions)
	{
		EGRoomOptions* options = *pOptions?*pOptions:[EGRoomOptions roomOptions];
		NSMutableDictionary* roomProps = [EGLoadBalancingPeer stripToCustomProperties:options.CustomRoomProperties];
		bool isOpen = options.IsOpen;
		if(!isOpen)
			[roomProps setObject:[NSValue value:&isOpen withObjCType:@encode(bool)] forKey:[NSValue value:&EGLB::Properties::Room::IS_OPEN withObjCType:@encode(nByte)]];
		bool isVisible = options.IsVisible;
		if(!isVisible)
			[roomProps setObject:[NSValue value:&isVisible withObjCType:@encode(bool)] forKey:[NSValue value:&EGLB::Properties::Room::IS_VISIBLE withObjCType:@encode(nByte)]];
		nByte maxPlayers = options.MaxPlayers;
		if(maxPlayers)
			[roomProps setObject:[NSValue value:&maxPlayers withObjCType:@encode(nByte)] forKey:[NSValue value:&EGLB::Properties::Room::MAX_PLAYERS withObjCType:@encode(nByte)]];
		if(options.PropsListedInLobby)
			[roomProps setObject:[options.PropsListedInLobby.Type isEqual:NSStringFromClass([NSString class])]?[[options.PropsListedInLobby copyDeep] autorelease]:[EGArray arrayWithType:NSStringFromClass([NSString class])] forKey:[NSValue value:&EGLB::Properties::Room::PROPS_LISTED_IN_LOBBY withObjCType:@encode(nByte)]];
		if(roomProps.count)
			[op setObject:roomProps forKey:[NSValue value:&EGLB::ParameterCode::ROOM_PROPERTIES withObjCType:@encode(nByte)]];

		bool cleanupCacheOnLeave = true;
		[op setObject:[NSValue value:&cleanupCacheOnLeave withObjCType:@encode(bool)] forKey:[NSValue value:&EGLB::ParameterCode::CLEANUP_CACHE_ON_LEAVE withObjCType:@encode(nByte)]];
		if(options.LobbyName)
		{
			[op setObject:options.LobbyName forKey:[NSValue value:&EGLB::ParameterCode::LOBBY_NAME withObjCType:@encode(nByte)]];
			nByte lobbyType = options.LobbyType;
			if(lobbyType != ExitGames::LoadBalancing::LobbyType::DEFAULT)
				[op setObject:[NSValue value:&lobbyType withObjCType:@encode(typeof(lobbyType))] forKey:[NSValue value:&EGLB::ParameterCode::LOBBY_TYPE withObjCType:@encode(nByte)]];
		}
		int playerTtl = options.PlayerTtl;
		if(playerTtl > 0)
			[op setObject:[NSValue value:&playerTtl withObjCType:@encode(typeof(playerTtl))] forKey:[NSValue value:&EGLB::ParameterCode::PLAYER_TTL withObjCType:@encode(nByte)]];
		int emptyRoomTtl = options.EmptyRoomTtl;
		if(emptyRoomTtl > 0)
			[op setObject:[NSValue value:&emptyRoomTtl withObjCType:@encode(typeof(emptyRoomTtl))] forKey:[NSValue value:&EGLB::ParameterCode::EMPTY_ROOM_TTL withObjCType:@encode(nByte)]];
		bool checkUserOnJoin = true;
		[op setObject:[NSValue value:&checkUserOnJoin withObjCType:@encode(typeof(checkUserOnJoin))] forKey:[NSValue value:&EGLB::ParameterCode::CHECK_USER_ON_JOIN withObjCType:@encode(nByte)]];
		bool suppressRoomEvents = options.SuppressRoomEvents;
		if(suppressRoomEvents)
			[op setObject:[NSValue value:&suppressRoomEvents withObjCType:@encode(typeof(suppressRoomEvents))] forKey:[NSValue value:&EGLB::ParameterCode::SUPPRESS_ROOM_EVENTS withObjCType:@encode(nByte)]];
		if(options.Plugins)
			[op setObject:[[options.Plugins copyDeep] autorelease] forKey:[NSValue value:&EGLB::ParameterCode::PLUGINS withObjCType:@encode(nByte)]];
		bool publishUserID = options.PublishUserID;
		if(publishUserID)
			[op setObject:[NSValue value:&publishUserID withObjCType:@encode(typeof(publishUserID))] forKey:[NSValue value:&EGLB::ParameterCode::PUBLISH_USER_ID withObjCType:@encode(nByte)]];
	}

	return op;
}

@end