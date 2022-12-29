#include "LoadBalancing-cpp/inc/Client.h"
#include "LoadBalancing-cpp/inc/Listener.h"
#include "Common-cpp/inc/Logger.h"
#include "Photon-cpp/inc/PhotonPeer.h"
// #include <CoreFoundation/CFHTTPMessage.h>

#include "LoadBalancing-cpp/inc/Listener.h"

class MyListener : public ExitGames::LoadBalancing::Listener
{
public:
    virtual void debugReturn(int debugLevel, const ExitGames::Common::JString& string)
    {
        // Provide an implementation for the debugReturn function here
    }

    virtual void connectionErrorReturn(int errorCode)
    {
        // Provide an implementation for the connectionErrorReturn function here
    }

    virtual void clientErrorReturn(int errorCode)
    {
        // Provide an implementation for the clientErrorReturn function here
    }

    virtual void warningReturn(int warningCode)
    {
        // Provide an implementation for the warningReturn function here
    }

    virtual void serverErrorReturn(int errorCode)
    {
        // Provide an implementation for the serverErrorReturn function here
    }

    virtual void joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player)
    {
        // Provide an implementation for the joinRoomEventAction function here
    }

    virtual void leaveRoomEventAction(int playerNr, bool isInactive)
    {
        // Provide an implementation for the leaveRoomEventAction function here
    }

    virtual void customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent)
    {
        // Provide an implementation for the customEventAction function here
    }

    virtual void connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& region, const ExitGames::Common::JString& cluster)
    {
        // Provide an implementation for the connectReturn function here
    }

    virtual void disconnectReturn(void)
    {
        // Provide an implementation for the disconnectReturn function here
    }

    virtual void createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& roomProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
    {
        // Provide an implementation for the createRoomReturn function here
    }
    virtual void joinOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& roomProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
    {
        // Provide an implementation for the joinOrCreateRoomReturn function here
    }

    virtual void joinRandomOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& roomProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
    {
        // Provide an implementation for the joinRandomOrCreateRoomReturn function here
    }

    virtual void joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& roomProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
    {
        // Provide an implementation for the joinRoomReturn function here
    }

    virtual void joinRandomRoomReturn(int /*localPlayerNr*/, const ExitGames::Common::Hashtable& /*roomProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int /*errorCode*/, const ExitGames::Common::JString& /*errorString*/) {

    }
    virtual void leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString)
    {
        // Provide an implementation for the leaveRoomReturn function here
    }

    virtual void joinLobbyReturn(void)
    {
        // Provide an implementation for the joinLobbyReturn function here
    }

    virtual void leaveLobbyReturn(void)
    {
        // Provide an implementation for the leaveLobbyReturn function here
    }

    virtual void onFindFriendsResponse(void)
    {
        // Provide an implementation for the onFindFriendsResponse function here
    }

    virtual void onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
    {
        // Provide an implementation for the onLobbyStatsResponse function here
    }

    virtual void webRpcReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& uriPath, int resultCode, const ExitGames::Common::Dictionary<ExitGames::Common::Object, ExitGames::Common::Object>& returnData)
    {
        // Provide an implementation for the webRpcReturn function here
    }

    virtual void onRoomListUpdate(void)
    {
        // Provide an implementation for the onRoomListUpdate function here
    }

    virtual void onRoomPropertiesChange(const ExitGames::Common::Hashtable& changes)
    {
        // Provide an implementation for the onRoomPropertiesChange function here
    }

    virtual void onPlayerPropertiesChange(int playerNr, const ExitGames::Common::Hashtable& changes)
    {
        // Provide an implementation for the onPlayerPropertiesChange function here
    }

    virtual void onAppStatsUpdate(void)
    {
        // Provide an implementation for the onAppStatsUpdate function here
    }

    virtual void onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
    {
        // Provide an implementation for the onLobbyStatsUpdate function here
    }

    virtual void onCacheSliceChanged(int cacheSliceIndex)
    {
        // Provide an implementation for the onCacheSliceChanged function here
    }

    virtual void onAchievementUnlocked(int achievementId)
    {
        // Provide an implementation for the onAchievementUnlocked function here
    }
};



class SampleNetworkLogic
{
public:
    SampleNetworkLogic(const ExitGames::Common::JString& appID, const ExitGames::Common::JString& appVersion);
    void connect(void);
    // void disconnect(void);
    // void run(void);
private:
    ExitGames::LoadBalancing::Client mLoadBalancingClient;
    MyListener mListener; // your implementation of the ExitGames::LoadBalancing::Listener interface
    ExitGames::Common::Logger mLogger; // accessed by EGLOG()
};

SampleNetworkLogic::SampleNetworkLogic(const ExitGames::Common::JString& appID, const ExitGames::Common::JString& appVersion)
    : mLoadBalancingClient(mListener, appID, appVersion)
{
}

void SampleNetworkLogic::connect(void)
{
    // connect() is asynchronous - the actual result arrives in the Listener::connectReturn() or the Listener::connectionErrorReturn() callback
    if(!mLoadBalancingClient.connect())
        EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"Could not connect.");
}

int main(void)
{
    static const ExitGames::Common::JString appID = L"<no-app-id>"; // set your app id here
    static const ExitGames::Common::JString appVersion = L"1.0";

    SampleNetworkLogic networkLogic(appID, appVersion);

    networkLogic.connect();
    return 0;
}
