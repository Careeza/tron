#pragma once

// server - Photon: <= 0
#define EGErrorCode_OPERATION_DENIED                    (   -3)
#define EGErrorCode_OPERATION_INVALID                   (   -2)
#define EGErrorCode_INTERNAL_SERVER_ERROR               (   -1)
#define EGErrorCode_OK                                  (    0)

// server - LoadBalancing: from SHRT_MAX downwards
#define EGErrorCode_INVALID_AUTHENTICATION              (32767)
#define EGErrorCode_GAME_ID_ALREADY_EXISTS              (32766)
#define EGErrorCode_GAME_FULL                           (32765)
#define EGErrorCode_GAME_CLOSED                         (32764)
#define EGErrorCode_ALREADY_MATCHED                     (32763)
#define EGErrorCode_SERVER_FULL                         (32762)
#define EGErrorCode_USER_BLOCKED                        (32761)
#define EGErrorCode_NO_MATCH_FOUND                      (32760)
#define EGErrorCode_GAME_DOES_NOT_EXIST                 (32758)
#define EGErrorCode_MAX_CCU_REACHED                     (32757)
#define EGErrorCode_INVALID_REGION                      (32756)
#define EGErrorCode_CUSTOM_AUTHENTICATION_FAILED        (32755)
#define EGErrorCode_AUTHENTICATION_TOKEN_EXPIRED        (32753)
#define EGErrorCode_PLUGIN_REPORTED_ERROR               (32752)
#define EGErrorCode_PLUGIN_MISMATCH                     (32751)
#define EGErrorCode_JOIN_FAILED_PEER_ALREADY_JOINED     (32750)
#define EGErrorCode_JOIN_FAILED_FOUND_INACTIVE_JOINER   (32749)
#define EGErrorCode_JOIN_FAILED_WITH_REJOINER_NOT_FOUND (32748)
#define EGErrorCode_JOIN_FAILED_FOUND_EXCLUDED_USER_ID  (32747)
#define EGErrorCode_JOIN_FAILED_FOUND_ACTIVE_JOINER     (32746)
#define EGErrorCode_HTTP_LIMIT_REACHED                  (32745)
#define EGErrorCode_EXTERNAL_HTTP_CALL_FAILED           (32744)

// client Photon: 1001-2000 (see Photon-objc EGStatusCode.h)

// client LoadBalancing: > 2000
// currently none