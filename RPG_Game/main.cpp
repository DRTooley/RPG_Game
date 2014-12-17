/*
CS 216 Fall 2013
Programming assignment
David Tooley
*/

#include "parser.h"
#include "GenericFactory.h"
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
#include "Room.h"
#include "Tools.h"

#include <functional>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>


using namespace std;


void dumpObjects(vector<XMLSerializable*> &v_objects);
void outputXML(vector<XMLSerializable*> & v_objects, ostream &output);


void getCurrentLevel(vector<vector<char>> &CL, DungeonLevel* DL);
void displayLevel(vector<vector<char>> &CL,DungeonLevel* DL);

void findChar(vector<vector<Tile>> DL, char find,int &Y, int &X){
	Y=0;
	
	for(auto it = DL.begin();it!=DL.end();it++){
		X=0;
		for(auto next = (*it).begin();next!=(*it).end();next++){
			if((*next).getUnderTile() == find){
				return;
			}
			X++;
		}
		Y++;
	}
	return;
}

void randXY(Tools & Tool, int &Y, int &X){
	X=Tool.randomValue(79);
	Y=Tool.randomValue(20);
}

vector<Creature*> CreateCreatures(Tools Tool, DungeonLevel * DL, int HowMany, int Strength){
	vector<Creature*> Monsters;
	int X,Y;
	for(int i =0; i<HowMany;i++){

		Creature * pCritter = GenericFactory::instance().generateCreature(Strength);
		Monsters.push_back(pCritter);
		if(pCritter != NULL){
			do{
				randXY(Tool,Y,X);
			}while(!pCritter->initialSet(DL,Y,X));
			//cout << Y<<","<<X<<endl;
			//pCritter->dumpObject();
			cout << endl;
		}
	}
	return Monsters;

}

vector<Item*> CreateItems(Tools Tool, DungeonLevel * DL, int HowMany){
	vector<Item*> Items;
	int X,Y;
	for(int i =0; i<HowMany;i++){
		Item * pItem;
		int type = Tool.randomValue(3);
		if(type==0)
			pItem = GenericFactory::instance().generateWeapon();
		else if(type ==1)
			pItem = GenericFactory::instance().generateArmor();
		else
			pItem = GenericFactory::instance().generateConsumable();
		Items.push_back(pItem);
		if(pItem != NULL){
			do{
				randXY(Tool,Y,X);
			}while(!pItem->initialSet(DL,Y,X));
		}
	}
	return Items;

}



