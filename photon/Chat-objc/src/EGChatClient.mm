/* Exit Games Photon Chat - objC Client Lib
* Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
* http://www.photonengine.com
* mailto:developer@photonengine.com
*/
#import <Foundation/NSException.h>
#include "Chat-cpp/inc/Client.h"
#include "Chat-cpp/inc/Enums/ErrorCode.h"
#include "Chat-cpp/inc/Enums/DisconnectCause.h"
#include "Chat-cpp/inc/Internal/Enums/EventCode.h"
#include "Chat-cpp/inc/Internal/Enums/OperationCode.h"
#include "Chat-cpp/inc/Internal/Enums/ParameterCode.h"
#import "Chat-objc/inc/EGChatPeer.h"
#import "Chat-objc/inc/EGChatClient.h"
#import "Chat-objc/inc/Internal/EGAuthenticationValues+Internal.h"
#import "Chat-objc/inc/Internal/EGChatChannel+Internal.h"

/** @file EGChatClient.h */

namespace ExitGames
{
	namespace Chat
	{
		// default name server address and port
		NSString* const NAMESERVER = @"ns.exitgamescloud.com:5058";
		// default region
		NSString* const REGION = @"EU";
	}
}

using namespace ExitGames;
using namespace ExitGames::Photon;
using namespace ExitGames::Common::DebugLevel;
using namespace ExitGames::Chat;
using namespace ExitGames::Chat::Internal;

@interface EGChatClient ()

@property (readonly) EGLogger* Logger;
@property (readwrite) int State; // redeclare for private write access

@end


@implementation EGChatClient
{
@private
	EGChatPeer* mPeer;
	id<EGChatListener> mListener;
	EGLogger* mLogger;
	NSString* mAppVersion;
	NSString* mAppID;
	NSString* mAppIDPeerInit; // appID adapted to the size suported by PhotonPeer
	nByte mConnectionProtocol;
	NSString* mNameserverAddress;
	NSString* mFrontEndAddress;	
	int mState;
	EGMutableAuthenticationValues* mAuthenticationValues;
	int mDisconnectedCause;
	bool mDidAuthenticate;
	NSString* mRegion;

	EGMutableArray* mPublicChannels;
	EGMutableArray* mPrivateChannels;
}

// properties

- (int) ServerTimeOffset
{
	return mPeer.ServerTimeOffset;
}

- (int) ServerTime
{
	return mPeer.ServerTime;
}

- (int) BytesOut
{
	return mPeer.BytesOut;
}

- (int) BytesIn
{
	return mPeer.BytesIn;
}

- (int) ByteCountCurrentDispatch
{
	return mPeer.ByteCountCurrentDispatch;
}

- (int) ByteCountLastOperation
{
	return mPeer.ByteCountLastOperation;
}

- (int) SentCountAllowance
{
	return mPeer.SentCountAllowance;
}

- (void) setSentCountAllowance:(int)sentCountAllowance
{
	mPeer.SentCountAllowance = sentCountAllowance;
}

- (int) TimePingInterval
{
	return mPeer.TimePingInterval;
}

- (void) setTimePingInterval:(int)timePingInterval
{
	mPeer.TimePingInterval = timePingInterval;
}

- (int) RoundTripTime
{
	return mPeer.RoundTripTime;
}

- (int) RoundTripTimeVariance
{
	return mPeer.RoundTripTimeVariance;
}

- (int) TimestampOfLastSocketReceive
{
	return mPeer.TimestampOfLastSocketReceive;
}

- (int)DebugOutputLevel
{
	return mPeer.DebugOutputLevel;
}

- (void) setDebugOutputLevel:(int)debugOutputLevel
{
	mLogger.DebugOutputLevel = mPeer.DebugOutputLevel = debugOutputLevel;
}

- (int) IncomingReliableCommandsCount
{
	return mPeer.IncomingReliableCommandsCount;
}

- (short) PeerID
{
	return mPeer.PeerID;
}

- (int) DisconnectTimeout
{
	return mPeer.DisconnectTimeout;
}

- (void) setDisconnectTimeout:(int)disconnectTimeout
{
	mPeer.DisconnectTimeout = disconnectTimeout;
}

- (int) QueuedIncomingCommands
{
	return mPeer.QueuedIncomingCommands;
}

- (int) QueuedOutgoingCommands
{
	return mPeer.QueuedOutgoingCommands;
}

