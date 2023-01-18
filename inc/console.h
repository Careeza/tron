#ifndef CONSOLE_H

# define CONSOLE_H

#include "outputListener.h"

class ConsoleImplementation;

class Console : public OutputListener
{
public:
	Console(void);
	~Console(void);
	void update(void);
	void write(const ExitGames::Common::JString& str);
	void writeLine(const ExitGames::Common::JString& str=ExitGames::Common::JString());
	static Console& get(void);
};

#endif