int main(int argc, char * argv[]){
	Tools Tool;
	string user = "Tunneler";
	char sym = 'T';
	int hth = 35;
	int baseXP =0;
	int baselevel=1;
	int basescore =0;
	int StairX;
	int StairY;
	int Depth=0;
	int randX,randY;
	int UpDown;
	int Generator;
	vector<vector<Creature*>> Mobs;
	vector<vector<Item*>>ItemsDL;
	vector<DungeonLevel*> GameMap;
	DungeonLevel * level = new DungeonLevel();
	GameMap.push_back(level);
	vector<vector<char>> CurrentLevel;
	//default Player
	Player Gamer = Player(user,sym,hth,baseXP, baselevel, basescore);
	
	Mobs.push_back(CreateCreatures(Tool,GameMap[Depth],3,30));
	ItemsDL.push_back(CreateItems(Tool,GameMap[Depth],2));
	findChar((*GameMap[Depth]).getDungeonMap(),'>',StairY,StairX);
	Gamer.initialSet(GameMap[Depth],StairY,StairX);


	cout<<"You are the Super Tunnler!"<<endl
		<<"Movement: W is up, A is left, S is down, D is right."<<endl
		<<"Use P to pickup items off of the ground, U is to use potions(if you have any)."<<endl
		<<"E gives a list of all things in your inventory and the option to drop items."<<endl
		<<"Your inventory can hold as many items as you would like."<<endl<<"You're basically a pack rat."<<endl
		<<"X is the input to display your current Stats. Picking up items, dropping items,"<<endl
		<<"using potions, and checking stats do not take up a movement turn."<<endl<<endl;

	cout<<"I implemented the positioning system inside of both the tiles and the entity."<<endl
		<<"If I were to restart I would most likely choose to use only the positioning " <<endl
		<<"inside of Entity just for simplicity sake. Origonally I thought it would make"<<endl
		<<"it easier access to the information that was needed, depending on the"<<endl
		<<"situation but it ended up being as much trouble to ensure that everything"<<endl
		<<"match from the tiles to the Entities. I also found having an inclusion circle"<<endl
		<<"is bad. eg: DungeonLevels including Tiles, Tiles (attempting) to include"<<endl
		<<"Entities, and Entities including DungeonLevels. Took me a while to get"<<endl
		<<"that one straightened out. Nothing too extravagant honestly, you either"<<endl
		<<"leave out the enterance or die to end the game. Enjoy!"<<endl;
	
	Tool.pause(false);

	displayLevel(CurrentLevel,GameMap[Depth]);
	bool keepPlaying =true;
	
	while(keepPlaying){
		UpDown = Gamer.Movement(GameMap[Depth],ItemsDL[Depth]);

		
		
		

		if(UpDown==-1){
			(*GameMap[Depth]->changeDungeonMap())[Gamer.getYC()][Gamer.getXC()].Contain();
			Depth++;
			
			bool newlyMade = false;
			if(Depth==GameMap.size()){
				GameMap.push_back(new DungeonLevel());
				newlyMade=true;
			}
			getCurrentLevel(CurrentLevel,GameMap[Depth]);
			findChar((*GameMap[Depth]).getDungeonMap(),'>',StairY,StairX);
			Gamer.initialSet(GameMap[Depth],StairY,StairX);
			if(newlyMade){
				Mobs.push_back(CreateCreatures(Tool,GameMap[Depth],3,30+Depth*25));
				ItemsDL.push_back(CreateItems(Tool,GameMap[Depth],3));
			}
			displayLevel(CurrentLevel,GameMap[Depth]);
		}
		else if(UpDown==1 && Depth>0){
			(*GameMap[Depth]->changeDungeonMap())[Gamer.getYC()][Gamer.getXC()].Contain();
			Depth--;

			getCurrentLevel(CurrentLevel,GameMap[Depth]);
			findChar((*GameMap[Depth]).getDungeonMap(),'<',StairY,StairX);
			Gamer.initialSet(GameMap[Depth],StairY,StairX);
			displayLevel(CurrentLevel,GameMap[Depth]);
		}
		else if(Depth==0 && UpDown ==1){
			cout<<"Game Over, you went out the enterance, Quitter!"<<endl;
			keepPlaying=false;
		}



		
		if(UpDown==0){
			//have all creatures move towards the player and then attack
			for(auto it = Mobs[Depth].begin();it!=Mobs[Depth].end();it++){
				(*it)->Move(GameMap[Depth],Gamer.getYC(),Gamer.getXC());
			}
			displayLevel(CurrentLevel,GameMap[Depth]);
			for(auto it = Mobs[Depth].begin();it!=Mobs[Depth].end();it++){
				bool AttemptAttack = (*it)->adjacent(Gamer.getYC(),Gamer.getXC());
				if(AttemptAttack && Gamer.getLevel() >= (*it)->getLevel()){
					Gamer.attack((*(*it))); //Gamer always attacks first if equal or higher level
					if(!(*it)->isDead()){
						(*it)->attack(Gamer);
					}
				}
				else if(AttemptAttack){
					(*it)->attack(Gamer);
					if(!Gamer.isDead()){
						Gamer.attack((*(*it)));
					}
				}
				if(AttemptAttack){
					cout<<"Gamer Health: "<<Gamer.getRemainingHealth()<<endl;
					cout<<(*it)->getName()<<"'s Health: "<< (*it)->getRemainingHealth()<<endl;
					if(!(*it)->isDead())
						Tool.pause(false);
				}
				if((*it)->isDead()){
					(*GameMap[Depth]->changeDungeonMap())[(*it)->getYC()][(*it)->getXC()].Contain();
					cout<<"The Mob has died"<<endl;
					Tool.pause(false);
				}
				if(Gamer.isDead()){
					cout<<"You have been mortally wounded in battle and died!"<<endl;
					keepPlaying = false;
					break;
				}

			}
			//deletes all dead Creatures and drop item 25% chance
			auto deletionCreatureIt = Mobs[Depth].begin();
			while(deletionCreatureIt!=Mobs[Depth].end()){
				if((*deletionCreatureIt)->isDead()){
					int DeadX=(*deletionCreatureIt)->getXC();
					int DeadY=(*deletionCreatureIt)->getYC();
					if(Tool.randomValue(4)==0){
						Item * pItem;
						int type = Tool.randomValue(3);
						if(type==0)
							pItem = GenericFactory::instance().generateWeapon();
						else if(type ==1)
							pItem = GenericFactory::instance().generateArmor();
						else
							pItem = GenericFactory::instance().generateConsumable();
						ItemsDL[Depth].push_back(pItem);
						pItem->initialSet(GameMap[Depth],DeadY,DeadX);
					}

					delete (*deletionCreatureIt);
					Mobs[Depth].erase(deletionCreatureIt);
					deletionCreatureIt = Mobs[Depth].begin();
				}
				else
					deletionCreatureIt++;
			}
			
			auto deletionItemIt = ItemsDL[Depth].begin();
			while(deletionItemIt!= ItemsDL[Depth].end()){
				if((*deletionItemIt)->isPickedUp()){
					ItemsDL[Depth].erase(deletionItemIt);
					deletionItemIt = ItemsDL[Depth].begin();
				}
				else{
					deletionItemIt++;
				}
			}

			

			if(!keepPlaying)
				break;


			Generator = Tool.randomValue(int(20/(Depth+1)+1));
			if (Generator==0){      //randomly generate more Creatures

				Creature * pCritter = GenericFactory::instance().generateCreature(Depth*15+30);
				do{
					randXY(Tool,randY,randX);
				}while(!pCritter->initialSet(GameMap[Depth],randY,randX));
				Mobs[Depth].push_back(pCritter);
			}

			displayLevel(CurrentLevel,GameMap[Depth]);
		}

			
	}

	cout<<"The Game is Over!"<<endl;
	cout<<"Level: "<<Gamer.getLevel()<<endl;
	cout<<"Score: "<<Gamer.getScore()<<endl;



	
	return 1;
}










