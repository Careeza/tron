#include "networkLogic.h"

static const EG_CHAR* appID = L"0baa921c-75d0-4172-8f0c-1e8ddffeedf8"; // set your app id here
static const EG_CHAR* appVersion = L"1.0";

static const int sendInterval = 1000;
static const nByte regionSelectionMode = ExitGames::LoadBalancing::RegionSelectionMode::SELECT;

static const EG_CHAR* PLAYER_NAME = L"OS X";

ExitGames::Common::JString& NetworkLogicListener::toString(ExitGames::Common::JString& retStr, bool /*withTypes*/) const {
	return retStr;
}

State StateAccessor::getState(void) const {
	return mState;
}

void StateAccessor::setState(State newState) {
	mState = newState;
	for(unsigned int i=0; i<mStateUpdateListeners.getSize(); i++)
		mStateUpdateListeners[i]->stateUpdate(newState);
}

void StateAccessor::registerForStateUpdates(NetworkLogicListener* listener) {
	mStateUpdateListeners.addElement(listener);
}

Input NetworkLogic::getLastInput(void) const {
	return mLastInput;
}

void NetworkLogic::setLastInput(Input newInput) {
	mLastInput = newInput;
}

State NetworkLogic::getState(void) const {
	return mStateAccessor.getState();
}

void NetworkLogic::setRoomName(const ExitGames::Common::JString& roomName) {
	mRoomName = roomName;
}

NetworkLogic::NetworkLogic(OutputListener* listener)
	: mpOutputListener(listener)
	, mLoadBalancingClient(*this, appID, appVersion, ExitGames::LoadBalancing::ClientConstructOptions().setRegionSelectionMode(regionSelectionMode))
	, mLastInput(INPUT_NON)
	, mLastSendTime(GETTIMEMS())
	, isServer(false) {
	mStateAccessor.setState(STATE_INITIALIZED);
	mLoadBalancingClient.setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS));
	mLogger.setListener(*this);
	mLogger.setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS));
	ExitGames::Common::Base::setListener(this);
	ExitGames::Common::Base::setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS));
}

void NetworkLogic::registerForStateUpdates(NetworkLogicListener* listener) {
	mStateAccessor.registerForStateUpdates(listener);
}

void NetworkLogic::connect(void) {
	mpOutputListener->writeLine(L"connecting to Photon");
	mLoadBalancingClient.connect(ExitGames::LoadBalancing::ConnectOptions().setUsername(PLAYER_NAME));
	mStateAccessor.setState(STATE_CONNECTING);
}

void NetworkLogic::disconnect(void) {
	mLoadBalancingClient.disconnect();
}

void NetworkLogic::opCreateRoom(nByte directMode) {
	mLoadBalancingClient.opCreateRoom(L"", ExitGames::LoadBalancing::RoomOptions().setMaxPlayers(4).setDirectMode(directMode));
	mStateAccessor.setState(STATE_JOINING);
	mpOutputListener->writeLine(ExitGames::Common::JString(L"creating room") + L"...");
	isServer = true;
}

void NetworkLogic::opCreateRoom(const ExitGames::Common::JString& roomID, nByte directMode) {
	mLoadBalancingClient.opCreateRoom(roomID, ExitGames::LoadBalancing::RoomOptions().setMaxPlayers(5).setDirectMode(directMode));
	mStateAccessor.setState(STATE_JOINING);
	mpOutputListener->writeLine(ExitGames::Common::JString(L"creating room") + L"...");
	isServer = true;
}

void NetworkLogic::opJoinOrCreateRoom(void) {
	ExitGames::Common::JString roomID(L"DemoLoadBalancing");
	mLoadBalancingClient.opJoinOrCreateRoom(roomID);
	mStateAccessor.setState(STATE_JOINING);
	mpOutputListener->writeLine(ExitGames::Common::JString(L"joining or creating room ") + roomID + L"...");
}

void NetworkLogic::opJoinRandomOrCreateRoom(void) {
	mLoadBalancingClient.opJoinRandomOrCreateRoom();
	mStateAccessor.setState(STATE_JOINING);
	mpOutputListener->writeLine(ExitGames::Common::JString(L"joining a random room or creating a new room") + L"...");
}

void NetworkLogic::opJoinRoom(const ExitGames::Common::JString& roomID, bool rejoin) {
	mLoadBalancingClient.opJoinRoom(roomID, rejoin);
	mStateAccessor.setState(STATE_JOINING);
	mpOutputListener->writeLine(ExitGames::Common::JString(rejoin?L"re":L"") + L"joining room " + roomID + "...");
}

