#include "Listener.h"
#include "UIListener.h"

class CPhotonLib
{
public:
	CPhotonLib(void);
	virtual ~CPhotonLib(void);

	int run(void);

	ExitGames::LoadBalancing::Client& getClient(void);

	enum States
	{
		SampleStarted = 0,
		PhotonPeerCreated,
		Connecting,
		ErrorConnecting,
		Connected,
		Joining,
		ErrorJoining,
		Joined,
		Leaving,
		ErrorLeaving,
		Left,
		Receiving,
		Disconnecting,
		Disconnected,
	};

	States getState(void) const;
	void setState(States newState);
protected:
	int createConnection(void);
	int closeConnection(void);
	short join(const char* gameId);
	short leave(void);
	void sendData(void);

	States mCurrentState;
	Listener mListener;
	ExitGames::Common::Logger mLogger;
	ExitGames::LoadBalancing::Client mClient;
};

class SampleCustomType : public ExitGames::Common::CustomType<SampleCustomType, 1>
{
	typedef ExitGames::Common::CustomType<SampleCustomType, 1> super;
public:
	using ToString::toString;

	SampleCustomType(void);
	SampleCustomType(nByte foo, nByte bar);
	SampleCustomType(const SampleCustomType& toCopy);
	~SampleCustomType(void);
	SampleCustomType& operator=(const SampleCustomType& toCopy);

	bool compare(const ExitGames::Common::CustomTypeBase& other) const;
	void duplicate(ExitGames::Common::CustomTypeBase* retVal) const;
	void deserialize(const nByte* pData, short length);
	short serialize(nByte* retVal) const;
	ExitGames::Common::JString& toString(ExitGames::Common::JString& retStr, bool withTypes=false) const;
private:
	nByte mFoo;
	nByte mBar;
};

class SampleCustomType2 : public ExitGames::Common::CustomType<SampleCustomType2, 2>
{
	typedef ExitGames::Common::CustomType<SampleCustomType2, 2> super;
public:
	using ToString::toString;

	SampleCustomType2(void);
	SampleCustomType2(const ExitGames::Common::Dictionary<ExitGames::Common::JString, SampleCustomType>& dic);
	SampleCustomType2(const SampleCustomType2& toCopy);
	~SampleCustomType2(void);
	SampleCustomType2& operator=(const SampleCustomType2& toCopy);

	bool compare(const ExitGames::Common::CustomTypeBase& other) const;
	void duplicate(ExitGames::Common::CustomTypeBase* retVal) const;
	void deserialize(const nByte* pData, short length);
	short serialize(nByte* retVal) const;
	ExitGames::Common::JString& toString(ExitGames::Common::JString& retStr, bool withTypes=false) const;
private:
	ExitGames::Common::Dictionary<ExitGames::Common::JString, SampleCustomType> mDic;

	static nByte mSerializationProtocol;
};