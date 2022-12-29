#import "Common-cpp/inc/Common.h"
#import "demo_photon_objc.h"
#import "PhotonLib.h"

@interface Listener ()

@property (readonly) EGLogger* Logger;

@end

@implementation Listener

@synthesize Logger = mLogger;

-(Listener*) initListener:(CPhotonLib*)lib :(id<UIListener>)txtView :(EGLogger*)logger
{
	current = lib;
	textView = txtView;
	mLogger = logger;
	return self;
}

- (void) debugReturn:(int)debugLevel :(NSString*)string
{
	fwprintf(stderr, L"%ls\n", string.UTF32String);
}

- (void) connectionErrorReturn:(int)errorCode
{
	EGLOG(EGDebugLevel_ERRORS, L" code: %d", errorCode);
	[textView writeToTextView:[NSString stringWithFormat:@"connection failed with error %d", errorCode]];
	current.State = Connected;
}

- (void) clientErrorReturn:(int)errorCode
{
	EGLOG(EGDebugLevel_ERRORS, L" code: %d", errorCode);
	[textView writeToTextView:[NSString stringWithFormat:@"received error %d from client", errorCode]];
}

- (void) warningReturn:(int)warningCode
{
	EGLOG(EGDebugLevel_WARNINGS, L" code: %d", warningCode);
	[textView writeToTextView:[NSString stringWithFormat:@"received warning %d from client", warningCode]];
}

- (void) serverErrorReturn:(int)errorCode
{
	EGLOG(EGDebugLevel_ERRORS, L" code: %d", errorCode);
	[textView writeToTextView:[NSString stringWithFormat:@"received error %d from server", errorCode]];
}

- (void) joinRoomEventAction:(int)playerNr :(EGArray*)playernrs :(EGLoadBalancingPlayer*)player
{
	EGLOG(EGDebugLevel_INFO, L"%ls joined the game", player.Name.UTF32String);
	[textView writeToTextView:[NSString stringWithFormat:@""]];
	[textView writeToTextView:[NSString stringWithFormat:@"player %d %@ has joined the game", playerNr, player.Name]];
}

- (void) leaveRoomEventAction:(int)playerNr :(bool)isInactive
{
	EGLOG(EGDebugLevel_INFO, L"");
	[textView writeToTextView:[NSString stringWithFormat:@""]];
	[textView writeToTextView:[NSString stringWithFormat:@"player %d has left the game %s", playerNr, isInactive?"(will be back)":""]];
}

- (void) customEventAction:(int)playerNr :(nByte)eventCode :(NSObject*)eventContentObj
{
	NSDictionary* eventDataContent = (NSDictionary*)eventContentObj;
	[textView writeToTextView:[eventDataContent toString:true]];
	switch(eventCode)
	{
		// you do not receive your own events, so you must start 2 clients, to receive the events, you sent
		case 0:
		{
			const nByte POS_X = 101, POS_Y = 102, key2 = 103;
			EGArray* ary = nil, *ary2 = nil, *ary3 = nil;
			NSArray* objAry = nil;
			int x = 0, y = 0;
			NSDictionary* testHash = nil;

			// then take your user data from within the inner hash

			// nByte key and int value:
			[(NSValue*)[eventDataContent objectForKey:[NSValue value:&POS_X withObjCType:@encode(nByte)]] getValue:&x];

			// NSString key and EGArray of float value
			ary = [eventDataContent objectForKey:@"testKey"];

			// nByte key and NSDictionary value
			testHash = [eventDataContent objectForKey:[NSValue value:&key2 withObjCType:@encode(nByte)]];
			[((NSValue*)[testHash objectForKey:[NSValue value:&POS_X withObjCType:@encode(nByte)]])getValue:&x];
			[((NSValue*)[testHash objectForKey:[NSValue value:&POS_Y withObjCType:@encode(nByte)]])getValue:&y];

			// NSString key and empty EGArray of int value
			ary2 = [eventDataContent objectForKey:@"emptyArray"];

			// NSString key and 3-dimensional EGArray of NSString value
			ary3 = [eventDataContent objectForKey:@"array3d"];

			// NSString key and NSArray value
			objAry = [eventDataContent objectForKey:@"objectArray"];
		}
			break;
		default:
			break;
	}
}

- (void) connectReturn:(int)errorCode :(NSString*)errorString :(NSString*)region :(NSString*)cluster
{
	EGLOG(EGDebugLevel_INFO, L"");
	if(errorCode)
	{
		EGLOG(EGDebugLevel_ERRORS, L"%ls", errorString.UTF32String);
		current.State = Disconnecting;
		return;
	}
	current.State = Connected;
	[textView writeToTextView:@"-------CONNECTED-------"];
}

- (void) disconnectReturn
{
	EGLOG(EGDebugLevel_INFO, L"");
	current.State = Disconnected;
	[textView writeToTextView:@"-------DISCONNECTED-------"];
}

