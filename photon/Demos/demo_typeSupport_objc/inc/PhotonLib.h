#import "demo_photon_CustomType_objc.h"
#import "demo_photon_objc.h"
#import "UIListener.h"
#import "LoadBalancing-objc/inc/EGLoadBalancingClient.h"

typedef enum
{
	SampleStarted = 0,
	PhotonPeerCreated,
	Connecting,
	Connected,
	EstablishingEncryption,
	ErrorEstablishingEncryption,
	EncryptionEstablished,
	Joining,
	ErrorJoining,
	Joined,
	Leaving,
	ErrorLeaving,
	Left,
	ErrorConnecting,
	Receiving,
	Disconnecting,
	Disconnected
} States;

@interface CPhotonLib : NSObject
{
	States currentState;
	Listener* mListener;
	EGLoadBalancingClient* mLoadBalancingClient;
	EGLogger* mLogger;

	id<UIListener> textView;
	SampleCustomType* mpCustomType;
}

@property (readwrite) States State;
@property (readonly) EGLoadBalancingClient* Client;

- (void) InitCPhotonLib:(id<UIListener>) textView;
- (int) Run;
- (int) CreateConnection;
- (int) CloseConnection;
- (short) Join:(NSString*)gameId;
- (short) Leave;
- (void) sendData;
- (void) Stop;

@end