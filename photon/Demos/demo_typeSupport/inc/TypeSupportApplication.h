#pragma once

class UIListener;

class TypeSupportApplication
{
public:
	//Launch main loop
	//this function takes ownership of listener
	static void run(UIListener* pListener);
};