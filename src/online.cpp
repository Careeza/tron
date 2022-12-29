#include "LoadBalancing-cpp/inc/Client.h"
#include "LoadBalancing-cpp/inc/Listener.h"
#include <unistd.h>
// #include "game.hpp"

class MyListener : public ExitGames::LoadBalancing::Listener
{
	public:
		MyListener() : ExitGames::LoadBalancing::Listener(), mIsConnected(false), roomJoinedOrCreated(false) {}
		virtual void debugReturn(int debugLevel, const ExitGames::Common::JString& string)
		{
			std::cout << "debugReturn: " << string << std::endl;
			// Provide an implementation for the debugReturn function here
		}

		virtual void connectionErrorReturn(int errorCode)
		{
			std::cerr << "Error in connection: " << errorCode << std::endl;
			// Provide an implementation for the connectionErrorReturn function here
		}

		virtual void clientErrorReturn(int errorCode)
		{
			std::cerr << "Error in client: " << errorCode << std::endl;
			// Provide an implementation for the clientErrorReturn function here
		}

		virtual void warningReturn(int warningCode)
		{
			std::cerr << "Warning: " << warningCode << std::endl;
			// Provide an implementation for the warningReturn function here
		}

		virtual void serverErrorReturn(int errorCode)
		{
			std::cerr << "Error in server: " << errorCode << std::endl;
			// Provide an implementation for the serverErrorReturn function here
		}

		virtual void joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player)
		{
			roomJoinedOrCreated = true;
			std::cout << "Player " << playerNr << " joined the room" << std::endl;
			// Provide an implementation for the joinRoomEventAction function here
		}

		virtual void leaveRoomEventAction(int playerNr, bool isInactive)
		{
			std::cout << "Player " << playerNr << " left the room" << std::endl;
			// Provide an implementation for the leaveRoomEventAction function here
		}

		virtual void customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent)
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

		virtual void connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& region, const ExitGames::Common::JString& cluster)
		{
			mIsConnected = true;
			std::cout << "Connected to " << region << std::endl;
			// Provide an implementation for the connectReturn function here
		}

		virtual void disconnectReturn(void)
		{
			std::cout << "Disconnected" << std::endl;
			// Provide an implementation for the disconnectReturn function here
		}

		virtual void createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& roomProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
		{
			std::cout << "Room created" << std::endl;
			// Provide an implementation for the createRoomReturn function here
		}
		virtual void joinOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& roomProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
		{
			std::cout << "Room joined or created" << std::endl;
			// Provide an implementation for the joinOrCreateRoomReturn function here
		}

		virtual void joinRandomOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& roomProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
		{
			std::cout << "Room joined or created" << std::endl;
			// Provide an implementation for the joinRandomOrCreateRoomReturn function here
		}

		virtual void joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& roomProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
		{
			std::cout << "Room joined" << std::endl;
			// Provide an implementation for the joinRoomReturn function here
		}

		virtual void joinRandomRoomReturn(int /*localPlayerNr*/, const ExitGames::Common::Hashtable& /*roomProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int /*errorCode*/, const ExitGames::Common::JString& /*errorString*/) {
			std::cout << "Room joined" << std::endl;
		}
		virtual void leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString)
		{
			std::cout << "Room left" << std::endl;
			// Provide an implementation for the leaveRoomReturn function here
		}

		virtual void joinLobbyReturn(void)
		{
			std::cout << "Joined lobby" << std::endl;
			// Provide an implementation for the joinLobbyReturn function here
		}

		virtual void leaveLobbyReturn(void)
		{
			std::cout << "Left lobby" << std::endl;
			// Provide an implementation for the leaveLobbyReturn function here
		}

		virtual void onFindFriendsResponse(void)
		{
			std::cout << "Friends found" << std::endl;
			// Provide an implementation for the onFindFriendsResponse function here
		}

		virtual void onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
		{
			std::cout << "Lobby stats received" << std::endl;
			// Provide an implementation for the onLobbyStatsResponse function here
		}

		virtual void webRpcReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& uriPath, int resultCode, const ExitGames::Common::Dictionary<ExitGames::Common::Object, ExitGames::Common::Object>& returnData)
		{
			std::cout << "WebRPC returned" << std::endl;
			// Provide an implementation for the webRpcReturn function here
		}

		virtual void onRoomListUpdate(void)
		{
			std::cout << "Room list updated" << std::endl;
			// Provide an implementation for the onRoomListUpdate function here
		}

		virtual void onRoomPropertiesChange(const ExitGames::Common::Hashtable& changes)
		{
			std::cout << "Room properties changed" << std::endl;
			// Provide an implementation for the onRoomPropertiesChange function here
		}

		virtual void onPlayerPropertiesChange(int playerNr, const ExitGames::Common::Hashtable& changes)
		{
			std::cout << "Player properties changed" << std::endl;
			// Provide an implementation for the onPlayerPropertiesChange function here
		}

		virtual void onAppStatsUpdate(void)
		{
			std::cout << "App stats updated" << std::endl;
			// Provide an implementation for the onAppStatsUpdate function here
		}

		virtual void onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
		{
			std::cout << "Lobby stats updated" << std::endl;
			// Provide an implementation for the onLobbyStatsUpdate function here
		}

		virtual void onCacheSliceChanged(int cacheSliceIndex)
		{
			std::cout << "Cache slice changed" << std::endl;
			// Provide an implementation for the onCacheSliceChanged function here
		}

		virtual void onAchievementUnlocked(int achievementId)
		{
			std::cout << "Achievement unlocked" << std::endl;
			// Provide an implementation for the onAchievementUnlocked function here
		}

		bool isConnected()
		{
			return mIsConnected;
		}

		bool isRoomJoinedOrCreated()
		{
			return roomJoinedOrCreated;
		}

	private:
		bool	mIsConnected;
		bool	roomJoinedOrCreated;
};

