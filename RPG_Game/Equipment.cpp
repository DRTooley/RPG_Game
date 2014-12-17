#include "Equipment.h"

Equipment::Equipment()
	:Item()
{
	s_slot="";
	m_setEquipmentVals["slot"] = &Equipment::setSlot;
	
}
Equipment::Equipment(string name,char symb,int val, int weight,string slot)
	:Item(name,symb,val,weight)
{
	s_slot=slot;
}
	
string Equipment::getSlot(){return s_slot;}
void Equipment::setSlot(string newSlot){s_slot = newSlot;}

void Equipment::dumpObject()
{
	cout<< "Equipment:"<<endl;
	dumpObjectData();
}
void Equipment::dumpObjectData()
{
	Item::dumpObjectData();
	cout<<"	         Slot : "<< getSlot() <<endl;
	
	
}
void Equipment::writeFragment(ostream & output)
{
	output<<" <Equipment>" <<endl;
	writeDataAsFragment(output);
	output<< " </Equipment>"<<endl;
}
void Equipment::writeDataAsFragment(ostream & output)
{
	Item::writeDataAsFragment(output);

	output<< "	<slot>"<<getSlot()<<"</slot>"<<endl;
}
void Equipment::setElementData(string sElementName, string sValue)
{
	Item::setElementData(sElementName,sValue);
	void (Equipment::*pFunc)(string) = m_setEquipmentVals[sElementName];
	if (pFunc == NULL ){
		//cout <<"Not an Item value"<<endl;
		Item::setElementData(sElementName,sValue);
	}
	else{
		
		(this->*pFunc)(sValue);
		//cout<<"Saved" + sValue +" in Item"<<endl;
	}
}