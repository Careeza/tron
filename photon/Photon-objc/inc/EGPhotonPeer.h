/* Exit Games Photon - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import <Foundation/NSNull.h>
#import "Common-objc/inc/EGBase.h"
#import "Common-objc/inc/EGCustomTypeUtils.h"
#import "Common-objc/inc/EGDictionary.h"
#import "Common-objc/inc/EGLogger.h"
#import "Common-objc/inc/EGTime.h"
#import "Common-objc/inc/NSObject+CopyDeep.h"
#import "Common-objc/inc/NSString+UTF32.h"
#import "Common-objc/inc/Enums/EGDebugLevel.h"
#import "Common-objc/inc/Enums/EGTypeCode.h"
#import "Photon-objc/inc/EGOperationRequest.h"
#import "Photon-objc/inc/EGPhotonListener.h"
#import "Photon-objc/inc/EGTrafficStats.h"
#import "Photon-objc/inc/EGTrafficStatsGameLevel.h"
#import "Photon-objc/inc/Enums/EGConnectionProtocol.h"
#import "Photon-objc/inc/Enums/EGErrorCode.h"
#import "Photon-objc/inc/Enums/EGNetworkPort.h"
#import "Photon-objc/inc/Enums/EGPeerState.h"
#import "Photon-objc/inc/Enums/EGStatusCode.h"

extern const int MAX_APP_ID_LENGTH;

@interface EGPhotonPeer : NSObject

@property (readonly) id<EGPhotonListener> Listener;
@property (readonly) int ServerTimeOffset;
@property (readonly) int ServerTime;
@property (readonly) int BytesOut;
@property (readonly) int BytesIn;
@property (readonly) int ByteCountCurrentDispatch;
@property (readonly) int ByteCountLastOperation;
@property (readonly) int Peerstate; // enum ExitGames::Photon::PeerState::PeerState
@property (readwrite) int SentCountAllowance;
@property (readwrite) int TimePingInterval;
@property (readonly) int RoundTripTime;
@property (readonly) int RoundTripTimeVariance;
@property (readonly) int TimestampOfLastSocketReceive;
@property (readwrite) int DebugOutputLevel; // enum ExitGames::Common::DebugLevel::DebugLevel
@property (readonly) short PeerID;
@property (readonly) bool IsEncryptionAvailable;
@property (readonly) int IncomingReliableCommandsCount;
@property (readwrite) int DisconnectTimeout;
@property (readonly) int QueuedIncomingCommands;
@property (readonly) int QueuedOutgoingCommands;
@property (readonly) NSString* ServerAddress;
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

- (instancetype) init NS_UNAVAILABLE;
- (instancetype) initWithPhotonListener:(id<EGPhotonListener>)listener; // = ConnectionProtocol::UDP
- (instancetype) initWithPhotonListener:(id<EGPhotonListener>)listener :(nByte)connectionProtocol;
- (bool) connect:(NSString*)ipAddr; // = NULL
- (bool) connect:(NSString*)ipAddr :(NSString*)appID;
- (void) disconnect;
- (void) service; // = true
- (void) service:(bool)dispatchIncomingCommands;
- (void) serviceBasic;
- (bool) opCustom:(const EGOperationRequest*)operationRequest :(bool)sendReliable; // = 0, = false
- (bool) opCustom:(const EGOperationRequest*)operationRequest :(bool)sendReliable :(nByte)channelID; // = false
- (bool) opCustom:(const EGOperationRequest*)operationRequest :(bool)sendReliable :(nByte)channelID :(bool)encrypt;
- (bool) sendOutgoingCommands;
- (bool) sendAcksOnly;
- (bool) dispatchIncomingCommands;
- (bool) establishEncryption;
- (void) fetchServerTimestamp;
- (void) resetTrafficStats;
- (void) resetTrafficStatsMaximumCounters;
- (NSString*) vitalStatsToString:(bool)all;
- (void) pingServer:(NSString*)address :(unsigned int)attempts;

@end