void NetworkLogic::opJoinRandomRoom(void) {
	mLoadBalancingClient.opJoinRandomRoom();
	mStateAccessor.setState(STATE_JOINING);
	mpOutputListener->writeLine(ExitGames::Common::JString(L"joining random room..."));
}

void NetworkLogic::run(void) {
	State state = mStateAccessor.getState();
	ExitGames::Common::JTime t = GETTIMEMS();
	if(mLastInput == INPUT_EXIT && state != STATE_DISCONNECTING && state != STATE_DISCONNECTED) {
		disconnect();
		mStateAccessor.setState(STATE_DISCONNECTING);
		mpOutputListener->writeLine(L"terminating application");
	}
	else {
		switch(state)
		{
			case STATE_INITIALIZED:
				connect();
				break;
			case STATE_CONNECTING:
				break;
			case STATE_CONNECTED:
				switch(mLastInput)
				{
					case INPUT_CREATE_ROOM:
						std::cout << "CREATING : " << mRoomName.UTF8Representation().cstr() << std::endl;
						opCreateRoom(mRoomName, ExitGames::LoadBalancing::DirectMode::MASTER_TO_ALL);
						break;
					case INPUT_JOIN_ROOM:
						opJoinRoom(mRoomName);
						break;
					default:
						break;
				}
				break;
			case STATE_JOINING:
				break;
			case STATE_JOINED:
				if (isServer) {
					// if(mLastSendTime+sendInterval < t) { //permet d'envoyer des evenements a des temps regulier
					// 	std::cout << "SENDING EVENT" << std::endl;
					// 	mLastSendTime = t;
					// 	sendEvent();
					// }
				}
				break;
			case STATE_LEAVING:
				break;
			case STATE_LEFT:
				mStateAccessor.setState(STATE_CONNECTED);
				break;
			case STATE_DISCONNECTING:
				break;
			default:
				break;
		}
	}
	mLastInput = INPUT_NON;
	mLoadBalancingClient.service();
}

void NetworkLogic::sendEvent(void)
{

	static int64 count = 0;
	if(mLoadBalancingClient.getCurrentlyJoinedRoom().getDirectMode() == ExitGames::LoadBalancing::DirectMode::NONE) {
		mLoadBalancingClient.opRaiseEvent(false, count, 0);
		mpOutputListener->write(ExitGames::Common::JString(L"S") + count + L" ");
	}
	else {
		sendDirect(count);
	}
	++count;
}

void NetworkLogic::sendDirect(int64 count) {
	int localNr = mLoadBalancingClient.getLocalPlayer().getNumber();
	unsigned long sendAt = GETTIMEMS();

	std::string str = std::to_string(sendAt);
	std::wstring widestr = std::wstring(str.begin(), str.end());
	const wchar_t* widecstr = widestr.c_str();

	ExitGames::Common::JString data(widecstr);

	std::string test = data.UTF8Representation().cstr();

	std::cout << "sending : [" << test << "]" << std::endl;

	const int sendMode = 0;
	const bool fallbackRelay = true;
	int sent = mLoadBalancingClient.sendDirect(data, ExitGames::LoadBalancing::SendDirectOptions().setFallbackRelay(fallbackRelay));

	// mpOutputListener->write(L"Sd" + str + L"->ALL(" + sent + ")\n");
}

void NetworkLogic::sendDirect(std::string str) {
	ExitGames::Common::JString data(str.c_str());
	const bool fallbackRelay = true;
	int sent = mLoadBalancingClient.sendDirect(data, ExitGames::LoadBalancing::SendDirectOptions().setFallbackRelay(fallbackRelay));
}

void NetworkLogic::sendDirect(std::string str, int player) {
	ExitGames::Common::JString data(str.c_str());
	ExitGames::Common::JArray<int> players;

	players.addElement(player);
	const bool fallbackRelay = true;
	int sent = mLoadBalancingClient.sendDirect(data, ExitGames::LoadBalancing::SendDirectOptions().setFallbackRelay(fallbackRelay).setTargetPlayers(players));
}

std::vector<std::string>	NetworkLogic::getUpdate() {
	std::vector<std::string> copy(updateInfo);
	updateInfo.clear();
	update = false;
	return copy;
}

void NetworkLogic::debugReturn(int debugLevel, const ExitGames::Common::JString& string) {
	mpOutputListener->debugReturn(debugLevel, string);
}

