

#include "Tile.h"

Tile::Tile()
{
	c_symbol = ' ';
	c_containedSymbol=c_symbol;
	b_hasContain = false;
	b_hasItem=false;
	c_itemSym = c_symbol;
}

Tile::Tile(char symbol)
{
	c_symbol=symbol;
	c_containedSymbol=c_symbol;
	b_hasContain = false;
	b_hasItem = false;
	c_itemSym = c_symbol;
}
Tile::~Tile(){}
char Tile::getUnderTile(){return c_symbol;}
char Tile::getTile()
{
	if(b_hasContain)
		return getContained();
	else if(b_hasItem)
		return getItem();
	return c_symbol;
}
char Tile::getItem(){return c_itemSym;}

char Tile::getContained(){return c_containedSymbol;}

bool Tile::hasItem(){return b_hasItem;}

void Tile::setTile(char newSymbol){c_symbol=newSymbol;}

bool Tile::hasCharacter(){return b_hasContain;}

void Tile::Contain(char sym)
{
	b_hasContain=true;
	c_containedSymbol=sym;
}
void Tile::ContainItem(char sym){
	b_hasItem = true;
	c_itemSym = sym;
}
void Tile::ItemPickUp(){
	b_hasItem = false;
	c_itemSym = c_symbol;
}
void Tile::Contain()
{
	c_containedSymbol=c_symbol;
	b_hasContain=false;
}

