#ifndef Consumable_H_INCLUDED
#define Consumable_H_INCLUDED

#include "Item.h"

class Consumable : public Item{

public:
	Consumable();
	Consumable(string name,char symb,int val, int weight,int quantity);
	

	virtual int getQuantity();

	virtual void setQuantity(int newQuantity);

	virtual void use();

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);
private:
	int i_quantity;
	map<string,void (Consumable::*)(int)> m_setConsumableVals;

};

#endif