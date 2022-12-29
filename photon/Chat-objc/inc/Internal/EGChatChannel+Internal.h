/* Exit Games Photon Chat - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "Chat-objc/inc/EGChatChannel.h"

@interface EGChatChannel ()

- (instancetype) initChannel:(NSString*)name :(bool)isPrivate NS_DESIGNATED_INITIALIZER;
+ (instancetype) channel:(NSString*)name :(bool)isPrivate;
- (void) addMessage:(NSString*)sender :(id<NSObject>)message;
- (void) addMessages:(EGArray*)senders :(EGArray*)messages;

@end