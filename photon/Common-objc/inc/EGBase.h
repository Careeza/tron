/* Exit Games Common - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "Common-objc/inc/EGBaseListener.h"
#import "Common-objc/inc/EGDefines.h"
#import "Common-objc/inc/EGToString.h"

@interface EGBase : NSObject

+ (void) setListener:(id<EGBaseListener>)baseListener;
+ (int) DebugOutputLevel;
+ (void) setDebugOutputLevel:(int)debugOutputLevel;

@end