- (void) createRoomReturn:(int)localPlayerNr :(NSDictionary*)gameProperties :(NSDictionary*)playerProperties :(int)errorCode :(NSString*)errorString
{
	EGLOG(EGDebugLevel_INFO, L"");
	if(errorCode)
	{
		EGLOG(EGDebugLevel_ERRORS, L"%ls", errorString.UTF32String);
		[textView writeToTextView:[NSString stringWithFormat:@"opCreateRoom() failed: %@", errorString]];
		current.State = ErrorJoining;
		return;
	}
	EGLOG(EGDebugLevel_INFO, L"localPlayerNr: %d", localPlayerNr);
	[textView writeToTextView:[NSString stringWithFormat:@"game room \"%@\" has been created", current.Client.CurrentlyJoinedRoom.Name]];
	current.State = Joined;
	[textView writeToTextView:@"----------JOINED-------"];
}

- (void) joinOrCreateRoomReturn:(int)localPlayerNr :(NSDictionary*)gameProperties :(NSDictionary*)playerProperties :(int)errorCode :(NSString*)errorString
{
	EGLOG(EGDebugLevel_INFO, L"");
	if(errorCode)
	{
		EGLOG(EGDebugLevel_ERRORS, L"%ls", errorString.UTF32String);
		[textView writeToTextView:[NSString stringWithFormat:@"opJoinOrCreateRoom() failed: %@", errorString]];
		current.State = ErrorJoining;
		return;
	}
	EGLOG(EGDebugLevel_INFO, L"localPlayerNr: %d", localPlayerNr);
	[textView writeToTextView:[NSString stringWithFormat:@"game room \"%@\" has been entered", current.Client.CurrentlyJoinedRoom.Name]];
	current.State = Joined;
	[textView writeToTextView:@"----------JOINED-------"];
}

- (void) joinRoomReturn:(int)localPlayerNr :(NSDictionary*)gameProperties :(NSDictionary*)playerProperties :(int)errorCode :(NSString*)errorString
{
	EGLOG(EGDebugLevel_INFO, L"");
	if(errorCode)
	{
		EGLOG(EGDebugLevel_ERRORS, L"%ls", errorString.UTF32String);
		[textView writeToTextView:[NSString stringWithFormat:@"opJoinRoom() failed: %@", errorString]];
		current.State = ErrorJoining;
		return;
	}
	EGLOG(EGDebugLevel_INFO, L"localPlayerNr: %d", localPlayerNr);
	[textView writeToTextView:[NSString stringWithFormat:@"game room \"%@\" has been successfully joined", current.Client.CurrentlyJoinedRoom.Name]];
	[textView writeToTextView:[NSString stringWithFormat:@"regularly sending dummy events now"]];
	current.State = Joined;
	[textView writeToTextView:@"----------JOINED-------"];

}

- (void) joinRandomRoomReturn:(int)localPlayerNr :(NSDictionary*)gameProperties :(NSDictionary*)playerProperties :(int)errorCode :(NSString*)errorString
{
	EGLOG(EGDebugLevel_INFO, L"");
	if(errorCode)
	{
		EGLOG(EGDebugLevel_ERRORS, L"%ls", errorString.UTF32String);
		[textView writeToTextView:[NSString stringWithFormat:@"opJoinRandomRoom() failed: %@", errorString]];
		current.State = ErrorJoining;
		return;
	}
	EGLOG(EGDebugLevel_INFO, L"localPlayerNr: %d", localPlayerNr);
	[textView writeToTextView:[NSString stringWithFormat:@"game room \"%@\" has been successfully joined", current.Client.CurrentlyJoinedRoom.Name]];
	current.State = Joined;
	[textView writeToTextView:@"----------JOINED-------"];
}

- (void) leaveRoomReturn:(int)errorCode :(NSString*)errorString
{
	EGLOG(EGDebugLevel_INFO, L"");
	if(errorCode)
	{
		EGLOG(EGDebugLevel_ERRORS, L"%ls", errorString.UTF32String);
		[textView writeToTextView:[NSString stringWithFormat:@"opLeaveRoom() failed: %@", errorString]];
		//current.State = Disconnected;
		current.State = Left;
		return;
	}
	[textView writeToTextView:[NSString stringWithFormat:@"game room has been successfully left"]];
	current.State = Left;
	[textView writeToTextView:@"----------LEFT-------"];
}

- (void) gotQueuedReturn
{
	EGLOG(EGDebugLevel_INFO, L"");
}

- (void) joinLobbyReturn
{
	EGLOG(EGDebugLevel_INFO, L"");
	[textView writeToTextView:[NSString stringWithFormat:@"joined lobby"]];
}

- (void) leaveLobbyReturn
{
	EGLOG(EGDebugLevel_INFO, L"");
	[textView writeToTextView:[NSString stringWithFormat:@"left lobby"]];
}

@end