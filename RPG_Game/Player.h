#ifndef Player_H_INCLUDED
#define Player_H_INCLUDED

#include "Character.h"
#include "Armor.h"
#include "Weapon.h"
#include "Consumable.h"
#include "Tools.h"
class Player :public Character {
public:
	Player();
	Player(string name,char symb,int health,int XP, int level, int score);
	
	virtual int getAttack();
	virtual bool isPlayer();
	virtual void setXP(int newXP);
	virtual void attack(Character &target);
	virtual int Movement(DungeonLevel * DL, vector<Item*>& DLitems);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);
	virtual int getScore();
	virtual void pickUp(DungeonLevel *DL, vector<Item*> DLitems);
	virtual void drop(DungeonLevel *DL, vector<Item*> &DLitems, Item* dropMe);
	virtual void dropList(DungeonLevel *DL, vector<Item*> &DLitems);
	virtual int getHealth();
	virtual void displayStats();
	virtual void usePotion();
private:
	int i_score;
	vector<Item*> v_items;
};
#endif