void dumpObjects(vector<XMLSerializable*> &v_objects)
{
	for(auto pObject:v_objects){
		pObject->dumpObject();
		cout<<endl;
	}
	
	
}

void outputXML(vector<XMLSerializable*> & v_objects, ostream &output)
{
	output <<"<?xml version = \"1.0\" encoding = \"UTF-8\"?>"<<endl<<"<World>"<<endl;

	for (auto it = v_objects.begin(); it !=v_objects.end();it++){
	(*it)->writeFragment(output);
	}
	output<<"</World>"<<endl;
}

void getCurrentLevel(vector<vector<char>> &CL, DungeonLevel* DL){
	vector<vector<Tile>> Map = DL->getDungeonMap();
	if(CL.size()<20){ //erases current and creates new if not the correct size
		vector<char> empty;
		for(int i =0;i<79;i++){
			empty.push_back(' ');
		}
		while(CL.size()>0)
			CL.pop_back();
		while(CL.size()<20){
			CL.push_back(empty);
		}
	}
	for(int i =0;i<20;i++){
		for (int j = 0; j < 79; j++)
		{
			CL[i][j] = Map[i][j].getTile();
		}
	}
} 

void displayLevel(vector<vector<char>> &CL,DungeonLevel* DL){
	getCurrentLevel(CL,DL);
	for(auto it = CL.begin();it!=CL.end();it++){
		for(auto internIt = it->begin(); internIt!=it->end();internIt++){
			cout<<(*internIt);
		}
		cout<<endl;
	}
}
