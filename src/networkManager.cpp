#include "networkThread.hpp"

// void		createListenerThread(NetworkManagerInfo *info) {
// 	std::thread	listenerThread(&NetworkManagerInfo::listenerThread, info);
// 	listenerThread.detach();
// }

NetworkThread::NetworkThread(SampleNetworkLogic &networkLogic_) : update(false), networkLogic(networkLogic_) {}

NetworkThread::~NetworkThread() {}

void	NetworkThread::listenerThread() {
	while (true) {
		networkLogic.run();
		if (networkLogic.getNbPlayers() != nbPLayer) {
			nbPLayer = networkLogic.getNbPlayers();
			update = true;
		}
		if (networkLogic.isConnected() != connected) {
			connected = networkLogic.isConnected();
			update = true;
		}
		if (networkLogic.isRoomJoinedOrCreated() != joinOrCreate) {
			joinOrCreate = networkLogic.isRoomJoinedOrCreated();
			update = true;
		}
	}
}

bool	NetworkThread::needUpdate() {
	return (update);
}

std::vector<int>	NetworkThread::getDirections() {
	mutex.lock();
	std::vector<int>	cDirections = this->directions;
	update = false;
	mutex.unlock();
	return (cDirections);
}

int	NetworkThread::getNbPlayer() {
	return (nbPLayer);
}

bool	NetworkThread::isConnected() {
	return (connected);
}

bool	NetworkThread::isJoinOrCreate() {
	return (joinOrCreate);
}

void	createListenerThread(NetworkThread &info) {
	std::thread	listenerThread(&NetworkThread::listenerThread, &info);
	listenerThread.detach();
}