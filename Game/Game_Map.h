#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "CommonFunc.h"
#include "BaseObject.h"

const int MAX_TILES = 110;
const int CHECK_POINT = 200;

class TileMat : public BaseObject
{
public:
	TileMat() {}
	~TileMat() {}

};

class GameMap : public BaseObject
{
public:
	GameMap();
	~GameMap();

	void LoadMap(char* name);
	void LoadTiles(SDL_Renderer* screen, int scene);
	void DrawMap(SDL_Renderer* screen);
	Map getMap() const { return game_map_; };

	void setMap(Map& map_data) { game_map_ = map_data; };
	
private:
	

	Map game_map_;
	TileMat tile_mat[MAX_TILES];
	
};

#endif // !GAME_MAP_H_

