#ifndef ONLINE_HPP

# define ONLINE_HPP

# include <string>
# include <vector>

enum UpdateType {
	UPDATE_READY,
	UPDATE_START,
	UPDATE_DIRECTION,
	UPDATE_NONE,
};

struct	gameOnlineInfo {
	gameOnlineInfo() : nbPlayers(0), currentPlayer(0), ready(false), updateServer(false), updateClient(false), playerReady({false, false, false, false}) {};
	int			nbPlayers;
	int			currentPlayer;
	bool		ready;
	bool		updateServer;
	bool		updateClient;
	UpdateType	updateType;
	std::vector<bool>		playerReady;
	DIRECTION				direction;
};

void	createClient(std::vector<int> roomNumber, gameOnlineInfo *info);
void	createServer(std::vector<int> roomNumber);


#endif