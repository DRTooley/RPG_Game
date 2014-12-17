#ifndef Weapon_H_INCLUDED
#define Weapon_H_INCLUDED

#include "Equipment.h"

class Weapon : public Equipment {
public:
	Weapon();
	Weapon(string name,char symb,int val, int weight,string slot,int attBonus, int weaponType);
	

	virtual void setAttackBonus(int newAB);
	virtual void setWeaponType(int newWT);

	virtual int getAttackBonus();
	virtual int getWeaponType();

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);

private:
	int i_attackBonus;
	int i_weaponType;
	map<string,void (Weapon::*)(int)> m_setWeaponVals;
};

#endif