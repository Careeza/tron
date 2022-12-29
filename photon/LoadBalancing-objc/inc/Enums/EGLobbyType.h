#pragma once

#define EGLobbyType_DEFAULT   ((nByte)1) ///<This lobby is used unless another is defined by game or JoinRandom. Room-lists will be sent and JoinRandomRoom can filter by matching properties.
#define EGLobbyType_SQL_LOBBY ((nByte)2) ///<This lobby type lists rooms like Default but JoinRandom has a parameter for SQL-like "where" clauses for filtering. This allows bigger, less, or and and combinations.