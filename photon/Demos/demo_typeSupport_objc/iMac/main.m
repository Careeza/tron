
#import <Foundation/Foundation.h>
#include <termios.h>
#include <fcntl.h>

#import "UIListener.h"
#import "DemoApplication.h"

@interface iMacUiListener : NSObject<UIListener>
@end

@implementation iMacUiListener

-(BOOL) isAnyKeyPressed
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

	if(ch != EOF)
		return YES;

	return NO;
}

-(void) writeToTextView:(NSString*)text
{
	printf("%s\n\n", text.UTF8String);
}

-(BOOL) shouldStopDemo
{
	return [self isAnyKeyPressed];
}

@end

int main (int argc, const char * argv[])
{
	@autoreleasepool
	{
		iMacUiListener* l = [iMacUiListener new];
		[DemoApplication startDemoWithListener:l];
		[l release];
	}
	return 0;
}