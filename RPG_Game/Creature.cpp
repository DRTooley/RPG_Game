#include "Creature.h"

Creature::Creature()
	:Character()
{
	b_hostile = true;
	m_setCreatureVals["hostile"] = &Creature::setHostile;

}
Creature::Creature(string name,char symb,int health,bool hostile,int XP, int level)
	:Character(name,symb,health,XP,level)
{
	b_hostile=hostile;

}//movement and stats
	
bool Creature::isHostile(){return b_hostile;}

void Creature::setHostile(bool newHostile){b_hostile=newHostile;}
bool Creature::isPlayer(){return false;}
Creature::Creature(Creature & Thing)
	:Character(Thing.getName(),Thing.getSymbol(),Thing.getHealth(),Thing.getXP(),Thing.getLevel())
{
	b_hostile=Thing.isHostile();
}

void Creature::attack(Character &target)
{
	if(target.isPlayer())
		Character::attack(target);
}
void Creature::Move(DungeonLevel* DL,int Y, int X){
	vector<vector<Tile>> *Changeable = DL->changeDungeonMap();
	(*Changeable)[getYC()][getXC()].Contain();
	if(getXC()<X){
		setXC(DL,getXC()+1);
	}

	else if(getYC()<Y){
		setYC(DL,getYC()+1);

	}
	else if(getXC()>X){
		setXC(DL,getXC()-1);
	}

	else if(getYC()>Y){
		setYC(DL,getYC()-1);
	}
	(*Changeable)[getYC()][getXC()].Contain(getSymbol());

}
void Creature::dumpObject()
{
	cout<< "Creature:"<<endl;
	dumpObjectData();
}
void Creature::dumpObjectData()
{
	Character::dumpObjectData();
	cout<<"	      Hostile : "<< isHostile() <<endl;

	
}
void Creature::writeFragment(ostream & output)
{
	output<<" <Creature>" <<endl;
	writeDataAsFragment(output);
	output<< " </Creature>"<<endl;
}
void Creature::writeDataAsFragment(ostream & output)
{
	Character::writeDataAsFragment(output);
	output<< "	<hostile>"<<isHostile()<<"</hostile>"<<endl;
}
void Creature::setElementData(string sElementName, string sValue)
{
	
	void (Creature::*pFunc)(bool) = m_setCreatureVals[sElementName];
	if (pFunc == NULL ){
		//cout <<"Not an Creature value"<<endl;
		Character::setElementData(sElementName,sValue);
	}
	else{
		bool bValue = false;
		//cout<<sValue<<"Next"<<endl;
		if( !sValue.compare("true")|| !sValue.compare("1")){
			bValue = true;
		}
		
		(this->*pFunc)(bValue);
		//cout<<"Saved" + sValue +" in Creature"<<endl;
	}
}