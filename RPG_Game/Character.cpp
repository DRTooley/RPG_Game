#include "Character.h"

Character::Character()
	:Entity()
{
	i_health=0;
	i_remainingHealth=i_health;
	m_setCharacterVals["health"] = &Character::setHealth;
	m_setCharacterVals["experience"] = &Character::setXP;
	m_setCharacterVals["level"] = &Character::setLevel;

	i_XP =0;
	i_level=1;
	i_XPtoLevel = i_level*5;
}
Character::Character(string name,char symb,int health,int XP, int level)
	:Entity(name,symb)
{
	i_health=health;
	i_remainingHealth=i_health;
	i_XP =XP;
	i_level =level;
	i_XPtoLevel = i_level*5;
}
	

int Character::getAttack(){
	return i_level*5+2;
}

void Character::attack(Character &target){
	target.setRemainingHealth(target.getRemainingHealth()-getAttack());
}

bool Character::isDead(){
	if(getRemainingHealth()<=0){
		//This Character is dead
		//	--> Must be deleted off the board and have chance to drop item
		return true;
	}
	return false;
}
void Character::setRemainingHealth(int healthLeft){i_remainingHealth=healthLeft;}
int Character::getRemainingHealth(){return i_remainingHealth;}

bool Character::adjacent(int GY, int GX){
	int X = getXC();
	int Y = getYC();

	for(int i =-1; i<2;i++)
		for(int j =-1;j<2;j++)
			if(X+i == GX && Y+j == GY)
				return true;
	return false;

}

bool Character::initialSet(DungeonLevel * DL,int ycoord, int xcoord){
	if(Entity::initialSet(DL,ycoord,xcoord)){
		(*(*DL).changeDungeonMap())[Entity::getYC()][Entity::getXC()].Contain(getSymbol());
		return true;
	}
	return false;
}
void Character::setXC(DungeonLevel* DL,int xcoord){
	if(inBounds(DL,Entity::getYC(),xcoord)){
		(*(*DL).changeDungeonMap())[Entity::getYC()][Entity::getXC()].Contain();
		Entity::setXC(xcoord);
		(*(*DL).changeDungeonMap())[Entity::getYC()][Entity::getXC()].Contain(getSymbol());
	}
}
void Character::setYC(DungeonLevel* DL,int ycoord){
	if(inBounds(DL,ycoord,getXC())){
		(*(*DL).changeDungeonMap())[Entity::getYC()][Entity::getXC()].Contain();
		Entity::setYC(ycoord);
		(*(*DL).changeDungeonMap())[Entity::getYC()][Entity::getXC()].Contain(getSymbol());
	}
}

void Character::setXP(int newXP)
{
	i_XP = i_XP + newXP;
	while(i_XP>=i_XPtoLevel)
		level();
}

void Character::level()
{

	i_XP = i_XP - i_XPtoLevel;
	i_level++;
	i_XPtoLevel=i_level*10;
	i_health=i_health+i_level*5;
	i_remainingHealth = i_health;
}
void Character::setLevel(int newLevel){i_level = newLevel;}

int Character::getXP(){return i_XP;}
int Character::getLevel(){return i_level;}

int Character::getHealth(){return i_health;}
void Character::setHealth(int newHealth){
	i_health=newHealth;
	i_remainingHealth=newHealth;
}

void Character::dumpObject()
{
	cout<< "Character:"<<endl;
	dumpObjectData();
}
void Character::dumpObjectData()
{
	Entity::dumpObjectData();
	cout<<"	       Health : "<< getHealth() <<endl;
	cout<<"	Experience : "<< getXP() <<endl;
	cout<<"	     Level : "<< getLevel() <<endl;
	
}
void Character::writeFragment(ostream & output)
{
	output<<" <Character>" <<endl;
	writeDataAsFragment(output);
	output<< " </Character>"<<endl;
}
void Character::writeDataAsFragment(ostream & output)
{
	Entity::writeDataAsFragment(output);
	output<< "	<health>"<<getHealth()<<"</health>"<<endl
		<< "	<experience>"<<getXP()<<"</experience>"<<endl
		<< "	<level>"<<getLevel()<<"</level>"<<endl;
}
void Character::setElementData(string sElementName, string sValue)
{
	void (Character::*pFunc)(int) = m_setCharacterVals[sElementName];
	if (pFunc == NULL ){
		//cout <<"Not an Character value"<<endl;
		Entity::setElementData(sElementName,sValue);
	}
	else{
		int iValue = stringToInt(sValue);
		(this->*pFunc)(iValue);
		//cout<<"Saved" + sValue +" in Character"<<endl;
	}
}

bool Character::isPlayer(){return false;}