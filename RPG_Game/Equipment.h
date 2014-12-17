#ifndef Equipment_H_INCLUDED
#define Equipment_H_INCLUDED

#include "Item.h"

class Equipment : public Item {
public:
	Equipment();
	Equipment(string name,char symb,int val, int weight,string slot);
	

	virtual string getSlot();

	virtual void setSlot(string newSlot);

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);
	
private:
	string s_slot;
	map<string,void (Equipment::*)(string)> m_setEquipmentVals;
};


#endif