/* Exit Games Common - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import <Foundation/NSString.h>

@protocol EGBaseListener

- (void) debugReturn:(int)debugLevel :(NSString*)string;

@end

/** @file */