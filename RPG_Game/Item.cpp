#include "Item.h"

Item::Item()
	:Entity()
{
	i_value = 0;
	i_weight =0;
	b_carried = false;
	m_setItemVals["value"] = &Item::setValue;
	m_setItemVals["weight"] = &Item::setWeight;
	Carrier=NULL;
}
Item::Item(string name,char symb,int val, int weight)
	:Entity(name,symb)
{
	i_value = val;
	i_weight =weight;
	b_carried = false;
	Carrier = NULL;
}
	
bool Item::initialSet(DungeonLevel * DL,int ycoord, int xcoord){
	if(Entity::initialSet(DL,ycoord,xcoord)){
		(*(*DL).changeDungeonMap())[Entity::getYC()][Entity::getXC()].ContainItem(getSymbol());
		return true;
	}
	return false;
}
int Item::getValue(){return i_value;}
int Item::getWeight(){return i_weight;}

void Item::setValue(int newValue){i_value=newValue;}
void Item::setWeight(int newWeight){i_weight=newWeight;}

void Item::dumpObject()
{
	cout<< "Item:"<<endl;
	dumpObjectData();
}
void Item::dumpObjectData()
{
	Entity::dumpObjectData();
	cout<<"	        Value : "<< getValue() <<endl;
	cout<<"	       Weight : "<< getWeight()<<endl;
	
}
void Item::writeFragment(ostream & output)
{
	output<<" <Item>" <<endl;
	writeDataAsFragment(output);
	output<< " </Item>"<<endl;
}
void Item::writeDataAsFragment(ostream & output)
{
	Entity::writeDataAsFragment(output);

	output<< "	<value>"<<getValue()<<"</value>"<<endl
		<<"	<weight>"<<getWeight()<<"</weight>"<<endl;
}
void Item::setElementData(string sElementName, string sValue)
{
	
	void (Item::*pFunc)(int) = m_setItemVals[sElementName];
	if (pFunc == NULL ){
		//cout <<"Not an Item value"<<endl;
		Entity::setElementData(sElementName,sValue);
	}
	else{
		int iValue = stringToInt(sValue);
		(this->*pFunc)(iValue);
		//cout<<"Saved" + sValue +" in Item"<<endl;
	}
	
}




bool Item::isPickedUp(){
	return b_carried;
}



void Item::pickUp(Entity* Thing)
{
	b_carried=true;
	Carrier = Thing;
}
void Item::drop()
{
	Entity::setXC(Carrier->getXC());
	Entity::setYC(Carrier->getYC());
	b_carried=false;
	Carrier = NULL;
	
}

int Item::getXC()
{
	if(b_carried)
		return Carrier->getXC();
	else
		return Entity::getXC();
}
int Item::getYC()
{
	if(b_carried)
		return Carrier->getYC();
	else
		return Entity::getYC();
}

void Item::setXC(int xcoord)
{
	if(!b_carried)
		Entity::setXC(xcoord);
}
void Item::setYC(int ycoord)
{
	if(!b_carried)
		Entity::setYC(ycoord);
}
