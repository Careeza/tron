#pragma once

#define EGDisconnectCause_NONE                                   ( 0) ///<No error was tracked.
#define EGDisconnectCause_DISCONNECT_BY_SERVER_USER_LIMIT        ( 1) ///<OnStatusChanged: The CCUs count of your Photon Server License is exausted (temporarily).
#define EGDisconnectCause_EXCEPTION_ON_CONNECT                   ( 2) ///<OnStatusChanged: The server is not available or the address is wrong. Make sure the port is provided and the server is up.
#define EGDisconnectCause_DISCONNECT_BY_SERVER                   ( 3) ///<OnStatusChanged: The server disconnected this client. Most likely the server's send buffer is full (receiving too much from other clients).
#define EGDisconnectCause_DISCONNECT_BY_SERVER_LOGIC             ( 4) ///<OnStatusChanged: The server disconnected this client due to server's logic (received a disconnect command).
#define EGDisconnectCause_TIMEOUT_DISCONNECT                     ( 5) ///<OnStatusChanged: This client detected that the server's responses are not received in due time. Maybe you send / receive too much?
#define EGDisconnectCause_EXCEPTION                              ( 6) ///<OnStatusChanged: Some internal exception caused the socket code to fail. Contact Exit Games.
#define EGDisconnectCause_INVALID_AUTHENTICATION                 ( 7) ///<OnOperationResponse: Authenticate in the Photon Cloud with invalid AppId. Update your subscription or contact Exit Games.
#define EGDisconnectCause_MAX_CCU_REACHED                        ( 8) ///<OnOperationResponse: Authenticate (temporarily) failed when using a Photon Cloud subscription without CCU Burst. Update your subscription.
#define EGDisconnectCause_INVALID_REGION                         ( 9) ///<OnOperationResponse: Authenticate when the app's Photon Cloud subscription is locked to some (other) region(s). Update your subscription or master server address.
#define EGDisconnectCause_OPERATION_NOT_ALLOWED_IN_CURRENT_STATE (10) ///<OnOperationResponse: Operation that's (currently) not available for this client (not authorized usually). Only tracked for op Authenticate.
#define EGDisconnectCause_CUSTOM_AUTHENTICATION_FAILED           (11) ///<OnOperationResponse: Authenticate in the Photon Cloud with invalid client values or custom authentication setup in Cloud Dashboard.