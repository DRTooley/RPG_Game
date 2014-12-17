#ifndef Creature_H_INCLUDED
#define Creature_H_INCLUDED

#include "Character.h"

class Creature : public Character {
public:
	Creature();
	Creature(Creature &Thing);
	Creature(string name,char symb,int health,bool hostile,int XP, int level);//movement and stats
	

	virtual bool isHostile();

	virtual void setHostile(bool newHostile);
	virtual bool isPlayer();
	virtual void attack(Character &target);

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);
	virtual void Move(DungeonLevel* DL,int Y, int X);

private:
	bool b_hostile;
	map<string,void (Creature::*)(bool)> m_setCreatureVals;

};

#endif