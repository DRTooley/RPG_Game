#ifndef Tile_H_INCLUDED
#define Tile_H_INCLUDED




class Tile{
public:
	Tile();
	Tile(char symbol);
	~Tile();
	char getUnderTile();
	char getTile();
	void setTile(char newSymbol);
	void Contain( char sym);
	void Contain();
	bool hasCharacter();
	char getItem();
	void ContainItem(char sym);
	void ItemPickUp();
	bool hasItem();
private:
	char getContained();
	char c_symbol;
	char c_containedSymbol;
	bool b_hasContain;
	bool b_hasItem;
	char c_itemSym;
};
#endif