- (bool) IsEncryptionAvailable
{
	return mPeer.IsEncryptionAvailable;
}

- (int) ResentReliableCommands
{
	return mPeer.ResentReliableCommands;
}

- (int) LimitOfUnreliableCommands
{
	return mPeer.LimitOfUnreliableCommands;
}

- (void) setLimitOfUnreliableCommands:(int)limitOfUnreliableCommands
{
	mPeer.LimitOfUnreliableCommands = limitOfUnreliableCommands;
}

- (bool) CRCEnabled
{
	return mPeer.CRCEnabled;
}

- (void) setCRCEnabled:(bool)crcEnabled
{
	mPeer.CRCEnabled = crcEnabled;
}

- (int) PacketLossByCRC
{
	return mPeer.PacketLossByCRC;
}

- (bool) TrafficStatsEnabled
{
	return mPeer.TrafficStatsEnabled;
}

- (void) setTrafficStatsEnabled:(bool)trafficStatsEnabled
{
	mPeer.TrafficStatsEnabled = trafficStatsEnabled;
}

- (int) TrafficStatsElapsedMs
{
	return mPeer.TrafficStatsElapsedMs;
}

- (EGTrafficStats*) TrafficStatsIncoming
{
	return mPeer.TrafficStatsIncoming;
}

- (EGTrafficStats*) TrafficStatsOutgoing
{
	return mPeer.TrafficStatsOutgoing;
}

- (EGTrafficStatsGameLevel*) TrafficStatsGameLevel
{
	return mPeer.TrafficStatsGameLevel;
}

- (nByte) QuickResendAttempts
{
	return mPeer.QuickResendAttempts;
}

- (void) setQuickResendAttempts:(nByte)quickResendAttempts
{
	mPeer.QuickResendAttempts = quickResendAttempts;
}

- (short) PeerCount
{
	return mPeer.PeerCount;
}

- (NSString*) UserID
{
	return mAuthenticationValues.UserID;
}

- (int) State
{
	return mState;
}

- (void) setState:(int)s
{
	[mListener onStateChange:mState=s];
}

@synthesize DisconnectedCause = mDisconnectedCause;
@synthesize Region = mRegion;
@synthesize PublicChannels = mPublicChannels;
@synthesize PrivateChannels = mPrivateChannels;

@synthesize Logger = mLogger;



// methods

- (instancetype) init
{
	EG_ASSERT(false, @"not implemented");
	return nil;
}

- (instancetype) initClient:(id<EGChatListener>)listener :(NSString*)applicationID :(NSString*)appVersion
{
	return [self initClient:listener :applicationID :appVersion :ConnectionProtocol::UDP];
}

- (instancetype) initClient:(id<EGChatListener>)listener :(NSString*)applicationID :(NSString*)appVersion :(nByte)connectionProtocol
{
	self = [super init];
	mPeer = [[EGChatPeer alloc] initWithPhotonListener:self :mConnectionProtocol=connectionProtocol];
	(mLogger = [EGLogger new]).Listener = mListener = [listener retain];
	mAppID = [applicationID retain];
	mAppVersion = [appVersion retain];
	mState = ClientState::Uninitialized;
	mDisconnectedCause = DisconnectCause::NONE;
	self.Region = [REGION copy];
	mPublicChannels = [[EGMutableArray alloc] initWithType:NSStringFromClass([EGChatChannel class])];
	mPrivateChannels = [[EGMutableArray alloc] initWithType:NSStringFromClass([EGChatChannel class])];
	mAppIDPeerInit = [[mAppID stringByReplacingOccurrencesOfString:@"-" withString:@""] retain];

	return self;
}

- (void) dealloc
{
	[mAppIDPeerInit release];
	[mPrivateChannels release];
	[mPublicChannels release];
	[mAppVersion release];
	[mAppID release];
	[mAuthenticationValues release];
	[mLogger release];
	[mListener release];
	[mPeer release];
	[super dealloc];
}

- (bool) connect
{
	return [self connect:nil];
}

- (bool) connect:(EGAuthenticationValues*)authenticationValues
{
	return [self connect:authenticationValues :NAMESERVER];
}

