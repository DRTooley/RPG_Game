#ifndef _GenericFactory_included_
#define _GenericFactory_included_

#include "Creature.h"
#include "EntityVector.h"
#include "Item.h"
#include "Consumable.h"
#include "Armor.h"
#include "Weapon.h"

#include <vector>

class GenericFactory
{
public:	
	static GenericFactory & instance();
	virtual ~GenericFactory();
	Creature * generateCreature(int iMaxHealth);
	Item * generateItem();
	Weapon* generateWeapon();
	Armor* generateArmor();
	Consumable* generateConsumable();

private:
	GenericFactory();
	EntityVector<Creature> m_vCreatures;
	EntityVector<Consumable> m_vConsumables;
	EntityVector<Armor> m_vArmor;
	EntityVector<Weapon> m_vWeapons;
	EntityVector<Item> m_vItems;

};

#endif
