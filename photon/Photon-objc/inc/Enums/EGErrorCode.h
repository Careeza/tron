#pragma once

#define EGErrorCode_SUCCESS       (    0) ///<No error
#define EGErrorCode_EFAILED       (    1) ///<General failure
#define EGErrorCode_ENOMEMORY     (    2) ///<Out of memory
#define EGErrorCode_EBADCLASS     (   10) ///<NULL class object
#define EGErrorCode_EBADPARM      (   14) ///<Invalid parameter
#define EGErrorCode_EITEMBUSY     (   32) ///<Context (system, interface, etc.) is busy
#define EGErrorCode_NET_SUCCESS   (    0) ///<No network error, successful operation
#define EGErrorCode_NET_ERROR     (   -1) ///<Unsuccessful operation
#define EGErrorCode_NET_ENETNONET (0x216) ///<Network subsystem unavailable
#define EGErrorCode_NET_MSGSIZE   (0x21B) ///<Message too long. A message sent on a datagram socket was larger than the internal message buffer or some other network limit, or the buffer used to receive a datagram was smaller than the datagram itself.
#define EGErrorCode_NET_ENOTCONN  (0x21C)