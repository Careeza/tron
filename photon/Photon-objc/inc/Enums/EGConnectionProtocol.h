#pragma once

#define EGConnectionProtocol_UDP     ((nByte)0) ///<Use UDP to connect to Photon, which allows you to send operations reliable or unreliable on demand.
#define EGConnectionProtocol_TCP     ((nByte)1) ///<Use TCP to connect to Photon.
#define EGConnectionProtocol_DEFAULT ((nByte)UDP)