void NetworkLogic::connectionErrorReturn(int errorCode) {
	EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"code: %d", errorCode);
	mpOutputListener->writeLine(ExitGames::Common::JString(L"received connection error ") + errorCode);
	mStateAccessor.setState(STATE_DISCONNECTED);
}

void NetworkLogic::clientErrorReturn(int errorCode) {
	EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"code: %d", errorCode);
	mpOutputListener->writeLine(ExitGames::Common::JString(L"received error ") + errorCode + L" from client");
}

void NetworkLogic::warningReturn(int warningCode) {
	EGLOG(ExitGames::Common::DebugLevel::WARNINGS, L"code: %d", warningCode);
	mpOutputListener->writeLine(ExitGames::Common::JString(L"received warning ") + warningCode + L" from client");
}

void NetworkLogic::serverErrorReturn(int errorCode) {
	EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"code: %d", errorCode);
	mpOutputListener->writeLine(ExitGames::Common::JString(L"received error ") + errorCode + " from server");
}

void NetworkLogic::joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& /*playernrs*/, const ExitGames::LoadBalancing::Player& player) {
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"%ls joined the game", player.getName().cstr());
	nbPlayer = playerNr - 1;
	if (isServer and nbPlayer > 0) {
		update = true;
		updateInfo.push_back("J" + std::to_string(playerNr));
	}
	mpOutputListener->writeLine(L"");
	mpOutputListener->writeLine(ExitGames::Common::JString(L"player ") + playerNr + L" " + player.getName() + L" has joined the game");
}

void NetworkLogic::leaveRoomEventAction(int playerNr, bool isInactive) {
	
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	mpOutputListener->writeLine(L"");
	mpOutputListener->writeLine(ExitGames::Common::JString(L"player ") + playerNr + L" has left the game");
}

void NetworkLogic::customEventAction(int playerNr, nByte /*eventCode*/, const ExitGames::Common::Object& eventContent) {
	// you do not receive your own events, unless you specify yourself as one of the receivers explicitly, so you must start 2 clients, to receive the events, which you have sent, as sendEvent() uses the default receivers of opRaiseEvent() (all players in same room like the sender, except the sender itself)
	EGLOG(ExitGames::Common::DebugLevel::ALL, L"");
	mpOutputListener->write(ExitGames::Common::JString(L"R") + ExitGames::Common::ValueObject<long long>(eventContent).getDataCopy() + "<-p" + playerNr + L" ");
}

void NetworkLogic::onDirectMessage(const ExitGames::Common::Object& msg, int remoteID, bool relay) {
	ExitGames::Common::JString data = ExitGames::Common::ValueObject<ExitGames::Common::JString>(msg).getDataCopy();
	std::string str = data.UTF8Representation().cstr();
	if (str[0] == '"') {
		str = str.substr(1, str.length() - 2);
	}
	updateInfo.push_back(str);
	if (isServer) {
		std::cout << "server received : [" << str << "]" << std::endl;
	}
	std::cout << "received : [" << str << "]" << std::endl;
	update = true;
}

void NetworkLogic::connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& region, const ExitGames::Common::JString& cluster) {
	if (errorCode) {
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"error code: %d   error message: %ls", errorCode, errorString.cstr());
		mStateAccessor.setState(STATE_DISCONNECTING);
		return;
	}
	// EGLOG(ExitGames::Common::DebugLevel::INFO, L"connected to cluster " + cluster + L" of region " + region + L", user id = " + mLoadBalancingClient.getUserID());
	// mpOutputListener->writeLine(L"connected to cluster " + cluster + L" of region " + region + L", user id = " + mLoadBalancingClient.getUserID());
	mUserID = mLoadBalancingClient.getUserID();
	mStateAccessor.setState(STATE_CONNECTED);
}

void NetworkLogic::disconnectReturn(void)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	mpOutputListener->writeLine(L"disconnected");
	mStateAccessor.setState(STATE_DISCONNECTED);
}

void NetworkLogic::createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString) {
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	if(errorCode) {
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
		mpOutputListener->writeLine(L"opCreateRoom() failed: " + errorString);
		mStateAccessor.setState(STATE_CONNECTED);
		return;
	}
	mLastJoinedRoom = mLoadBalancingClient.getCurrentlyJoinedRoom().getName();

	EGLOG(ExitGames::Common::DebugLevel::INFO, L"localPlayerNr: %d", localPlayerNr);
	mpOutputListener->writeLine(L"... room " + mLoadBalancingClient.getCurrentlyJoinedRoom().getName() + " has been created");
	mpOutputListener->writeLine(L"regularly sending dummy events now");
	mStateAccessor.setState(STATE_JOINED);
}

