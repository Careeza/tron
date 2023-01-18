#include "LoadBalancing-cpp/inc/Client.h"
#include "LoadBalancing-cpp/inc/Listener.h"
#include "online.hpp"
#include <unistd.h>
// #include "game.hpp"

MyListener::MyListener() : ExitGames::LoadBalancing::Listener(), mIsConnected(false), roomJoinedOrCreated(false), nbPlayers(0), errorInConnection(false) {}

void MyListener::debugReturn(int debugLevel, const ExitGames::Common::JString& string)
{
	std::cout << "debugReturn: " << string << std::endl;
	// Provide an implementation for the debugReturn function here
}

void MyListener::connectionErrorReturn(int errorCode)
{
	errorInConnection = true;
	std::cerr << "Error in connection: " << errorCode << std::endl;
	// Provide an implementation for the connectionErrorReturn function here
}

void MyListener::clientErrorReturn(int errorCode)
{
	std::cerr << "Error in client: " << errorCode << std::endl;
	// Provide an implementation for the clientErrorReturn function here
}

void MyListener::warningReturn(int warningCode)
{
	std::cerr << "Warning: " << warningCode << std::endl;
	// Provide an implementation for the warningReturn function here
}

void MyListener::serverErrorReturn(int errorCode)
{
	std::cerr << "Error in server: " << errorCode << std::endl;
	// Provide an implementation for the serverErrorReturn function here
}

void MyListener::joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player)
{
	roomJoinedOrCreated = true;
	nbPlayers = playernrs.getSize();
	std::cout << "Player " << playerNr << " joined the room" << std::endl;
	// Provide an implementation for the joinRoomEventAction function here
}

void MyListener::leaveRoomEventAction(int playerNr, bool isInactive)
{
	std::cout << "Player " << playerNr << " left the room" << std::endl;
	// Provide an implementation for the leaveRoomEventAction function here
}

void MyListener::customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent)
{
	std::cout << "Player " << playerNr << " sent a custom event" << std::endl;
	switch(eventCode)
	{
		case 1:
			std::cout << "Event code 1" << std::endl;
			// ExitGames::Common::Hashtable content = ExitGames::Common::ValueObject<ExitGames::Common::Hashtable>(eventContent).getDataCopy();
			// ExitGames::Common::Hashtable* pContent = ExitGames::Common::ValueObject<ExitGames::Common::Hashtable>(eventContent).getDataAddress();
			break;
		default:
			break;
	}
}

void MyListener::connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& region, const ExitGames::Common::JString& cluster)
{
	mIsConnected = true;
	std::cout << "Connected to " << region << std::endl;
	// Provide an implementation for the connectReturn function here
}

void MyListener::disconnectReturn(void)
{
	std::cout << "Disconnected" << std::endl;
	// Provide an implementation for the disconnectReturn function here
}

void MyListener::createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& roomProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
{
	std::cout << "Room created" << std::endl;
	// Provide an implementation for the createRoomReturn function here
}
void MyListener::joinOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& roomProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
{
	std::cout << "Room joined or created" << std::endl;
	// Provide an implementation for the joinOrCreateRoomReturn function here
}

void MyListener::joinRandomOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& roomProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
{
	std::cout << "Room joined or created" << std::endl;
	// Provide an implementation for the joinRandomOrCreateRoomReturn function here
}

void MyListener::joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& roomProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
{
	std::cout << "Room joined" << std::endl;
	// Provide an implementation for the joinRoomReturn function here
}

void MyListener::joinRandomRoomReturn(int /*localPlayerNr*/, const ExitGames::Common::Hashtable& /*roomProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int /*errorCode*/, const ExitGames::Common::JString& /*errorString*/) {
	std::cout << "Room joined" << std::endl;
}

void MyListener::leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString)
{
	std::cout << "Room left" << std::endl;
	// Provide an implementation for the leaveRoomReturn function here
}

void MyListener::joinLobbyReturn(void)
{
	std::cout << "Joined lobby" << std::endl;
	// Provide an implementation for the joinLobbyReturn function here
}

void MyListener::leaveLobbyReturn(void)
{
	std::cout << "Left lobby" << std::endl;
	// Provide an implementation for the leaveLobbyReturn function here
}

void MyListener::onFindFriendsResponse(void)
{
	std::cout << "Friends found" << std::endl;
	// Provide an implementation for the onFindFriendsResponse function here
}

void MyListener::onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
{
	std::cout << "Lobby stats received" << std::endl;
	// Provide an implementation for the onLobbyStatsResponse function here
}

void MyListener::webRpcReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& uriPath, int resultCode, const ExitGames::Common::Dictionary<ExitGames::Common::Object, ExitGames::Common::Object>& returnData)
{
	std::cout << "WebRPC returned" << std::endl;
	// Provide an implementation for the webRpcReturn function here
}

void MyListener::onRoomListUpdate(void)
{
	std::cout << "Room list updated" << std::endl;
	// Provide an implementation for the onRoomListUpdate function here
}

void MyListener::onRoomPropertiesChange(const ExitGames::Common::Hashtable& changes)
{
	std::cout << "Room properties changed" << std::endl;
	// Provide an implementation for the onRoomPropertiesChange function here
}

