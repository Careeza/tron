#import "DemoApplication.h"
#import "PhotonLib.h"
#import "demo_photon_objc.h"

@implementation DemoApplication

+ (void) startDemoWithListener:(id<UIListener>)listener
{
	CPhotonLib* photonLib = [CPhotonLib alloc];
	[photonLib InitCPhotonLib:listener];

	while(YES)
	{
		@autoreleasepool
		{
			if([photonLib Run])
				break;
			else if([listener shouldStopDemo])
			{
				[photonLib Stop];
				break;
			}
		}
		usleep(300000);
	}

	[listener writeToTextView:@"---STOPPED----"];
	[photonLib release];
}

@end