class SampleNetworkLogic
{
	public:
		SampleNetworkLogic(const ExitGames::Common::JString& appID, const ExitGames::Common::JString& appVersion);
		void	connect(void);
		void	run(void);
		void	disconnect(void);
		void	createRoom(const ExitGames::Common::JString& roomName, nByte maxPlayers);
		void	joinRoom(const ExitGames::Common::JString& roomName);
		bool	isConnected();
		bool	isRoomJoinedOrCreated();
		void	sendEvent(const ExitGames::Common::Object& eventData, bool reliable = true, int eventCode = 1);
	private:
		ExitGames::LoadBalancing::Client mLoadBalancingClient;
		MyListener mListener; // your implementation of the ExitGames::LoadBalancing::Listener interface
		ExitGames::Common::Logger mLogger; // accessed by EGLOG()
};

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

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " <mode>" << std::endl;
		std::cout << "mode: Server or Client" << std::endl;
		return 1;
	}

	static const ExitGames::Common::JString appID = L"0baa921c-75d0-4172-8f0c-1e8ddffeedf8"; // set your app id here
	static const ExitGames::Common::JString appVersion = L"1.0";

	SampleNetworkLogic networkLogic(appID, appVersion);

	networkLogic.connect();
	bool shouldExit = false;
	bool shouldCreateRoom = true;

	std::cout << "waiting for connection..." << std::endl;
	while (!networkLogic.isConnected()) {
		networkLogic.run();
	}
	std::cout << "connected!" << std::endl;
	std::string mode(argv[1]);
	bool		modeServer = mode.compare("Server") == 0;
	bool		modeClient = mode.compare("Client") == 0;
	if (modeServer) {
		std::cout << "creating room..." << std::endl;
		networkLogic.createRoom(L"test", 4);
	} else if (modeClient) {
		std::cout << "joining room..." << std::endl;
		networkLogic.joinRoom(L"test");
	} else {
		std::cout << "invalid mode" << std::endl;
		return 1;
	}
	while (!networkLogic.isRoomJoinedOrCreated()) {
		networkLogic.run();
	}
	std::cout << "room joined or created!" << std::endl;
	if (modeServer) {
		std::string data = "Hello World!";
		networkLogic.sendEvent(ExitGames::Common::ValueObject<ExitGames::Common::JString>(data.c_str()));
	}
	// networkLogic.joinRoom(L"test");
	while(!shouldExit)
	{
		networkLogic.run();
		if (shouldCreateRoom)
		{
			shouldCreateRoom = false;
			// networkLogic.createRoom(L"test", 4);
		}
	}
	networkLogic.disconnect();
}

