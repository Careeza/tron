/* Exit Games Photon LoadBalancing - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "LoadBalancing-objc/inc/EGFriendInfo.h"
#import "LoadBalancing-objc/inc/EGLoadBalancingListener.h"
#import "LoadBalancing-objc/inc/EGLoadBalancingPeer.h"
#import "LoadBalancing-objc/inc/EGLoadBalancingRoom.h"
#import "LoadBalancing-objc/inc/EGLobbyStatsResponse.h"
#import "LoadBalancing-objc/inc/Enums/EGCustomAuthenticationType.h"
#import "LoadBalancing-objc/inc/Enums/EGDisconnectCause.h"
#import "LoadBalancing-objc/inc/Enums/EGErrorCode.h"
#import "LoadBalancing-objc/inc/Enums/EGLobbyType.h"
#import "LoadBalancing-objc/inc/Enums/EGMatchmakingMode.h"
#import "LoadBalancing-objc/inc/Enums/EGPeerStates.h"
#import "LoadBalancing-objc/inc/Enums/EGRegionSelectionMode.h"
#import "LoadBalancing-objc/inc/Enums/EGServerType.h"

@interface EGLoadBalancingClient : NSObject <EGPhotonListener>

@property (readonly) int ServerTimeOffset;
@property (readonly) int ServerTime;
@property (readonly) int BytesOut;
@property (readonly) int BytesIn;
@property (readonly) int ByteCountCurrentDispatch;
@property (readonly) int ByteCountLastOperation;
@property (readwrite) int SentCountAllowance;
@property (readwrite) int TimePingInterval;
@property (readonly) int RoundTripTime;
@property (readonly) int RoundTripTimeVariance;
@property (readonly) int TimestampOfLastSocketReceive;
@property (readwrite) int DebugOutputLevel;
@property (readonly) int IncomingReliableCommandsCount;
@property (readonly) short PeerID;
@property (readwrite) int DisconnectTimeout;
@property (readonly) int QueuedIncomingCommands;
@property (readonly) int QueuedOutgoingCommands;
@property (readonly) bool IsEncryptionAvailable;
@property (readonly) int ResentReliableCommands;
@property (readwrite) int LimitOfUnreliableCommands;
@property (readwrite) bool CRCEnabled;
@property (readonly) int PacketLossByCRC;
@property (readwrite) bool TrafficStatsEnabled;
@property (readonly) int TrafficStatsElapsedMs;
@property (readonly) EGTrafficStats* TrafficStatsIncoming;
@property (readonly) EGTrafficStats* TrafficStatsOutgoing;
@property (readonly) EGTrafficStatsGameLevel* TrafficStatsGameLevel;
@property (readwrite) nByte QuickResendAttempts;
@property (readonly) short PeerCount;
@property (readonly) int State;
@property (readonly) NSString* MasterserverAddress;
@property (readonly) int CountPlayersIngame;
@property (readonly) int CountGamesRunning;
@property (readonly) int CountPlayersOnline;
@property (readonly) EGLoadBalancingMutableRoom* CurrentlyJoinedRoom;
@property (readonly) NSDictionary* RoomList;
@property (readonly) bool IsInRoom;
@property (readonly) bool IsInGameRoom;
@property (readonly) bool IsInLobby;
@property (readwrite) bool AutoJoinLobby;
@property (readonly) EGLoadBalancingMutablePlayer* LocalPlayer;
@property (readonly) EGArray* FriendList;
@property (readonly) int FriendListAge;
@property (readonly) int DisconnectedCause;
@property (readonly) NSString* UserID;
@property (readonly) NSString* RegionWithBestPing;

- (instancetype) init NS_UNAVAILABLE;
- (instancetype) initClient:(id<EGLoadBalancingListener>)listener :(NSString*)applicationID :(NSString*)appVersion;
- (instancetype) initClient:(id<EGLoadBalancingListener>)listener :(NSString*)applicationID :(NSString*)appVersion :(nByte)connectionProtocol;
- (instancetype) initClient:(id<EGLoadBalancingListener>)listener :(NSString*)applicationID :(NSString*)appVersion :(nByte)connectionProtocol :(bool)autoLobbyStats;
- (instancetype) initClient:(id<EGLoadBalancingListener>)listener :(NSString*)applicationID :(NSString*)appVersion :(nByte)connectionProtocol :(bool)autoLobbyStats :(nByte)regionSelectionMode NS_DESIGNATED_INITIALIZER;
+ (instancetype) new NS_UNAVAILABLE;

- (bool) connect; // nil
- (bool) connect:(EGAuthenticationValues*)authenticationValues; // = nil
- (bool) connect:(EGAuthenticationValues*)authenticationValues :(NSString*)username; // = NAMESERVER
- (bool) connect:(EGAuthenticationValues*)authenticationValues :(NSString*)username :(NSString*)serverAddress; // = ServerType::NAME_SERVER
- (bool) connect:(EGAuthenticationValues*)authenticationValues :(NSString*)username :(NSString* const)serverAddress :(nByte)serverType;
- (void) disconnect;
- (void) service; // = true
- (void) service:(bool)dispatchIncomingCommands;
- (void) serviceBasic;
- (bool) sendOutgoingCommands;
- (bool) sendAcksOnly;
- (bool) dispatchIncomingCommands;
- (void) fetchServerTimestamp;
- (void) resetTrafficStats;
- (void) resetTrafficStatsMaximumCounters;
- (NSString*) vitalStatsToString:(bool)all;

- (bool) opJoinLobby;
- (bool) opJoinLobby:(NSString*)lobbyName;
- (bool) opJoinLobby:(NSString*)lobbyName :(nByte)lobbyType;
- (bool) opLeaveLobby;
- (bool) opCreateRoom;
- (bool) opCreateRoom:(NSString*)gameID;
- (bool) opCreateRoom:(NSString*)gameID :(EGRoomOptions*)options;
- (bool) opJoinOrCreateRoom:(NSString*)gameID;
- (bool) opJoinOrCreateRoom:(NSString*)gameID :(EGRoomOptions*)options;
- (bool) opJoinOrCreateRoom:(NSString*)gameID :(EGRoomOptions*)options :(int)cacheSliceIndex;
- (bool) opJoinRandomOrCreateRoom;
- (bool) opJoinRandomOrCreateRoom:(NSString*)gameID;
- (bool) opJoinRandomOrCreateRoom:(NSString*)gameID :(EGRoomOptions*)options;
- (bool) opJoinRandomOrCreateRoom:(NSString*)gameID :(EGRoomOptions*)options :(NSDictionary*)customRoomProperties;
- (bool) opJoinRandomOrCreateRoom:(NSString*)gameID :(EGRoomOptions*)options :(NSDictionary*)customRoomProperties :(nByte)maxPlayers;
- (bool) opJoinRandomOrCreateRoom:(NSString*)gameID :(EGRoomOptions*)options :(NSDictionary*)customRoomProperties :(nByte)maxPlayers :(nByte)matchmakingMode;
- (bool) opJoinRandomOrCreateRoom:(NSString*)gameID :(EGRoomOptions*)options :(NSDictionary*)customRoomProperties :(nByte)maxPlayers :(nByte)matchmakingMode :(NSString*)lobbyName;
- (bool) opJoinRandomOrCreateRoom:(NSString*)gameID :(EGRoomOptions*)options :(NSDictionary*)customRoomProperties :(nByte)maxPlayers :(nByte)matchmakingMode :(NSString*)lobbyName :(nByte)lobbyType;
- (bool) opJoinRandomOrCreateRoom:(NSString*)gameID :(EGRoomOptions*)options :(NSDictionary*)customRoomProperties :(nByte)maxPlayers :(nByte)matchmakingMode :(NSString*)lobbyName :(nByte)lobbyType :(NSString*)sqlLobbyFilter;
- (bool) opJoinRoom:(NSString*)gameID;
- (bool) opJoinRoom:(NSString*)gameID :(int)playerNumber;
- (bool) opJoinRoom:(NSString*)gameID :(int)playerNumber :(int)cacheSliceIndex;
- (bool) opJoinRandomRoom;
- (bool) opJoinRandomRoom:(NSDictionary*)customRoomProperties;
- (bool) opJoinRandomRoom:(NSDictionary*)customRoomProperties :(nByte)maxPlayers;
- (bool) opJoinRandomRoom:(NSDictionary*)customRoomProperties :(nByte)maxPlayers :(nByte)matchmakingMode;
- (bool) opJoinRandomRoom:(NSDictionary*)customRoomProperties :(nByte)maxPlayers :(nByte)matchmakingMode :(NSString*)lobbyName;
- (bool) opJoinRandomRoom:(NSDictionary*)customRoomProperties :(nByte)maxPlayers :(nByte)matchmakingMode :(NSString*)lobbyName :(nByte)lobbyType;
- (bool) opJoinRandomRoom:(NSDictionary*)customRoomProperties :(nByte)maxPlayers :(nByte)matchmakingMode :(NSString*)lobbyName :(nByte)lobbyType :(NSString*)sqlLobbyFilter;
- (bool) opLeaveRoom; // = false
- (bool) opLeaveRoom:(bool)willComeBack;
- (bool) opRaiseEvent:(bool)reliable :(id<NSObject>)parameters :(nByte)eventCode;
- (bool) opRaiseEvent:(bool)reliable :(id<NSObject>)parameters :(nByte)eventCode :(EGRaiseEventOptions*)raiseEventOptions;
- (bool) opFindFriends:(EGArray*)friendsToFind;
- (bool) opLobbyStats; // = nil
- (bool) opLobbyStats:(EGArray*)lobbiesToQuery; // array of EGLobbyStatsRequest
- (bool) opChangeGroups:(EGArray*)groupsToRemove :(EGArray*)groupsToAdd; // arrays of nByte
- (bool) opCustomAuthenticationSendNextStepData:(EGAuthenticationValues*)authenticationValues;
- (bool) opWebRpc:(NSString*)uriPath; // = nil
- (bool) opWebRpc:(NSString*)uriPath :(id<NSObject>)parameters;
- (bool) selectRegion:(NSString*)selectedRegion;

@end