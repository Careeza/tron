#import <Foundation/Foundation.h>
#include <termios.h>
#include <fcntl.h>
#import "NetworkLogic.h"

int getcharIfKbhit(void);

int getcharIfKbhit(void)
{
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	return ch;
}

@interface iMacOutputListener : NSObject<OutputListener>
@end

@implementation iMacOutputListener

- (void) write:(NSString*)str, ...
{
	va_list args;
	va_start(args, str);
	[self write:str :args];
	va_end(args);
}

- (void) write:(NSString*)str :(va_list)args
{
	wprintf(L"%ls", [[[NSString alloc] initWithFormat:str arguments:args] autorelease].UTF32String);
}

- (void) writeLine:(NSString*)str, ...
{
	va_list args;
	va_start(args, str);
	[self writeLine:str :args]; 
	va_end(args);
}

- (void) writeLine:(NSString*)str :(va_list)args
{
	[self write:str :args];
	wprintf(L"\n");
}

@end



@interface iMacUI :NSObject <NetworkLogicListener>
{
	iMacOutputListener* mOutputListener;
}

- (void) main;

@end



@implementation iMacUI

- (void) main
{
	mOutputListener = [iMacOutputListener new];
	NetworkLogic* networkLogic = [NetworkLogic networkLogicWithOutputListener:mOutputListener :@"1.0"];
	[networkLogic registerForStateUpdates:self];
	[mOutputListener writeLine:@"always:"];
	[mOutputListener writeLine:@"0 - exit"];
	[mOutputListener writeLine:@"--------------------"];
	[mOutputListener writeLine:@"outside a game room:"];
	[mOutputListener writeLine:@"1 - create game"];
	[mOutputListener writeLine:@"2 - join or create game"];
	[mOutputListener writeLine:@"2 - join random or create new game"];
	[mOutputListener writeLine:@"2 - join game"];
	[mOutputListener writeLine:@"2 - join random game"];
	[mOutputListener writeLine:@"--------------------"];
	[mOutputListener writeLine:@"inside a game room:"];
	[mOutputListener writeLine:@"1 - leave game"];
	[mOutputListener writeLine:@"--------------------"];
	while(networkLogic.LastInput != INPUT_EXIT && networkLogic.State != STATE_DISCONNECTED)
	{
		int ch = getcharIfKbhit();
		switch(networkLogic.State)
		{
			case STATE_CONNECTED:
				switch(ch)
			{
				case '0':
					networkLogic.LastInput = INPUT_EXIT;
					break;
				case '1':
					networkLogic.LastInput = INPUT_CREATE_GAME;
					break;
				case '2':
					networkLogic.LastInput = INPUT_JOIN_OR_CREATE_GAME;
					break;
				case '3':
					networkLogic.LastInput = INPUT_JOIN_RANDOM_OR_CREATE_GAME;
					break;
				case '4':
					networkLogic.LastInput = INPUT_JOIN_GAME;
					break;
				case '5':
					networkLogic.LastInput = INPUT_JOIN_RANDOM_GAME;
					break;
				default:
					networkLogic.LastInput = INPUT_NON;
					break;
			}
				break;
			case STATE_JOINED:
				switch(ch)
			{
				case '0':
					networkLogic.LastInput = INPUT_EXIT;
					break;
				case '1':
					networkLogic.LastInput = INPUT_LEAVE_GAME;
					break;
				default:
					networkLogic.LastInput = INPUT_NON;
					break;
			}
				break;
			default:
				switch(ch)
			{
				case '0':
					networkLogic.LastInput = INPUT_EXIT;
					break;
				default:
					networkLogic.LastInput = INPUT_NON;
					break;
			}
				break;
		}
		[networkLogic run];
		usleep(100000);
	}
}

- (void) stateUpdate:(State)newState
{
}

@end



int main(int argc, const char* argv[])
{
	@autoreleasepool
	{
		[[[iMacUI new] autorelease] main];
	}
	return 0;
}