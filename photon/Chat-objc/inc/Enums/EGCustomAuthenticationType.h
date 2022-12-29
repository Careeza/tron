#pragma once

#define EGCustomAuthenticationType_CUSTOM   ((nByte)0) ///<Use a custom authentification service. Currently the only implemented option.
#define EGCustomAuthenticationType_STEAM    ((nByte)1) ///<Authenticates users by their Steam Account. Set auth values accordingly!
#define EGCustomAuthenticationType_FACEBOOK ((nByte)2) ///<Authenticates users by their Facebook Account. Set auth values accordingly!
#define EGCustomAuthenticationType_NONE     ((nByte)UCHAR_MAX) ///<Disables custom authentification.