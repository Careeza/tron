/* Exit Games Common - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */
 
#pragma once

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import "Common-objc/inc/EGArray.h"

@interface EGDictionary : NSDictionary

@property (readonly) NSDictionary* Data;
@property (readonly) EGArray* KeyTypes;
@property (readonly) EGArray* ValTypes;
@property (readonly) EGArray* Dimensions;
@property (readonly) NSString* KeyType;
@property (readonly) NSString* ValType;
@property (readonly) const char* CKeyType;
@property (readonly) const char* CValType;
@property (readonly) NSString* Type;
@property (readonly) const char* CType;
@property (readonly) EGArray* allKeys;

- (instancetype) init NS_UNAVAILABLE;
+ (instancetype) new NS_UNAVAILABLE;
+ (instancetype) dictionary NS_UNAVAILABLE;
- (instancetype) initWithKeyType:(NSString*)keyType valueType:(NSString*)valType;
- (instancetype) initWithKeyType:(NSString*)keyType valueType:(NSString*)valType valueDimensions:(unsigned int)dimension;
- (instancetype) initWithCKeyType:(const char*)keyType valueType:(const char*)valType;
- (instancetype) initWithCKeyType:(const char*)keyType valueType:(const char*)valType valueDimensions:(unsigned int)dimension;
- (instancetype) initWithKeyTypes:(NSString* const[])keys valueTypes:(NSString* const[])vals count:(NSUInteger)cnt;
- (instancetype) initWithKeyTypes:(NSString* const[])keys valueTypes:(NSString* const[])vals valueDimensions:(const unsigned int*)dimension count:(NSUInteger)cnt;
- (instancetype) initWithCKeyTypes:(const char* const[])keys valueTypes:(const char* const[])vals count:(NSUInteger)cnt;
- (instancetype) initWithCKeyTypes:(const char* const[])keys valueTypes:(const char* const[])vals valueDimensions:(const unsigned int*)dimension count:(NSUInteger)cnt;
- (instancetype) initWithCoder:(NSCoder*)aDecoder NS_DESIGNATED_INITIALIZER;
+ (instancetype) dictionaryWithKeyType:(NSString*)keyType valueType:(NSString*)valType;
+ (instancetype) dictionaryWithKeyType:(NSString*)keyType valueType:(NSString*)valType valueDimensions:(unsigned int)dimension;
+ (instancetype) dictionaryWithCKeyType:(const char*)keyType valueType:(const char*)valType;
+ (instancetype) dictionaryWithCKeyType:(const char*)keyType valueType:(const char*)valType valueDimensions:(unsigned int)dimension;
+ (instancetype) dictionaryWithKeyTypes:(NSString* const[])keys valueTypes:(NSString* const[])vals count:(NSUInteger)cnt;
+ (instancetype) dictionaryWithKeyTypes:(NSString* const[])keys valueTypes:(NSString* const[])vals valueDimensions:(const unsigned int*)dimension count:(NSUInteger)cnt;
+ (instancetype) dictionaryWithCKeyTypes:(const char* const[])keys valueTypes:(const char* const[])vals count:(NSUInteger)cnt;
+ (instancetype) dictionaryWithCKeyTypes:(const char* const[])keys valueTypes:(const char* const[])vals valueDimensions:(const unsigned int*)dimension count:(NSUInteger)cnt;
+ (instancetype) dictionaryWithCoder:(NSCoder*)aDecoder;
+ (NSString*) getTypeFromObj:(id)obj;
+ (const char*) getCTypeFromObj:(id)obj;

@end


@interface EGMutableDictionary : EGDictionary

@property (readwrite, copy) NSMutableDictionary* MutableData;

- (void)setObject:(id)anObject forKey:(id)aKey;
- (void)setValue:(id)value forKey:(NSString*)key;
- (void)addEntriesFromDictionary:(NSDictionary *)otherDictionary;
- (void)setDictionary:(NSDictionary*)otherDictionary;
- (void)removeObjectForKey:(id)aKey;
- (void)removeAllObjects;
- (void)removeObjectsForKeys:(NSArray*)keyArray;

- (instancetype) initWithCapacity:(NSUInteger)numItems;
+ (instancetype) dictionaryWithCapacity:(NSUInteger)numItems;

@end