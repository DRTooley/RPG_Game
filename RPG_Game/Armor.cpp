#include "Armor.h"

Armor::Armor()
	:Equipment()
{
	i_defenseBonus =0;
	m_setArmorVals["defenseBonus"] = &Armor::setDefenseBonus;
}
Armor::Armor(string name,char symb,int val, int weight,string slot,int defenseBonus)
	:Equipment(name,symb,val,weight,slot)
{
	i_defenseBonus =defenseBonus;
}
	

void Armor::setDefenseBonus(int newDB){i_defenseBonus=newDB;}
int Armor::getDefenseBonus(){return i_defenseBonus;}

void Armor::dumpObject()
{
	cout<< "Armor:"<<endl;
	dumpObjectData();
}
void Armor::dumpObjectData()
{
	Equipment::dumpObjectData();
	cout<<"	Defense Bonus : "<< getDefenseBonus() <<endl;
	
}
void Armor::writeFragment(ostream & output)
{
	output<<" <Armor>" <<endl;
	writeDataAsFragment(output);
	output<< " </Armor>"<<endl;
}
void Armor::writeDataAsFragment(ostream & output)
{
	Equipment::writeDataAsFragment(output);

	output<< "	<defenseBonus>"<<getDefenseBonus()<<"</defenseBonus>"<<endl;
}
void Armor::setElementData(string sElementName, string sValue)
{
	
	void (Armor::*pFunc)(int) = m_setArmorVals[sElementName];
	if (pFunc == NULL ){
		//cout <<"Not an Armor value"<<endl;
		Equipment::setElementData(sElementName,sValue);
	}
	else{
		int iValue = stringToInt(sValue);
		(this->*pFunc)(iValue);
		//cout<<"Saved" + sValue +" in Armor"<<endl;
	}
}