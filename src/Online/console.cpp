#include "console.h"

Console::Console(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
}

Console::~Console(void) {
}

void Console::update(void) {
}

void Console::write(const ExitGames::Common::JString& str) {
	wprintf(L"%ls", str.cstr());
}

void Console::writeLine(const ExitGames::Common::JString& str) {
	wprintf(L"%ls\n", str.cstr());
}

Console& Console::get(void) {
	static Console console;
	return console;
}