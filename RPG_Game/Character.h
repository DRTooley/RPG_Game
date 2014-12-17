#ifndef Character_H_INCLUDED
#define Character_H_INCLUDED

#include "Entity.h"

class Character : public Entity {
public:
	Character();
	Character(string name,char symb,int health,int XP, int level);// stats and inventory
	

	virtual int getHealth();
	virtual void setHealth(int newHealth);
	virtual bool isPlayer();
	virtual bool adjacent(int GY, int GX);

	virtual void attack(Character &target);
	virtual int getAttack();

	virtual bool initialSet(DungeonLevel * DL,int ycoord, int xcoord);
	virtual void setXP(int newXP);
	virtual void setLevel(int newLevel);
	virtual bool isDead();

	virtual int getXP();
	virtual int getLevel();
	virtual void level();
	virtual void setRemainingHealth(int healthLeft);
	virtual int getRemainingHealth();

	virtual void setXC(DungeonLevel* DL,int xcoord);
	virtual void setYC(DungeonLevel* DL,int ycoord);


	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);
private:
	int i_health;
	map<string,void (Character::*)(int)> m_setCharacterVals;

	int i_remainingHealth;
	int i_level;
	int i_XP;
	int i_XPtoLevel;
};
#endif