void NetworkLogic::joinOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString) {
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	if (errorCode) {
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
		mpOutputListener->writeLine(L"opJoinOrCreateRoom() failed: " + errorString);
		mStateAccessor.setState(STATE_CONNECTED);
		return;
	}
	mLastJoinedRoom = mLoadBalancingClient.getCurrentlyJoinedRoom().getName();

	EGLOG(ExitGames::Common::DebugLevel::INFO, L"localPlayerNr: %d", localPlayerNr);
	mpOutputListener->writeLine(L"... room " + mLoadBalancingClient.getCurrentlyJoinedRoom().getName() + " has been entered");
	mpOutputListener->writeLine(L"regularly sending dummy events now");
	mStateAccessor.setState(STATE_JOINED);
}

void NetworkLogic::joinRandomOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString) {
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	if (errorCode) {
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
		mpOutputListener->writeLine(L"opJoinRandomOrCreateRoom() failed: " + errorString);
		mStateAccessor.setState(STATE_CONNECTED);
		return;
	}
	mLastJoinedRoom = mLoadBalancingClient.getCurrentlyJoinedRoom().getName();

	EGLOG(ExitGames::Common::DebugLevel::INFO, L"localPlayerNr: %d", localPlayerNr);
	mpOutputListener->writeLine(L"... room " + mLoadBalancingClient.getCurrentlyJoinedRoom().getName() + " has been entered");
	mpOutputListener->writeLine(L"regularly sending dummy events now");
	mStateAccessor.setState(STATE_JOINED);
}

void NetworkLogic::joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString) {
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	if (errorCode) {
		mLastJoinedRoom = L"";
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
		mpOutputListener->writeLine(L"opJoinRoom() failed: " + errorString);
		mStateAccessor.setState(STATE_CONNECTED);
		return;
	}
	currentPlayer = localPlayerNr - 1;
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"localPlayerNr: %d", localPlayerNr);
	mpOutputListener->writeLine(L"... room " + mLoadBalancingClient.getCurrentlyJoinedRoom().getName() + " has been joined");
	mpOutputListener->writeLine(L"regularly sending dummy events now");
	mStateAccessor.setState(STATE_JOINED);
}

void NetworkLogic::joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString) {
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	if(errorCode) {
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
		mpOutputListener->writeLine(L"opJoinRandomRoom() failed: " + errorString);
		mStateAccessor.setState(STATE_CONNECTED);
		return;
	}

	mLastJoinedRoom = mLoadBalancingClient.getCurrentlyJoinedRoom().getName();

	EGLOG(ExitGames::Common::DebugLevel::INFO, L"localPlayerNr: %d", localPlayerNr);
	mpOutputListener->writeLine(L"... room " + mLoadBalancingClient.getCurrentlyJoinedRoom().getName() + " has been joined");
	mpOutputListener->writeLine(L"regularly sending dummy events now");
	mStateAccessor.setState(STATE_JOINED);
}

void NetworkLogic::leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString) {
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	if(errorCode) {
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
		mpOutputListener->writeLine(L"opLeaveRoom() failed: " + errorString);
		mStateAccessor.setState(STATE_DISCONNECTING);
		return;
	}
	mStateAccessor.setState(STATE_LEFT);
	mpOutputListener->writeLine(L"room has been successfully left");
}

void NetworkLogic::joinLobbyReturn(void) {
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	mpOutputListener->writeLine(L"joined lobby");
}

void NetworkLogic::leaveLobbyReturn(void) {
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	mpOutputListener->writeLine(L"left lobby");
}

void NetworkLogic::onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats) {
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"%ls", lobbyStats.toString().cstr());
	mpOutputListener->writeLine(L"LobbyStats: " + lobbyStats.toString());
}

void NetworkLogic::onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats) {
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"%ls", lobbyStats.toString().cstr());
	mpOutputListener->writeLine(L"LobbyStats: " + lobbyStats.toString());
}

void NetworkLogic::onAvailableRegions(const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegions, const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegionServers) {
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"%ls / %ls", availableRegions.toString().cstr(), availableRegionServers.toString().cstr());
	mpOutputListener->writeLine(L"onAvailableRegions: " + availableRegions.toString() + L" / " + availableRegionServers.toString());
	int idx = availableRegions.getIndexOf(L"eu");
	ExitGames::Common::JString selectedRegion = availableRegions[idx>-1?idx:0];
	mpOutputListener->writeLine(L"selecting region: " + (selectedRegion));
	mLoadBalancingClient.selectRegion(selectedRegion);
}