void MyListener::onPlayerPropertiesChange(int playerNr, const ExitGames::Common::Hashtable& changes)
{
	std::cout << "Player properties changed" << std::endl;
	// Provide an implementation for the onPlayerPropertiesChange function here
}

void MyListener::onAppStatsUpdate(void)
{
	std::cout << "App stats updated" << std::endl;
	// Provide an implementation for the onAppStatsUpdate function here
}

void MyListener::onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
{
	std::cout << "Lobby stats updated" << std::endl;
	// Provide an implementation for the onLobbyStatsUpdate function here
}

void MyListener::onCacheSliceChanged(int cacheSliceIndex)
{
	std::cout << "Cache slice changed" << std::endl;
	// Provide an implementation for the onCacheSliceChanged function here
}

void MyListener::onAchievementUnlocked(int achievementId)
{
	std::cout << "Achievement unlocked" << std::endl;
	// Provide an implementation for the onAchievementUnlocked function here
}

bool MyListener::isConnected()
{
	return mIsConnected;
}

bool MyListener::isRoomJoinedOrCreated()
{
	return roomJoinedOrCreated;
}

int MyListener::getNbPlayers()
{
	return nbPlayers;
}

SampleNetworkLogic::SampleNetworkLogic(const ExitGames::Common::JString& appID, const ExitGames::Common::JString& appVersion)
	: mLoadBalancingClient(mListener, appID, appVersion)
{
	std::cout << "SampleNetworkLogic" << std::endl;
}

void SampleNetworkLogic::connect(void)
{
	// connect() is asynchronous - the actual result arrives in the Listener::connectReturn() or the Listener::connectionErrorReturn() callback
	if(!mLoadBalancingClient.connect()) {
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"Could not connect.");
	}
}

void SampleNetworkLogic::run(void)
{
	mLoadBalancingClient.service(); // needs to be called regularly!
}

void SampleNetworkLogic::disconnect(void)
{
	mLoadBalancingClient.disconnect(); // disconnect() is asynchronous - the actual result arrives in the Listener::disconnectReturn() callback
}

void SampleNetworkLogic::createRoom(const ExitGames::Common::JString& roomName, nByte maxPlayers)
{
	ExitGames::LoadBalancing::RoomOptions roomOptions;
	roomOptions.setMaxPlayers(maxPlayers);
	mLoadBalancingClient.opCreateRoom(roomName, roomOptions);
}

void SampleNetworkLogic::joinRoom(const ExitGames::Common::JString& roomName)
{
	mLoadBalancingClient.opJoinRoom(roomName);
}

bool SampleNetworkLogic::isConnected() {
	return mListener.isConnected();
}

bool SampleNetworkLogic::isRoomJoinedOrCreated() {
	return mListener.isRoomJoinedOrCreated();
}

void SampleNetworkLogic::sendEvent(const ExitGames::Common::Object& eventData, bool reliable, int eventCode)
{
	mLoadBalancingClient.opRaiseEvent(true, eventData, eventCode);
}

int SampleNetworkLogic::getNbPlayers() {
	return mListener.getNbPlayers();
}

// int main(int argc, char** argv) {
// 	if (argc < 2) {
// 		std::cout << "Usage: " << argv[0] << " <mode>" << std::endl;
// 		std::cout << "mode: Server or Client" << std::endl;
// 		return 1;
// 	}

// 	static const ExitGames::Common::JString appID = L"0baa921c-75d0-4172-8f0c-1e8ddffeedf8"; // set your app id here
// 	static const ExitGames::Common::JString appVersion = L"1.0";

// 	SampleNetworkLogic networkLogic(appID, appVersion);

// 	networkLogic.connect();
// 	bool shouldExit = false;
// 	bool shouldCreateRoom = true;

// 	std::cout << "waiting for connection..." << std::endl;
// 	while (!networkLogic.isConnected()) {
// 		networkLogic.run();
// 	}
// 	std::cout << "connected!" << std::endl;
// 	std::string mode(argv[1]);
// 	bool		modeServer = mode.compare("Server") == 0;
// 	bool		modeClient = mode.compare("Client") == 0;
// 	if (modeServer) {
// 		std::cout << "creating room..." << std::endl;
// 		networkLogic.createRoom(L"test", 4);
// 	} else if (modeClient) {
// 		std::cout << "joining room..." << std::endl;
// 		networkLogic.joinRoom(L"test");
// 	} else {
// 		std::cout << "invalid mode" << std::endl;
// 		return 1;
// 	}
// 	while (!networkLogic.isRoomJoinedOrCreated()) {
// 		networkLogic.run();
// 	}
// 	std::cout << "room joined or created!" << std::endl;
// 	while (networkLogic.getNbPlayers() < 2) {
// 		networkLogic.run();
// 	}
// 	if (modeServer) {
// 		std::cout << "sending event..." << std::endl;
// 		std::string data = "Hello World!";
// 		networkLogic.sendEvent(ExitGames::Common::ValueObject<ExitGames::Common::JString>(data.c_str()));
// 	}
// 	// networkLogic.joinRoom(L"test");
// 	while(!shouldExit)
// 	{
// 		networkLogic.run();
// 		if (shouldCreateRoom)
// 		{
// 			shouldCreateRoom = false;
// 			// networkLogic.createRoom(L"test", 4);
// 		}
// 	}
// 	networkLogic.disconnect();
// }

