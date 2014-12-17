#ifndef Entity_H_INCLUDED
#define Entity_H_INCLUDED

#include "DungeonLevel.h"
#include "XMLSerializable.h"

class Entity : public XMLSerializable{

public:

	Entity();
	Entity(string name,char symb); 

	virtual ~Entity();

	virtual string getName();
	virtual char getSymbol();
	virtual bool initialSet(DungeonLevel * DL,int ycoord, int xcoord);
	virtual void setName(string newName);
	virtual void setSymbol(string newSymbol);
	virtual int stringToInt(string num);
	virtual int getXC();
	virtual int getYC();
	virtual void setXC(int xcoord);
	virtual void setYC(int ycoord);

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);
protected:
	bool inBounds(DungeonLevel* DL,int ycoord, int xcoord);
private:
	
	string s_name;
	char c_symbol;
	map<string,void (Entity::*)(string)> m_setEntityVals;
	int xc;
	int yc;
};

#endif