#pragma once

#define EGTypeCode_BYTE               ((nByte)'b') ///<nByte
#define EGTypeCode_SHORT              ((nByte)'k') ///<short
#define EGTypeCode_INTEGER            ((nByte)'i') ///<int
#define EGTypeCode_LONG               ((nByte)'l') ///<int64
#define EGTypeCode_FLOAT              ((nByte)'f') ///<float
#define EGTypeCode_DOUBLE             ((nByte)'d') ///<double
#define EGTypeCode_BOOLEAN            ((nByte)'o') ///<bool
#define EGTypeCode_STRING             ((nByte)'s') ///<@if CPP JString@endif @if OBJC NSString@endif
#define EGTypeCode_HASHTABLE          ((nByte)'h') ///<@if CPP Hashtable@endif @if OBJC NSDictionary@endif
#define EGTypeCode_DICTIONARY         ((nByte)'D') ///<@if CPP Dictionary@endif @if OBJC EGDictionary@endif
#define EGTypeCode_OBJECT             ((nByte)'z') ///<@if CPP Object@endif @if OBJC NSObject@endif, only allowed for arrays!
#define EGTypeCode_ARRAY              ((nByte)'y') ///<internal only
#define EGTypeCode_BYTEARRAY          ((nByte)'x') ///<internal only
#define EGTypeCode_PHOTON_COMMAND     ((nByte)'p') ///<internal only@internal used for photon commands
#define EGTypeCode_EG_NULL            ((nByte)'*') ///<internal only@internal for adding NULL as a value to a HashTable
#define EGTypeCode_CUSTOM             ((nByte)'c') ///<internal only@internal for custom data, (de-)serialized by callbacks, implemented by the application
#define EGTypeCode_UNKNOWN            ((nByte)0) ///<internal only@internal used instead of OBJECT for values inside an Dictionary