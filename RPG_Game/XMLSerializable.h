#ifndef _XMLSerializable_included_
#define _XMLSerializable_included_


#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <functional>
using namespace std;

class XMLSerializable
{
public:
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);
};


#endif