- (bool) connect:(EGAuthenticationValues*)authenticationValues :(NSString* const)nameServerAddress
{
	[mAuthenticationValues release];
	mAuthenticationValues = authenticationValues?[authenticationValues mutableCopy]:[EGMutableAuthenticationValues new];
	[mPublicChannels removeAllObjects];
	[mPrivateChannels removeAllObjects];
	mDidAuthenticate = false;
	if([mPeer connect:[NSString stringWithFormat:@"%@%@", nameServerAddress, [nameServerAddress containsString:@":"]?@"":[NSString stringWithFormat:@":%d", mConnectionProtocol==ConnectionProtocol::UDP?NetworkPort::UDP::NAME:NetworkPort::TCP::NAME]] :mAppIDPeerInit])
	{
		self.State = ClientState::ConnectingToNameServer;
		return true;
	}
	else
		return false;
}

- (void) disconnect
{
	self.State = ClientState::Disconnecting;
	[mPeer disconnect];
}

- (void) service
{
	[mPeer service];
}

- (void) service:(bool)dispatchIncomingCommands
{
	[mPeer service:dispatchIncomingCommands];
}

- (void) serviceBasic
{
	[mPeer serviceBasic];
}

- (bool) sendOutgoingCommands
{
	return [mPeer sendOutgoingCommands];
}

- (bool) sendAcksOnly
{
	return [mPeer sendAcksOnly];
}

- (bool) dispatchIncomingCommands
{
	return [mPeer dispatchIncomingCommands];
}

- (void) fetchServerTimestamp
{
	[mPeer fetchServerTimestamp];
}

- (void) resetTrafficStats
{
	[mPeer resetTrafficStats];
}

- (void) resetTrafficStatsMaximumCounters
{
	[mPeer resetTrafficStatsMaximumCounters];
}

- (NSString*) vitalStatsToString:(bool)all
{
	return [mPeer vitalStatsToString:all];
}

- (EGChatChannel*) getChannel:(EGArray* const)channels :(NSString*)name
{
	for(int i = 0;i < channels.count;++i)
		if([((EGChatChannel*)channels[i]).Name isEqualToString:name])
			return channels[i];
	return NULL;
}

- (EGChatChannel*) getOrAddChannel:(EGMutableArray*)channels :(NSString*)name :(bool)isPrivate
{
	EGChatChannel* ch = [self getChannel:channels :name];
	if(!ch)
	{
		ch = [[EGChatChannel alloc] initChannel:name :isPrivate];
		[channels addObject:ch];
	}
	return ch;
}

- (void) removeChannel:(EGMutableArray*)channels :(NSString*)name
{
	for(int i = 0;i < channels.count;++i)
	{
		if([((EGChatChannel*)channels[i]).Name isEqualToString:name])
			[channels removeObjectAtIndex:i];
		else
			++i;
	}
}

- (EGChatChannel*) getPublicChannel:(NSString*)channelName
{
	return [self getChannel:mPublicChannels :channelName];
}

- (EGChatChannel*) getPrivateChannel:(NSString*)userName
{
	return [self getChannel:mPrivateChannels :userName];
}

- (bool) opSubscribe:(EGArray*)channels
{
	return [self opSubscribe:channels :0];
}

- (bool) opSubscribe:(EGArray*)channels :(int)messagesFromHistory
{
	if(mState != ClientState::ConnectedToFrontEnd)
	{
		EGLOG(ERRORS, L"subscribe: client in wrong state: %d", mState);
		return false;
	}
	else
		return [mPeer opSubscribe:channels :messagesFromHistory];
}

- (bool) opUnsubscribe:(EGArray*)channels
{
	if(mState != ClientState::ConnectedToFrontEnd)
	{
		EGLOG(ERRORS, L"гтsubscribe: client in wrong state: %d", mState);
		return false;
	}
	else
		return [mPeer opUnsubscribe:channels];
}

- (bool) opPublishMessage:(NSString*)channelName :(id<NSObject>)message
{
	if(mState != ClientState::ConnectedToFrontEnd)
	{
		EGLOG(ERRORS, L"opPublishMessage: client in wrong state: %d", mState);
		return false;
	}
	else
		return [mPeer opPublishMessage:channelName :message];
}

- (bool) opSendPrivateMessage:(NSString*)target :(id<NSObject>)message
{
	return [self opSendPrivateMessage:target :message :false];
}

- (bool) opSendPrivateMessage:(NSString*)target :(id<NSObject>)message :(bool)encrypt
{
	if(mState != ClientState::ConnectedToFrontEnd)
	{
		EGLOG(ERRORS, L"opSendPrivateMessage: client in wrong state: %d", mState);
		return false;
	}
	else
		return [mPeer opSendPrivateMessage:target :message :encrypt];
}

