//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#ifndef GAME_H
#define GAME_H

#include "network.h"
#include "structures.h"

#ifdef _WIN32
#define DLLEXPORT extern "C" __declspec(dllexport)

#ifdef ENABLE_THREADS
#include "pthread.h"
#endif

#else
#define DLLEXPORT

#ifdef ENABLE_THREADS
#include <pthread.h>
#endif

#endif

struct Connection
{
  int socket;
  
  #ifdef ENABLE_THREADS
  pthread_mutex_t mutex;
  #endif
  
  int mapWidth;
  int mapHeight;
  int turnNumber;
  int maxDroids;
  int playerID;
  int gameNumber;
  int scrapRate;
  int maxScrap;
  int dropTime;

  _Player* Players;
  int PlayerCount;
  _Mappable* Mappables;
  int MappableCount;
  _Droid* Droids;
  int DroidCount;
  _Tile* Tiles;
  int TileCount;
  _ModelVariant* ModelVariants;
  int ModelVariantCount;
};

#ifdef __cplusplus
extern "C"
{
#endif
  DLLEXPORT Connection* createConnection();
  DLLEXPORT void destroyConnection(Connection* c);
  DLLEXPORT int serverConnect(Connection* c, const char* host, const char* port);

  DLLEXPORT int serverLogin(Connection* c, const char* username, const char* password);
  DLLEXPORT int createGame(Connection* c);
  DLLEXPORT int joinGame(Connection* c, int id, const char* playerType);

  DLLEXPORT void endTurn(Connection* c);
  DLLEXPORT void getStatus(Connection* c);


//commands

  ///Allows a player to display messages on the screen
  DLLEXPORT int playerTalk(_Player* object, char* message);
  ///Allows a player to spawn a Droid.
  DLLEXPORT int playerOrbitalDrop(_Player* object, int x, int y, int variant);
  ///Make the Droid move to the respective x and y location.
  DLLEXPORT int droidMove(_Droid* object, int x, int y);
  ///Command to operate (repair, attack, hack) on another Droid.
  DLLEXPORT int droidOperate(_Droid* object, int x, int y);

//derived properties



//accessors

DLLEXPORT int getMapWidth(Connection* c);
DLLEXPORT int getMapHeight(Connection* c);
DLLEXPORT int getTurnNumber(Connection* c);
DLLEXPORT int getMaxDroids(Connection* c);
DLLEXPORT int getPlayerID(Connection* c);
DLLEXPORT int getGameNumber(Connection* c);
DLLEXPORT int getScrapRate(Connection* c);
DLLEXPORT int getMaxScrap(Connection* c);
DLLEXPORT int getDropTime(Connection* c);

DLLEXPORT _Player* getPlayer(Connection* c, int num);
DLLEXPORT int getPlayerCount(Connection* c);

DLLEXPORT _Mappable* getMappable(Connection* c, int num);
DLLEXPORT int getMappableCount(Connection* c);

DLLEXPORT _Droid* getDroid(Connection* c, int num);
DLLEXPORT int getDroidCount(Connection* c);

DLLEXPORT _Tile* getTile(Connection* c, int num);
DLLEXPORT int getTileCount(Connection* c);

DLLEXPORT _ModelVariant* getModelVariant(Connection* c, int num);
DLLEXPORT int getModelVariantCount(Connection* c);



  DLLEXPORT int networkLoop(Connection* c);
#ifdef __cplusplus
}
#endif

#endif
