/*
#include <iostream>
#include <map>
#include <string>

#include <functional>
#include "XMLSerializable.h"
#include "Armor.h"
#include "Weapon.h"
#include "Item.h"
#include "Creature.h"

using namespace std;


int  main(){
	string sLookup;
	cout << "What class would you like to create? ";
	cin >> sLookup;

	map<string,function<XMLSerializable*()>> mapConstructor;
	mapConstructor["Item"] = [](){return new Item;};
	mapConstructor["Creature"] = []() { return new Creature;};
	mapConstructor["Weapon"] = [] () {return new Weapon;};
	mapConstructor["Armor"]= [](){return new Armor;};

	function<XMLSerializable*()> pFunc = mapConstructor[sLookup];
	if (pFunc == NULL ){
	cout <<"There ain't nothin' in there!!"<<endl;
	}
	else{
	pFunc();
	cout<<"It has been a pleasure working for you"<<endl;
	}
	return 1;
}
*/