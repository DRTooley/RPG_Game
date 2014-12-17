#include "Weapon.h"

Weapon::Weapon()
	:Equipment()
{
	i_attackBonus = 0;
	i_weaponType = -1;
	m_setWeaponVals["attackBonus"] = &Weapon::setAttackBonus;
	m_setWeaponVals["weaponType"] = &Weapon::setWeaponType;
}
Weapon::Weapon(string name,char symb,int val, int weight,string slot,int attBonus, int weaponType)
	:Equipment(name,symb,val,weight,slot)
{
	i_attackBonus = attBonus;
	i_weaponType = weaponType;
}
	

void Weapon::setAttackBonus(int newAB){i_attackBonus=newAB;}
void Weapon::setWeaponType(int newWT){i_weaponType=newWT;}

int Weapon::getAttackBonus(){return i_attackBonus;}
int Weapon::getWeaponType(){return i_weaponType;}

void Weapon::dumpObject()
{
	cout<< "Weapon:"<<endl;
	dumpObjectData();
}
void Weapon::dumpObjectData()
{
	Equipment::dumpObjectData();
	cout<<"	 Attack Bonus : "<< getSlot() <<endl;
	cout<<"	  Weapon Type : "<< getSlot() <<endl;
}
void Weapon::writeFragment(ostream & output)
{
	output<<" <Weapon>" <<endl;
	writeDataAsFragment(output);
	output<< " </Weapon>"<<endl;
}
void Weapon::writeDataAsFragment(ostream & output)
{
	Equipment::writeDataAsFragment(output);

	output<< "	<attackBonus>"<<getAttackBonus()<<"</attackBonus>"<<endl
		<<"	<weaponType>"<<getWeaponType()<<"</weaponType>"<<endl;
}
void Weapon::setElementData(string sElementName, string sValue)
{
	void (Weapon::*pFunc)(int) = m_setWeaponVals[sElementName];
	if (pFunc == NULL ){
		//cout <<"Not an Weapon value"<<endl;
		Equipment::setElementData(sElementName,sValue);
	}
	else{
		int iValue = stringToInt(sValue);
		(this->*pFunc)(iValue);
		//cout<<"Saved" + sValue +" in Weapon"<<endl;
	}
}