#pragma once

#define EGPeerState_DISCONNECTED             (0) ///<The peer is disconnected and can't call Operations. Call PhotonPeer_connect().
#define EGPeerState_CONNECTING               (1) ///<The peer is establishing the connection: opening a socket, exchanging packages with Photon.
#define EGPeerState_INITIALIZING_APPLICATION (2) ///<The connection is established and now sends the application name to Photon. You set the "application name" by calling PhotonPeer_connect().
#define EGPeerState_CONNECTED                (3) ///<The peer is connected and initialized (selected an application). You can now use operations.
#define EGPeerState_DISCONNECTING            (4) ///<The peer is disconnecting. It sent a disconnect to the server, which will acknowledge closing the connection.