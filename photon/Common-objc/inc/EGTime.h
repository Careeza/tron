/* Exit Games Common - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "Common-objc/inc/EGBase.h"

@interface EGTime : EGBase
{
}

+ (bool) less:(int)firstTime :(int)secondTime;
+ (bool) greater:(int)firstTime :(int)secondTime;
+ (bool) lessOrEqual:(int)firstTime :(int)secondTime;
+ (bool) greaterOrEqual:(int)firstTime :(int)secondTime;
+ (int) difference:(int)firstTime :(int)secondTime;

@end