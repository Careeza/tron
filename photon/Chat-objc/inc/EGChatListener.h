/* Exit Games Photon Chat - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import <Foundation/Foundation.h>
#import "Common-objc/inc/EGArray.h"
#import "Common-objc/inc/EGBaseListener.h"

@class EGArray;

@protocol EGChatListener <NSObject, EGBaseListener>

// implement your error-handling here
- (void) onStateChange:(int)state; // enum ExitGames::Chat::ClientState::ClientState
- (void) connectionErrorReturn:(int)errorCode;
- (void) clientErrorReturn:(int)errorCode;
- (void) warningReturn:(int)warningCode;
- (void) serverErrorReturn:(int)errorCode;

// callbacks for operations on server
- (void) connectReturn:(int)errorCode :(NSString*)errorString;
- (void) disconnectReturn;
- (void) subscribeReturn:(EGArray*)channels :(EGArray*)results;
- (void) unsubscribeReturn:(EGArray*)channels;

- (void) onStatusUpdate:(NSString*)user :(int)status :(bool)gotMessage :(id<NSObject>)message;
- (void) onGetMessages:(NSString*)channelName :(EGArray*)senders :(EGArray*)messages;
- (void) onPrivateMessage:(NSString*)sender :(id<NSObject>)message :(NSString*)channelName;

@optional

@end

/** @file */