- (bool) opSetOnlineStatus:(int)status
{
	return [self opSetOnlineStatus:status :nil :false];
}

- (bool) opSetOnlineStatus:(int)status :(id<NSObject>)message
{
	return [self opSetOnlineStatus:status :message :false];
}

- (bool) opSetOnlineStatus:(int)status :(id<NSObject>)message :(bool)skipMessage
{
	if(mState != ClientState::ConnectedToFrontEnd)
	{
		EGLOG(ERRORS, L"opSetOnlineStatus: client in wrong state: %d", mState);
		return false;
	}
	else
		return [mPeer opSetOnlineStatus:status :message :skipMessage];
}

- (bool) opAddFriends:(EGArray*)userIDs
{
	if(mState != ClientState::ConnectedToFrontEnd)
	{
		EGLOG(ERRORS, L"opAddFriends: client in wrong state: %d", mState);
		return false;
	}
	else
		return [mPeer opAddFriends:userIDs];
}

- (bool) opRemoveFriends:(EGArray*)userIDs
{
	if(mState != ClientState::ConnectedToFrontEnd)
	{
		EGLOG(ERRORS, L"opRemoveFriends: client in wrong state: %d", mState);
		return false;
	}
	else
		return [mPeer opRemoveFriends:userIDs];
}



// protocol implementations

- (void) onOperationResponse:(EGOperationResponse*)operationResponse
{
	EGLOG(operationResponse.ReturnCode?ERRORS:INFO, [operationResponse toString:true].UTF32String);
	switch(operationResponse.OperationCode)
	{
		case OperationCode::AUTHENTICATE:
			[self handleAuthResponse:operationResponse];
			break;
		case OperationCode::PUBLISH:
			break;
		case OperationCode::SEND_PRIVATE:
			break;
		case OperationCode::CHANNEL_HISTORY:
			break;
		case OperationCode::UPDATE_STATUS:
			break;
		case OperationCode::ADD_FRIENDS:
			break;
		case OperationCode::REMOVE_FRIENDS:
			break;
		default:
			break;
	}
}

- (void) handleAuthResponse:(EGOperationResponse*)operationResponse
{
	int oldState = mState;
	if(operationResponse.ReturnCode)
	{
		EGLOG(ERRORS, L"Authentication failed with errorcode %d: %ls", operationResponse.ReturnCode, operationResponse.DebugMessage);
		
		switch (operationResponse.ReturnCode)
		{
			case ExitGames::Chat::ErrorCode::INVALID_AUTHENTICATION:
				mDisconnectedCause = DisconnectCause::INVALID_AUTHENTICATION;
				break;
			case ExitGames::Chat::ErrorCode::CUSTOM_AUTHENTICATION_FAILED:
				mDisconnectedCause = DisconnectCause::CUSTOM_AUTHENTICATION_FAILED;
				break;
			case ExitGames::Chat::ErrorCode::INVALID_REGION:
				mDisconnectedCause = DisconnectCause::INVALID_REGION;
				break;
			case ExitGames::Chat::ErrorCode::MAX_CCU_REACHED:
				mDisconnectedCause = DisconnectCause::MAX_CCU_REACHED;
				break;
			case ExitGames::Chat::ErrorCode::OPERATION_DENIED:
				mDisconnectedCause = DisconnectCause::OPERATION_NOT_ALLOWED_IN_CURRENT_STATE;
				break;
		}
		[self handleConnectionFlowError:oldState :operationResponse.ReturnCode :operationResponse.DebugMessage];
	}
	else
	{
		if(mState == ClientState::ConnectedToNameServer)
		{
			self.State = ClientState::Authenticated;
			// TODO: what if no secret or address data in response?
			mAuthenticationValues.Secret = [operationResponse objectForKey:[NSValue value:&ParameterCode::SECRET withObjCType:@encode(nByte)]];
			mFrontEndAddress = [[operationResponse objectForKey:[NSValue value:&ParameterCode::ADDRESS withObjCType:@encode(nByte)]] copy];
			EGLOG(INFO, L"Server returned secret: %ls. %ls", mAuthenticationValues.Secret.UTF32String, [operationResponse toString]);
			[mPeer disconnect];
		}
		else if(mState == ClientState::ConnectingToFrontEnd)
			self.State = ClientState::ConnectedToFrontEnd;	
	}
}

