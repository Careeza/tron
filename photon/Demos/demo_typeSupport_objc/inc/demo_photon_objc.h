#import "UIListener.h"
#import "LoadBalancing-objc/inc/EGLoadBalancingClient.h"

@class CPhotonLib;

@interface Listener : NSObject <EGLoadBalancingListener>
{
@private
	CPhotonLib* current;
	id<UIListener> textView;
	EGLogger* mLogger;
}

- (Listener*) initListener:(CPhotonLib*)lib :(id<UIListener>)txtView :(EGLogger*)logger;

@end