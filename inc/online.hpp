#ifndef ONLINE_HPP

# define ONLINE_HPP

# include "LoadBalancing-cpp/inc/Client.h"
# include "LoadBalancing-cpp/inc/Listener.h"

class MyListener : public ExitGames::LoadBalancing::Listener
{
	public:
		MyListener();
		virtual void	debugReturn(int debugLevel, const ExitGames::Common::JString& string);
		virtual void	connectionErrorReturn(int errorCode);
		virtual void	clientErrorReturn(int errorCode);
		virtual void	warningReturn(int warningCode);
		virtual void	serverErrorReturn(int errorCode);
		virtual void	joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player);
		virtual void	leaveRoomEventAction(int playerNr, bool isInactive);
		virtual void	customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent);
		virtual void	connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& region, const ExitGames::Common::JString& cluster);
		virtual void	disconnectReturn(void);
		virtual void	createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& roomProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
		virtual void	joinOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& roomProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
		virtual void	joinRandomOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& roomProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
		virtual void	joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& roomProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
		virtual void	joinRandomRoomReturn(int /*localPlayerNr*/, const ExitGames::Common::Hashtable& /*roomProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int /*errorCode*/, const ExitGames::Common::JString& /*errorString*/);
		virtual void	leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString);
		virtual void	joinLobbyReturn(void);
		virtual void	leaveLobbyReturn(void);
		virtual void	onFindFriendsResponse(void);
		virtual void	onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats);
		virtual void	webRpcReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& uriPath, int resultCode, const ExitGames::Common::Dictionary<ExitGames::Common::Object, ExitGames::Common::Object>& returnData);
		virtual void	onRoomListUpdate(void);
		virtual void	onRoomPropertiesChange(const ExitGames::Common::Hashtable& changes);
		virtual void	onPlayerPropertiesChange(int playerNr, const ExitGames::Common::Hashtable& changes);
		virtual void	onAppStatsUpdate(void);
		virtual void	onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats);
		virtual void	onCacheSliceChanged(int cacheSliceIndex);
		virtual void 	onAchievementUnlocked(int achievementId);
		bool			isConnected();
		bool 			isRoomJoinedOrCreated();
		int 			getNbPlayers();

	private:
		bool	mIsConnected;
		bool	roomJoinedOrCreated;
		int		nbPlayers;
		bool	errorInConnection;
};

class SampleNetworkLogic
{
	public:
		SampleNetworkLogic(const ExitGames::Common::JString& appID, const ExitGames::Common::JString& appVersion);
		void	connect(void);
		void	run(void);
		void	disconnect(void);
		void	createRoom(const ExitGames::Common::JString& roomName, nByte maxPlayers = 4);
		void	joinRoom(const ExitGames::Common::JString& roomName);
		bool	isConnected();
		bool	isRoomJoinedOrCreated();
		int		getNbPlayers();
		void	sendEvent(const ExitGames::Common::Object& eventData, bool reliable = true, int eventCode = 1);
	private:
		ExitGames::LoadBalancing::Client mLoadBalancingClient;
		MyListener mListener; // your implementation of the ExitGames::LoadBalancing::Listener interface
		ExitGames::Common::Logger mLogger; // accessed by EGLOG()
};


#endif