- (void) handleSubscribeResponse:(EGEventData*)eventData
{
	EGArray* channels = [[EGArray alloc] initWithArray:[eventData objectForKey:[NSValue value:&ParameterCode::CHANNELS withObjCType:@encode(nByte)]]];
	EGArray* results = [[EGArray alloc] initWithArray:[eventData objectForKey:[NSValue value:&ParameterCode::SUBSCRIBE_RESULTS withObjCType:@encode(nByte)]]];
	for(int i = 0;i < channels.count;++i)
	{
		if((int)i < results.count)
		{
			bool res = false;
			[results[i] getValue:&res];
			if(res)
				[self getOrAddChannel:mPublicChannels :channels[i] :false];
		}
	}
	[mListener subscribeReturn:channels :results];
}

- (void) handleUnsubscribeResponse:(EGEventData*)eventData
{
	EGArray* channels = [[EGArray alloc] initWithArray:[eventData objectForKey:[NSValue value:&ParameterCode::CHANNELS withObjCType:@encode(nByte)]]];
	for(int i = 0;i < channels.count;++i)
		[self removeChannel:mPublicChannels :channels[i]];
	[mListener unsubscribeReturn:channels];
}

- (void) onStatusChanged:(int)statusCode
{	
	switch(statusCode)
	{
		case 0:
			break;
		case StatusCode::CONNECT:
		{
			[mPeer establishEncryption];	            
			if(self.State == ClientState::ConnectingToNameServer)
			{
				self.State = ClientState::ConnectedToNameServer;
				EGLOG(INFO, L"connected to nameserver");
			}
			else if(self.State == ClientState::ConnectingToFrontEnd)
			{
				[mPeer opAuthenticateOnFrontEnd:mAuthenticationValues.Secret];
				EGLOG(INFO, L"connected to frontend");
			}
		}
			break;
		case StatusCode::DISCONNECT:
		{
			if(self.State == ClientState::Authenticated)
			{
				[mPeer connect:mFrontEndAddress :mAppIDPeerInit];
				self.State = ClientState::ConnectingToFrontEnd;
			}
			else
			{
				self.State = ClientState::Disconnected;
				[mListener disconnectReturn];
			}
		}
			break;
		case StatusCode::ENCRYPTION_ESTABLISHED:
			if(self.State == ClientState::ConnectedToNameServer)
				if(!mDidAuthenticate) {
					if([mPeer opAuthenticateOnNameServer:mAppID :mAppVersion :mRegion :mAuthenticationValues])
						mDidAuthenticate = true;
					else
					{
						mDidAuthenticate = false;
						[mListener debugReturn:ERRORS :[@"Error calling OpAuthenticate! Did not work. Check log output, CustomAuthenticationValues and if you're connected. State: " stringByAppendingFormat:@"%d", self.State]];
					}
				}
			break;
		case StatusCode::ENCRYPTION_FAILED_TO_ESTABLISH:
			[self handleConnectionFlowError:self.State :statusCode :@"Encryption failed to establish"];
			break;
			// cases till next break should set mDisconnectedCause below
		case StatusCode::EXCEPTION:
		case StatusCode::EXCEPTION_ON_CONNECT:
		case StatusCode::INTERNAL_RECEIVE_EXCEPTION:
		case StatusCode::TIMEOUT_DISCONNECT:
		case StatusCode::DISCONNECT_BY_SERVER:
		case StatusCode::DISCONNECT_BY_SERVER_USER_LIMIT:
		case StatusCode::DISCONNECT_BY_SERVER_LOGIC:
			[mListener connectionErrorReturn:statusCode];
			if(mPeer.Peerstate != PeerState::DISCONNECTED && mPeer.Peerstate != PeerState::DISCONNECTING)
				[mPeer disconnect];
			else
				self.State = ClientState::Disconnected;
			break;
		case StatusCode::SEND_ERROR:
			[mListener clientErrorReturn:statusCode];
			break;
		case StatusCode::QUEUE_OUTGOING_RELIABLE_WARNING:
		case StatusCode::QUEUE_OUTGOING_UNRELIABLE_WARNING:
		case StatusCode::QUEUE_OUTGOING_ACKS_WARNING:
		case StatusCode::QUEUE_SENT_WARNING:
			[mListener warningReturn:statusCode];
			break;
		case Chat::ErrorCode::OPERATION_INVALID:
		case Chat::ErrorCode::INTERNAL_SERVER_ERROR:
			[mListener serverErrorReturn:statusCode];
			break;
		default:
			EGLOG(ERRORS, L"received unknown status-code from server");
			break;
	}
	// above cases starting from StatusCode::EXCEPTION till next break should set mDisconnectedCause here
	switch(statusCode)
	{
		case StatusCode::DISCONNECT_BY_SERVER_USER_LIMIT:
			mDisconnectedCause = DisconnectCause::DISCONNECT_BY_SERVER_USER_LIMIT;
			break;
		case StatusCode::EXCEPTION_ON_CONNECT:
			mDisconnectedCause = DisconnectCause::EXCEPTION_ON_CONNECT;
			break;
		case StatusCode::DISCONNECT_BY_SERVER:
			mDisconnectedCause = DisconnectCause::DISCONNECT_BY_SERVER;
			break;
		case StatusCode::DISCONNECT_BY_SERVER_LOGIC:
			mDisconnectedCause = DisconnectCause::DISCONNECT_BY_SERVER_LOGIC;
			break;
		case StatusCode::TIMEOUT_DISCONNECT:
			mDisconnectedCause = DisconnectCause::TIMEOUT_DISCONNECT;
			break;
		case StatusCode::EXCEPTION:
		case StatusCode::INTERNAL_RECEIVE_EXCEPTION:
			mDisconnectedCause = DisconnectCause::EXCEPTION;
			break;
	}
}

