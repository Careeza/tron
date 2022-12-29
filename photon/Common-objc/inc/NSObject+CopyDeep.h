/* Exit Games Common - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import <Foundation/NSObject.h>

@interface NSObject (CopyDeep)

- (id) copyDeep;
- (id) mutableCopyDeep;

@end