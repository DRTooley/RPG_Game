#include "Entity.h"


Entity::Entity(){
	s_name ="";
	c_symbol = ' ';
	//void (Entity::*func1)(string) = &Entity::setName;
	//void (Entity::*func2)(string) = &Entity::setSymbol;
	m_setEntityVals["name"] = &Entity::setName;
	m_setEntityVals["symbol"] = &Entity::setSymbol;
	
}
Entity::Entity(string name,char symb)
	:XMLSerializable()
{
	s_name =name;
	c_symbol = symb;
}



bool Entity::initialSet(DungeonLevel * DL,int ycoord, int xcoord){
	if(inBounds(DL,ycoord,xcoord)){
		Entity::setXC(xcoord);
		Entity::setYC(ycoord);
		return true;
	}
	return false;
}




int Entity::getXC(){return xc;}
int Entity::getYC(){return yc;}
void Entity::setXC(int xcoord){
	xc=xcoord;
}
void Entity::setYC(int ycoord){
	yc=ycoord;
}
bool Entity::inBounds(DungeonLevel* DL,int ycoord, int xcoord){
	if(ycoord<0 || ycoord >19 || xcoord <0 || xcoord >79){
		return false;
	}
	char nextSpace=DL->getDungeonMap()[ycoord][xcoord].getTile();
	if(DL->getDungeonMap()[ycoord][xcoord].hasItem()){
		char nextSpaceItem=DL->getDungeonMap()[ycoord][xcoord].getItem();
		if(nextSpace== '.' || nextSpace == '#'|| nextSpace == '>'|| nextSpace == '<'||nextSpace == nextSpaceItem){
			return true;
		}
	}
	else if (nextSpace== '.' || nextSpace == '#'|| nextSpace == '>'|| nextSpace == '<')
		return true;
	return false;
}
Entity::~Entity(){}

string Entity::getName(){return s_name;}
//void Entity::addToMap(string ref, function<void(string)> pRef){m_setVals[ref] = pRef;}
char Entity::getSymbol(){return c_symbol;}

void Entity::setName(string newName){s_name=newName;}
void Entity::setSymbol(string newSymbol){c_symbol=newSymbol[0];}
int Entity::stringToInt(string num){return atoi(num.c_str());}

void Entity::dumpObject()
{
	cout<< "Entity:"<<endl;
	dumpObjectData();
}
void Entity::dumpObjectData()
{
	cout<<"	         Name : "<< getName() <<endl;
	cout<<"	       Symbol : "<< getSymbol()<<endl;
	
}
void Entity::writeFragment(ostream & output)
{
	output<<" <Entity>" <<endl;
	writeDataAsFragment(output);
	output<< " </Entity>"<<endl;
}
void Entity::writeDataAsFragment(ostream & output)
{
	output<< "	<name>"<<getName()<<"</name>"<<endl
		<<"	<symbol>"<<getSymbol()<<"</symbol>"<<endl;
}
void Entity::setElementData(string sElementName, string sValue)
{
	
	void (Entity::*pFunc)(string) = m_setEntityVals[sElementName];

	if (pFunc == NULL ){
		//cout <<"Not an Entity value"<<endl;
	}
	else{
		(this->*pFunc)(sValue);
		//cout<<"Saved" + sValue +" in Entity"<<endl;
		
	}
	
}