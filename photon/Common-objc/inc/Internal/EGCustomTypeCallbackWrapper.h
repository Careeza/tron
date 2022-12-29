/* Exit Games Common - objC Client Lib
 * Copyright (C) 2004-2022 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import <Foundation/NSData.h>
#import <Foundation/NSDictionary.h>
#import "Common-objc/inc/EGCustomType.h"
#include "Common-cpp/inc/Helpers/CustomTypeCallbackWrapper.h"

class EGCustomTypeCallbackWrapper: public ExitGames::Common::Helpers::CustomTypeCallbackWrapper
{
public:
	EGCustomTypeCallbackWrapper();

	static void initClass(nByte typeCode, Class<EGCustomType> delegate);
	static Class<EGCustomType> getClassForCode(nByte typecode);
	
	static void* cbCalloc(int count, nByte customTypeCode);
	static void cbFree(const void* pData, nByte customTypeCode);
	static unsigned int cbSizeOf(nByte customTypeCode);

	//From ExitGames::Common::CustomTypeCallbackWrapper
	virtual void cleanup(const void* pData);
	virtual bool compare(const void* pData1, void* pData2);
	virtual void duplicate(const void* pData, void* retVal);
	virtual void deserialize(const nByte* pData, short length, void* retVal);
	virtual short serialize(const void* pData, nByte* retVal);
	virtual unsigned int toString(const void* pData, EG_CHAR* buffer);
	virtual ExitGames::Common::Helpers::CustomTypeCallbackWrapper* copy() const;

private:
	static Class<EGCustomType> mDelegates[UCHAR_MAX];
	static NSMutableDictionary* getAllocationSizes(void);
};