#pragma once

#define EGStatusCode_EXCEPTION_ON_CONNECT              (1023) ///<the PhotonPeer encountered an exception while opening the incoming connection to the server. The server could be down / not running.
#define EGStatusCode_CONNECT                           (1024) ///<the PhotonPeer is connected.
#define EGStatusCode_DISCONNECT                        (1025) ///<the PhotonPeer just disconnected.
#define EGStatusCode_EXCEPTION                         (1026) ///<the PhotonPeer encountered an exception and will disconnect, too.
#define EGStatusCode_QUEUE_OUTGOING_RELIABLE_WARNING   (1027) ///<PhotonPeer outgoing queue is filling up. send more often.
#define EGStatusCode_QUEUE_OUTGOING_UNRELIABLE_WARNING (1029) ///<PhotonPeer outgoing queue is filling up. send more often.
#define EGStatusCode_SEND_ERROR                        (1030) ///<Sending command failed. Either not connected, or the requested channel is bigger than the number of initialized channels.
#define EGStatusCode_QUEUE_OUTGOING_ACKS_WARNING       (1031) ///<PhotonPeer outgoing queue is filling up. Send more often.
#define EGStatusCode_QUEUE_INCOMING_RELIABLE_WARNING   (1033) ///<PhotonPeer incoming reliable queue is filling up. Dispatch more often.
#define EGStatusCode_QUEUE_INCOMING_UNRELIABLE_WARNING (1035) ///<PhotonPeer incoming unreliable queue is filling up. Dispatch more often.
#define EGStatusCode_QUEUE_SENT_WARNING                (1037) ///<PhotonPeer sent queue is filling up. Check, why the server does not acknowledge your sent reliable commands.
#define EGStatusCode_INTERNAL_RECEIVE_EXCEPTION        (1039) ///<Exception, if a server cannot be connected. Most likely, the server is not responding. Ask user to try again later.
#define EGStatusCode_TIMEOUT_DISCONNECT                (1040) ///<Disconnection due to a timeout (client did no longer receive ACKs from server).
#define EGStatusCode_DISCONNECT_BY_SERVER              (1041) ///<Disconnect by server due to timeout (received a disconnect command, cause server misses ACKs of client).
#define EGStatusCode_DISCONNECT_BY_SERVER_USER_LIMIT   (1042) ///<Disconnect by server due to concurrent user limit reached (received a disconnect command).
#define EGStatusCode_DISCONNECT_BY_SERVER_LOGIC        (1043) ///<Disconnect by server due to server's logic (received a disconnect command).
#define EGStatusCode_ENCRYPTION_ESTABLISHED            (1048) ///<The encryption-setup for secure communication finished successfully.
#define EGStatusCode_ENCRYPTION_FAILED_TO_ESTABLISH    (1049) ///<The encryption-setup failed for some reason. Check debug logs.