#include "Consumable.h"

Consumable::Consumable()
	:Item()
{
	i_quantity =0;
	m_setConsumableVals["quantity"] = &Consumable::setQuantity;
}
Consumable::Consumable(string name,char symb,int val, int weight,int quantity)
	:Item(name,symb,val,weight)
{
	i_quantity =quantity;
}
	
int Consumable::getQuantity(){return i_quantity;}

void Consumable::setQuantity(int newQuantity){i_quantity = newQuantity;}

void Consumable::use(){

}

void Consumable::dumpObject()
{
	cout<< "Consumable:"<<endl;
	dumpObjectData();
}
void Consumable::dumpObjectData()
{
	Item::dumpObjectData();
	cout<<"	quantity : "<< getQuantity() <<endl;
	
}
void Consumable::writeFragment(ostream & output)
{
	output<<" <Consumable>" <<endl;
	writeDataAsFragment(output);
	output<< " </Consumable>"<<endl;
}
void Consumable::writeDataAsFragment(ostream & output)
{
	Item::writeDataAsFragment(output);

	output<< "	<quantity>"<<getQuantity()<<"</quantity>"<<endl;
}
void Consumable::setElementData(string sElementName, string sValue)
{
	
	void (Consumable::*pFunc)(int) = m_setConsumableVals[sElementName];
	if (pFunc == NULL ){
		//cout <<"Not a Consumable value"<<endl;
		Item::setElementData(sElementName,sValue);
	}
	else{
		int iValue = stringToInt(sValue);
		(this->*pFunc)(iValue);
		//cout<<"Saved" + sValue +" in Consumable"<<endl;
	}
}