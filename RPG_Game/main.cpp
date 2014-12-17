/*
CS 216 Fall 2013
Programming assignment
David Tooley
*/
/*

#include "Entity.h"
#include "Item.h"
#include "Consumable.h"
#include "Equipment.h"
#include "Weapon.h"
#include "Armor.h"
#include "Character.h"
#include "Creature.h"
#include "Player.h"
#include "DungeonLevel.h"
#include "Tile.h"

#include <functional>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>


using namespace std;

void parseElement(istream & input, string sPrefix, XMLSerializable * pObject, map<string,function<XMLSerializable*()>> & m_map, vector<XMLSerializable*> & v_objects, int &flag);
void parseXML(string sFilename, map<string,function<XMLSerializable*()>> & m_map, vector<XMLSerializable*> & v_objects);
void dumpObjects(vector<XMLSerializable*> &v_objects);
void outputXML(vector<XMLSerializable*> & v_objects, ostream &output);


int main(int argc, char * argv[])
{
	

	//Parse XML call
	//Create the mapping
	map<string,function<XMLSerializable*()>> m_objectMap;
	m_objectMap["Item"] = [](){return new Item;};
	m_objectMap["Creature"] = []() { return new Creature;};
	m_objectMap["Weapon"] = [] () {return new Weapon;};
	m_objectMap["Armor"]= [](){return new Armor;};

	vector<XMLSerializable*> v_myObjects;

	cout << "What file should we parse? ";
	string sInFilename;
	cin >> sInFilename;
	cout << endl;

	parseXML(sInFilename, m_objectMap, v_myObjects);
	cout<<endl<<endl<<endl;
	dumpObjects(v_myObjects);
	cout<<endl;
	cout << "Where should it be saved? ";
	string sOutFilename;
	cin >> sOutFilename;
	ofstream output;
	output.open(sOutFilename);
	outputXML(v_myObjects, output);
	

	
	system("pause");
	return 0;
}



void parseElement(istream & input, string sPrefix, XMLSerializable * pObject, map<string,function<XMLSerializable*()>> & m_map, vector<XMLSerializable*> & v_objects, int &flag)
{
	int count = flag;
	string sElementName;
	getline(input, sElementName, '>');

	if( sElementName.back() == '/' )
	{
		//cout << sPrefix << "Empty element: " << sElementName << endl;
		return;
	}
	else
	{
		//cout << sPrefix << " Element - " << sElementName << endl;
		//cout << "Try to construct " << sElementName << " here." << endl;
	}

	string sContent = "";
	string ElemNm = sElementName;


	while( true )
	{

		char c = input.get();

		while( c != '<' )
		{
			if( c != '\n' )
				sContent.push_back(c);

			c = input.get();
		}

		if( input.peek() == '/' )
		{
			input.get();
			string sEndElement;
			getline(input, sEndElement, '>');

			if( sEndElement != sElementName ){
				cout << "Bad XML found" << endl;
				cout<< sEndElement<<" is not " << sElementName<<endl<<endl;
				flag--;
				
				
			}
			//else
				//cout<< sEndElement<<" is " << sElementName<<endl<<endl;

			//cout << sPrefix << " : " << sElementName << " : "  << sContent << endl;
			if(pObject!=NULL)
				pObject->setElementData(sElementName,sContent);

			flag--;
			return;
		}
		else
		{
			
			function<XMLSerializable*()> pFunc = m_map[ElemNm];
			if (pFunc == NULL ){
				//cout <<"DO NOTHING"<<endl;
			}
			else{
				ElemNm ="";
				pObject = pFunc();
				v_objects.push_back(pObject);
				//cout<<endl<<endl<<endl<<"I have created a new XML pointer"<<endl;
			}

			flag++;
			parseElement(input, sPrefix + " > " + sElementName, pObject, m_map,v_objects, flag);
			if(flag !=count){
				v_objects.pop_back();
				return;
			}
		}

	}

}

void parseXML(string sFilename, map<string,function<XMLSerializable*()>> & m_map, vector<XMLSerializable*> & v_objects)
{
	ifstream input;
	input.open(sFilename);

	while( input.get() != '?' );
	while( input.get() != '?' );
	
	if( input.get() != '>' )
	{
		cout << "Bad XML detected" << endl;
		return;
	}

	while( input.get() != '<' );

	int flag =0;
	parseElement(input, "> ", NULL, m_map,v_objects,flag);
	
}

void dumpObjects(vector<XMLSerializable*> &v_objects)
{
	for(auto pObject:v_objects){
		pObject->dumpObject();
		cout<<endl;
	}
	//	Same thing
//	for(int i =0; i<vObjects.size();i++){
//		vObjects[i]->dumpObject();
//		cout<<endl;
//	}
	
	
}

void outputXML(vector<XMLSerializable*> & v_objects, ostream &output)
{
	output <<"<?xml version = \"1.0\" encoding = \"UTF-8\"?>"<<endl<<"<World>"<<endl;

	for (auto it = v_objects.begin(); it !=v_objects.end();it++){
	(*it)->writeFragment(output);
	}
	output<<"</World>"<<endl;
}

*/