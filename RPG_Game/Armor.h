#ifndef Armor_H_INCLUDED
#define Armor_H_INCLUDED

#include "Equipment.h"

class Armor : public Equipment {
public:
	Armor();
	Armor(string name,char symb,int val, int weight,string slot,int defenseBonus);
	

	virtual void setDefenseBonus(int newDB);
	virtual int getDefenseBonus();

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);
private:
	int i_defenseBonus;
	map<string,void (Armor::*)(int)> m_setArmorVals;
};
#endif