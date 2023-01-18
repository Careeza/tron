#pragma once

#include <iostream>
#include "Common-cpp/inc/Common.h"

class OutputListener : public virtual ExitGames::Common::BaseListener
{
public:
	virtual ~OutputListener(void){};
	virtual void write(const ExitGames::Common::JString& str) = 0;
	virtual void writeLine(const ExitGames::Common::JString& str=ExitGames::Common::JString()) = 0;
	virtual void debugReturn(int debugLevel, const ExitGames::Common::JString& str) {
		fwprintf(stderr, L"%ls\n", str.cstr());
	}
};