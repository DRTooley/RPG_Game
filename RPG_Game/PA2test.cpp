/*
CS 216 Fall 2013
Programming assignment
David Tooley
*/
/*

#include "Entity.h"
#include "Item.h"
#include "Consumable.h"
#include "Equipment.h"
#include "Weapon.h"
#include "Armor.h"
#include "Character.h"
#include "Creature.h"
#include "Player.h"
#include "DungeonLevel.h"
#include "Tile.h"

#include <functional>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>


using namespace std;

void pause(bool have_newline);
int findHeight(vector<vector<Tile>> & DungeonMap, int y, int x);
int findWidth(vector<vector<Tile>> & DungeonMap, int y, int x);
void passable(vector<vector<Tile>> & DungeonMap, int y, int x);
bool rectangular(vector<vector<Tile>> & DungeonMap, int y, int x);
int hasSixteen(vector<vector<Tile>> & DungeonMap, int y, int x);



void pause(bool have_newline)
{
    if (have_newline) {
        // Ignore the newline after the user's previous input.
        cin.ignore(200, '\n');
    }

    // Prompt for the user to press ENTER, then wait for a newline.
    cout << endl << "Press ENTER to continue." << endl;
    cin.ignore(200, '\n');
}

void passable(vector<vector<Tile>> & DungeonMap, int y, int x){
	if(DungeonMap[y][x].getTile()== ' '||DungeonMap[y][x].getTile()=='X'){
		return;
	}
	DungeonMap[y][x].setTile('X');
	if(y>0){
		if(x>0)
			passable(DungeonMap, y-1,x-1);
		passable(DungeonMap, y-1,x);
		if(x<79)
			passable(DungeonMap, y-1,x+1);
	}
	if(x>0)
		passable(DungeonMap, y,x-1);
	if(x<79)
	passable(DungeonMap, y,x+1);
	if(y<20){
		if(x>0)
			passable(DungeonMap, y+1,x-1);
		passable(DungeonMap, y+1,x);
		if(x<79)
			passable(DungeonMap, y+1,x+1);
	}
}

bool rectangular(vector<vector<Tile>> & DungeonMap, int y, int x){
	int roomHeight=findHeight(DungeonMap,y,x);
	int roomWidth = findWidth(DungeonMap,y,x);
	

	for(int height = y; height<y+roomHeight;height++){
		for(int width =x; width<x+roomWidth;width++){
			if(DungeonMap[height][width].getTile()==' '||
				DungeonMap[height][width].getTile()=='#')
			{
					return false;
			}
		}
	}
	
	for(int LR=y;LR<y+roomHeight;LR++){
		if(x+roomWidth<79)
			if(DungeonMap[LR][x+roomWidth].getTile()=='.'||
				DungeonMap[LR][x+roomWidth].getTile()=='<'||
				DungeonMap[LR][x+roomWidth].getTile()=='>')
			{
					return false;
			}
		if(x-1>=0)
			if(DungeonMap[LR][x-1].getTile()=='.'||
				DungeonMap[LR][x-1].getTile()=='<'||
				DungeonMap[LR][x-1].getTile()=='>')
			{
					return false;
			}
	}
	for(int TB=x;TB<=x+roomWidth;TB++){
		if(y-1>=0)
			if(DungeonMap[y-1][TB].getTile()=='.'||
				DungeonMap[y-1][TB].getTile()=='<'||
				DungeonMap[y-1][TB].getTile()=='>')
			{
					return false;
			}
		if(y+roomHeight<20)	
			if(DungeonMap[y+roomHeight][TB].getTile()=='.'||
				DungeonMap[y+roomHeight][TB].getTile()=='<'||
				DungeonMap[y+roomHeight][TB].getTile()=='>')
			{
					return false;
			}
	}

	return true;
		
}

int findHeight(vector<vector<Tile>> & DungeonMap, int y, int x){
	int height =0;
	if(y<20){
		if(DungeonMap[y][x].getTile()== ' '||DungeonMap[y][x].getTile()== '#'){
			return 0;
		}
	}
	else 
		return 0;
	height++;
	return height+=findHeight(DungeonMap,y+1,x);
}

int findWidth(vector<vector<Tile>> & DungeonMap, int y, int x){
	int width =1;
	if(x<79){
		if(DungeonMap[y][x].getTile()== ' '||DungeonMap[y][x].getTile()== '#'){
			return 0;
		}
	}
	else
		return 0;
	
	width+=findWidth(DungeonMap,y,x+1);
	return width;
}

int hasSixteen(vector<vector<Tile>> & DungeonMap, int y, int x){
	int numDot=0;
	if(DungeonMap[y][x].getTile()!= '.'&&DungeonMap[y][x].getTile()!= '>'&&DungeonMap[y][x].getTile()!= '<'){
		return 0;
	}
	
	numDot++;
	DungeonMap[y][x].setTile('X');
	if(y>0){
		if(x>0)
			numDot+=hasSixteen(DungeonMap, y-1,x-1);
		numDot+=hasSixteen(DungeonMap, y-1,x);
		if(x<79)
			numDot+=hasSixteen(DungeonMap, y-1,x+1);
	}
	if(x>0)
		numDot+=hasSixteen(DungeonMap, y,x-1);
	if(x<79)
	numDot+=hasSixteen(DungeonMap, y,x+1);
	if(y<20){
		if(x>0)
			numDot+=hasSixteen(DungeonMap, y+1,x-1);
		numDot+=hasSixteen(DungeonMap, y+1,x);
		if(x<79)
			numDot+=hasSixteen(DungeonMap, y+1,x+1);
	}
	return numDot;
}






int main(int argc, char * argv[])
{
	int numConnectFail=0;
	int numLessSixteen=0;
	int numNotRect=0;
	int numLessTwoHund=0;
	int numNoUpstair=0;
	int numNoDownstair=0;
	int numWrongDimensions=0;

	DungeonLevel* test;
	//Get # runs here
	int userInput = 10000;
	//create for loop here for that many runs
	for(int runs =0;runs<userInput;runs++){
		test = new DungeonLevel;
		vector<vector<Tile>> DungeonMap = test->getDungeonMap();
		//Testing DungeonLevel
		int RoomTiles=0;
		bool downstairs = false; 
		bool upstairs=false;
		bool rectangle=true;
		int sixteen=16;
		bool dimensions=true;

		if(DungeonMap[0].size()!=79||DungeonMap.size()!=20){
			dimensions=false;
			numWrongDimensions++;
		}


		
		for(int height = 0; height<20;height++){
			for(int width =0; width<79;width++){
				if(DungeonMap[height][width].getTile()=='.'){ // 200 tiles
					RoomTiles++;
				}
				if(DungeonMap[height][width].getTile()=='>')
					downstairs=true;
				if(DungeonMap[height][width].getTile()=='<')
					upstairs=true;
			}
		}

		//rectangular/overlap test (Assumed to not over lap if all are rectangular)
		for(int height = 0; height<20;height++){
			for(int width =0; width<79;width++){
				if(DungeonMap[height][width].getTile()=='.'||DungeonMap[height][width].getTile()=='>'||DungeonMap[height][width].getTile()=='<'){
					if(rectangle){
						rectangle = rectangular(DungeonMap,height,width);
						hasSixteen(DungeonMap,height,width);//used to destroy room so that it is not counted twice
					}
				}
			}
		}
		DungeonMap = test->getDungeonMap();


		//test for >= 16 spaces in each room
		for(int height = 0; height<20;height++){
			for(int width =0; width<79;width++){
				if(DungeonMap[height][width].getTile()=='.'){
					if(sixteen>=16)
						sixteen = hasSixteen(DungeonMap,height,width);//actual has 16 test number
				}
			}
		}
		DungeonMap = test->getDungeonMap();




		//Connectivity test - > will destroy map
		int y=0; int x=0;bool hasNoPassable = false; bool connected = true;
		while(DungeonMap[y][x].getTile()==' '){
			x++;
			if(x>=79){
				y++;
				x=0;
			}
			if(y>=20){
				break;
				hasNoPassable=true;
			}
		}
		if(!hasNoPassable){
			passable(DungeonMap,y,x);
		}
		for(int height = 0; height<20;height++){
			for(int width =0; width<79;width++){
				if(DungeonMap[height][width].getTile()=='.'||
					DungeonMap[height][width].getTile()=='#'||
					DungeonMap[height][width].getTile()=='<'||
					DungeonMap[height][width].getTile()=='>'){
					connected = false;
				}
			}
		}

		if(dimensions)
			cout<<"Correct Dimensions: true"<<endl;
		else{
			numWrongDimensions++;
			cout<<"Correct Dimensions: false"<<endl;
		}
		if( RoomTiles>=200)
			cout<<"Room Tiles >= 200: true"<<endl;
		else{
			cout<<"Room Tiles >= 200: false"<<endl;
			numLessTwoHund++;
		}
		if(downstairs)
			cout<<"Downstairs: true"<<endl;
		else{
			cout<<"Downstairs: false"<<endl;
			numNoDownstair++;
		}
		if(upstairs)
			cout<<"Upstairs: true"<<endl;
		else{
			cout<<"Upstairs: false"<<endl;
			numNoUpstair++;
		}
		if(rectangle)
			cout<<"Rectangular: true"<<endl;
		else{
			cout<<"Rectangular: false"<< endl;
			numNotRect++;
			test->displayDungeonLevel();
			system("pause");
		}
		if(sixteen>=16)
			cout<<">Sixteen: true"<<endl;
		else{
			cout<<">Sixteen: false"<<endl;
			numLessSixteen++;
		}

		cout<<"Connectivity test: ";
		if(connected)
			cout<<"true"<<endl;
		else{
			cout<<"false"<<endl;
			numConnectFail++;
		}

	
		//after all tests are complete
		delete test;
		}//end for loop

	cout<<endl<<"Results:"<<endl;
	cout<<"Number of connection Failures: " <<numConnectFail<<endl;
	cout<<"Number with rooms less than 16 spaces: "<< numLessSixteen<<endl;
	cout<<"Number of non-rectangular rooms: "<< numNotRect<<endl;
	cout<<"Number less than 200 room spaces: "<< numLessTwoHund<<endl;
	cout<<"Number missing upstairs: "<< numNoUpstair<<endl;
	cout<<"Number missing downstairs: "<< numWrongDimensions<<endl;
		
	


	
	pause(false);
	return 0;
}
*/