- (void) onEvent:(EGEventData*)eventData
{
	EGLOG(ALL, [eventData toString].UTF32String); // don't print out the payload here, as that can get too expensive for big events
	switch(eventData.Code)
	{
		case EventCode::CHAT_MESSAGES:
		{
			EGArray* senders = [[EGArray alloc] initWithArray:[eventData objectForKey:[NSValue value:&ParameterCode::SENDERS withObjCType:@encode(nByte)]]];
			EGArray* messages = [[EGArray alloc] initWithArray:[eventData objectForKey:[NSValue value:&ParameterCode::MESSAGES withObjCType:@encode(nByte)]]];
			NSString* channelName = [eventData objectForKey:[NSValue value:&ParameterCode::CHANNEL withObjCType:@encode(nByte)]];
			EGChatChannel* ch = [self getChannel:mPublicChannels :channelName];
			if(ch)
			{
				[ch addMessages:senders :messages];
				[mListener onGetMessages:channelName :senders :messages];
			}
			else
				EGLOG(WARNINGS, L"Got message from unsubscribed channel %ls", channelName.UTF32String);
			
		}
			break;
		case EventCode::PRIVATE_MESSAGE:
		{
			NSString* message = [eventData objectForKey:[NSValue value:&ParameterCode::MESSAGE withObjCType:@encode(nByte)]];
			NSString* sender = [eventData objectForKey:[NSValue value:&ParameterCode::SENDER withObjCType:@encode(nByte)]];
			NSString* channelName = sender;
			if([sender isEqualToString:self.UserID])
				channelName = [eventData objectForKey:[NSValue value:&ParameterCode::USER_ID withObjCType:@encode(nByte)]];
			[[self getOrAddChannel:mPrivateChannels :channelName :true] addMessage:sender :message];
			[mListener onPrivateMessage:sender :message :channelName];
		}
			break;
		case EventCode::STATUS_UPDATE:
		{
			int status = 0;
			NSString* message = [eventData objectForKey:[NSValue value:&ParameterCode::MESSAGE withObjCType:@encode(nByte)]];
			NSString* user = [eventData objectForKey:[NSValue value:&ParameterCode::SENDER withObjCType:@encode(nByte)]];
			[[eventData objectForKey:[NSValue value:&ParameterCode::STATUS withObjCType:@encode(nByte)]] getValue:&status];
			bool gotMessage = [eventData objectForKey:[NSValue value:&ParameterCode::MESSAGE withObjCType:@encode(nByte)]] != nil;
			[mListener onStatusUpdate:user :status :gotMessage :message];
		}
			break;
		case EventCode::SUBSCRIBE:
			[self handleSubscribeResponse:eventData];
			break;
		case EventCode::UNSUBSCRIBE:
			[self handleUnsubscribeResponse:eventData];
			break;
	}
}

- (void) handleConnectionFlowError:(int)oldState :(int)errorCode :(NSString* const)errorString
{
	self.State = ClientState::Disconnecting;
	[mPeer disconnect];
}

- (void) debugReturn:(int)debugLevel :(NSString*)string
{
	[mListener debugReturn:debugLevel :string];
}

@end