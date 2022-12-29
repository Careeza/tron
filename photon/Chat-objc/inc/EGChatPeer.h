/* Exit Games Photon Chat - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "Photon-objc/inc/EGPhotonPeer.h"
#import "Chat-objc/inc/EGAuthenticationValues.h"
#import "Common-objc/inc/EGArray.h"

@interface EGChatPeer : EGPhotonPeer

- (bool) opAuthenticateOnNameServer:(NSString*)appID :(NSString*)appVersion :(NSString*)region :(const EGAuthenticationValues*)authenticationValues;
- (bool) opAuthenticateOnFrontEnd:(NSString*)secret;
- (bool) opSubscribe:(EGArray*)channels;
- (bool) opSubscribe:(EGArray*)channels :(int)messagesFromHistory;
- (bool) opUnsubscribe:(EGArray*)channels;
- (bool) opPublishMessage:(NSString*)channelName :(id<NSObject>)message;
- (bool) opSendPrivateMessage:(NSString*)target :(id<NSObject>)message;
- (bool) opSendPrivateMessage:(NSString*)target :(id<NSObject>)message :(bool)encrypt;
- (bool) opSetOnlineStatus:(int)status :(id<NSObject>)message :(bool)skipMessage;
- (bool) opAddFriends:(EGArray*)userIDs;
- (bool) opRemoveFriends:(EGArray*)userIDs;

@end