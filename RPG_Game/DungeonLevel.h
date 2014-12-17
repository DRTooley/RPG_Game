#ifndef DungeonLevel_H_INCLUDED
#define DungeonLevel_H_INCLUDED

#include <random>
#include <iostream>
#include <ctime>
#include <vector>
#include "Room.h"
#include "Tile.h"
using namespace std;


class DungeonLevel{
public:
	DungeonLevel();
	~DungeonLevel();
	vector<vector<Tile>> *changeDungeonMap();
	vector<vector<Tile>> getDungeonMap();
	void displayDungeonLevel();

private:
	void blankCanvas();
	void createAllRooms();
	void paintRooms();
	bool notEnoughFloorTiles();
	void addStairs();
	void drawTunnels();
	void drawTunnel(Room * one, Room* two);
	void reorderLtoR();
	Room* createRandRoom();
	int checkRooms();
	vector<vector<Tile>> v_tiles;
	vector<Room*> randRoom;
	mt19937 mt;
};


#endif