#pragma once

#define EGClientState_Uninitialized               (0) ///<Peer is created but not used yet.
#define EGClientState_ConnectingToNameServer      (1) ///<Connecting to Name Server (includes connect authenticate and joining the lobby)
#define EGClientState_ConnectedToNameServer       (2) ///<Connected to Name Server.
#define EGClientState_Authenticating              (3) ///<Authenticating.
#define EGClientState_Authenticated               (4) ///<Authenticated.
#define EGClientState_DisconnectingFromNameServer (5) ///<Transition from Name to Chat Server.
#define EGClientState_ConnectingToFrontEnd        (6) ///<Transition to Chat Server.
#define EGClientState_ConnectedToFrontEnd         (7) ///<Connected to Chat Server. Subscribe to channels and chat here.
#define EGClientState_Disconnecting               (8) ///<The client disconnects (from any server).
#define EGClientState_Disconnected                (9) ///<The client is no longer connected (to any server). Connect to Name Server to go on.