/* Exit Games Common - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "Common-objc/inc/EGBaseListener.h"
#import "Common-objc/inc/NSString+UTF32.h"

@interface EGLogger : NSObject

@property (readwrite) int DebugOutputLevel;
- (void) setListener:(id<EGBaseListener>)listener;

- (instancetype) initWithDebugOutputLevel:(int)debugLevel NS_DESIGNATED_INITIALIZER;
+ (instancetype) logger;
+ (instancetype) loggerWithDebugOutputLevel:(int)debugLevel;
- (void) log:(int)debugLevel :(const EG_CHAR*)file :(const EG_CHAR*)function :(unsigned int)line :(const EG_CHAR*)dbgMsg, ...;
- (void) vlog:(int)debugLevel :(const EG_CHAR*)file :(const EG_CHAR*)function :(unsigned int)line :(const EG_CHAR*)dbgMsg :(va_list)args;

@end

#ifdef EG_LOGGING
#	undef EGLOG
#	define EGLOG(debugLevel, ...) [self.Logger log:debugLevel :__WFILE__ :__WFUNCTION__ :__LINE__ :__VA_ARGS__]
#	define EGVLOG(debugLevel, dbgMsg, args) [self.Logger vlog:debugLevel :__WFILE__ :__WFUNCTION__ :__LINE__ :dbgMsg :args]
#endif