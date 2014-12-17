#ifndef Item_H_INCLUDED
#define Item_H_INCLUDED

#include "Entity.h"

class Item : public Entity{

public:

	Item();
	Item(string name,char symb,int val, int weight);
	

	virtual int getValue();
	virtual int getWeight();

	virtual void setValue(int newValue);
	virtual void setWeight(int newWeight);
	virtual int getXC();
	virtual int getYC();
	virtual void setXC(int xcoord);
	virtual void setYC(int ycoord);
	virtual bool initialSet(DungeonLevel * DL,int ycoord, int xcoord);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);
	virtual void pickUp(Entity* Thing);
	virtual bool isPickedUp();
	virtual void drop();

private:
	int i_value;
	int i_weight;
	map<string,void (Item::*)(int)> m_setItemVals;
	bool b_carried;
	Entity * Carrier;
};



#endif