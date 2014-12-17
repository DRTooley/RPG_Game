#include "Player.h"

Player::Player()
	:Character()
{
	i_score=0;
}

Player::Player(string name,char symb,int health,int XP, int level,int score)
	:Character(name,symb,health,XP,level)
{
	i_score= score;
}
	
void Player::setXP(int newXP){
	i_score+=newXP;
	Character::setXP(newXP);
}

bool Player::isPlayer(){return true;}

void Player::attack(Character &target)
{
	target.setRemainingHealth(target.getRemainingHealth()-getAttack());
	setXP(1);
}

int Player::getScore(){return i_score;}

void Player::displayStats(){

	cout<<endl<<"Name:             "<< getName()<<endl;
	cout<< "Symbol:           "<<getSymbol()<<endl;
	cout<< "Current Score:    "<< getScore()<<endl;
	cout<< "Current Level:    "<< getLevel()<<endl;
	cout<< "Health:           "<< getHealth()<<endl;
	cout<< "Base Health:      "<<Character::getHealth()<<endl;
	cout<< "Health Remaining: "<<getRemainingHealth()<<endl;
	cout<< "Attack Power:     "<<getAttack()<<endl<<endl;
}

int Player::getAttack(){
	Weapon * pBest=NULL;
	Weapon * isWeapon=NULL;
	for(int i =0; i<v_items.size();i++){
		isWeapon = dynamic_cast<Weapon*> (v_items[i]);
		if(isWeapon != NULL && pBest==NULL)
			pBest = isWeapon;
		else if(isWeapon != NULL)
			if(isWeapon->getAttackBonus() > pBest->getAttackBonus())
				pBest = isWeapon;
	}
	if(pBest !=NULL)
		return pBest->getAttackBonus()+Character::getAttack();
	return Character::getAttack();
}

void Player::usePotion(){
	Consumable * isPotion=NULL;
	for(int i =0; i<v_items.size();i++){
		isPotion = dynamic_cast<Consumable*> (v_items[i]);
		if(isPotion != NULL){
			setRemainingHealth(getRemainingHealth()+getLevel()*7);
			if(getRemainingHealth()>getHealth())
				setRemainingHealth(getHealth());
			auto it = v_items.begin();
			delete v_items[i];
			v_items.erase(it+i);
			return;
		}
	}
	

}

int Player::Movement(DungeonLevel * DL, vector<Item*>& DLitems){
	char direction;
	Tools Tool;

	bool NotAcceptable=true;
	if(getRemainingHealth()<getHealth()) //slowly heals
		setRemainingHealth(getRemainingHealth()+1);
	
	do{
	cout<< "Enter Direction (WASD): ";
	cin>> direction;
	cin.ignore(200, '\n');
	if (cin.fail()){
		cin.clear();
		cout <<"That is not a valid direction, please enter W,S,A or D." <<endl<<endl;
	}
	else if(direction == 'w' || direction == 'W' ||direction == 'a' || direction == 'A' ||direction == 'S' || direction == 's' ||direction == 'd' || direction == 'D' ){
		NotAcceptable=false;
	}
	else if(direction == 'p' || direction == 'P')
		pickUp(DL,DLitems);
	else if(direction == 'e' || direction == 'E')
		dropList(DL,DLitems);
	else if(direction == 'x' || direction == 'X')
		displayStats();
	else if(direction == 'u' || direction =='U')
		usePotion();
	cout<<endl<<endl;
	}while(NotAcceptable);
	bool hadMove = true;
	vector<vector<Tile>> *Changeable = DL->changeDungeonMap();
	(*Changeable)[getYC()][getXC()].Contain();
	if(direction == 'd' || direction == 'D' ){
		//cout<<"("<<getXC()+1<<","<<getYC()<<")"<<endl;
		setXC(DL,getXC()+1);
	}

	else if(direction == 'w' || direction == 'W' ){
		//cout<<"("<<getXC()<<","<<getYC()-1<<")"<<endl;
		setYC(DL,getYC()-1);

	}
	else if(direction == 'a' || direction == 'A'){
		//cout<<"("<<getXC()-1<<","<<getYC()<<")"<<endl;
		setXC(DL,getXC()-1);
	}

	else if(direction == 'S' || direction == 's'){
		//cout<<"("<<getXC()<<","<<getYC()+1<<")"<<endl;
		setYC(DL,getYC()+1);
	}
	else
		hadMove = false;
	
	if((*Changeable)[getYC()][getXC()].getUnderTile() =='<' && hadMove)
	{
		return -1;
	}
	else if((*Changeable)[getYC()][getXC()].getUnderTile() =='>' && hadMove)
	{
		return 1;
	}
	else
	{
		(*Changeable)[getYC()][getXC()].Contain(getSymbol());
		return 0;
	}
	
}

void Player::pickUp(DungeonLevel *DL, vector<Item*> DLitems){
	if((*DL->changeDungeonMap())[getYC()][getXC()].hasItem()){
		for(auto it = DLitems.begin();it!=DLitems.end();it++){
			int itemX = (*it)->getXC();
			int itemY = (*it)->getYC();
			if(itemX == getXC() && itemY == getYC()){
				(*it)->pickUp(this);//marked to be removed from the DL's item list
				(*DL->changeDungeonMap())[itemY][itemX].ItemPickUp();
				v_items.push_back((*it));
				cout<<endl<<(*it)->getName()<<" has been put into your inventory!"<<endl<<endl;
			}
		}
	}

}

void Player::dropList(DungeonLevel *DL, vector<Item*> &DLitems){
	int vecPos =0;
	if(v_items.empty()){
		cout<<"You are not carrying any items!"<<endl;
		return;
	}
	cout<<"To drop the item enter the corresponding integer value."<<endl;
	for(auto it = v_items.begin();it!=v_items.end();it++){
		cout<<vecPos<<": "<<(*it)->getName()<<endl;
		vecPos++;
	}
	cout<<"To cancel enter -1"<<endl;
	int input; bool badInput =true;
	do{
		cout<< "Enter item number: ";
		cin>> input;
		if (cin.fail()){
			cin.clear();
			cin.ignore(200,'\n');
			cout <<"That is not a valid integer. Acceptable values are between -1 and "<<vecPos-1 <<endl<<endl;
		}
		else if(input >=-1 && input <vecPos){
			if(input == -1)
				return;
			drop(DL,DLitems,v_items[input]);
			badInput=false;
		}
		else
			cout<< "That is not an acceptable number."<<endl;
	}while(badInput);

}

void Player::drop(DungeonLevel *DL, vector<Item*> &DLitems, Item* dropMe){
	(*DL->changeDungeonMap())[getYC()][getXC()].ContainItem(dropMe->getSymbol());
	dropMe->drop();
	DLitems.push_back(dropMe);
	for(auto it=v_items.begin();it!=v_items.end();it++){
		if((*it) == dropMe){
			v_items.erase(it);
			break;
		}
	} 
}

int Player::getHealth(){
	//automatically selects the strongest armor in your inventory and uses it.
	Armor * pBest=NULL;
	Armor * isArmor=NULL;
	for(int i =0; i<v_items.size();i++){
		isArmor = dynamic_cast<Armor*> (v_items[i]);
		if(isArmor != NULL && pBest==NULL)
			pBest = isArmor;
		else if(isArmor != NULL)
			if(isArmor->getDefenseBonus() > pBest->getDefenseBonus())
				pBest = isArmor;
	}
	if(pBest !=NULL)
		return Character::getHealth() + pBest->getDefenseBonus();
	return Character::getHealth();
}

void Player::dumpObject()
{
	cout<< "Player:"<<endl;
	dumpObjectData();
}

void Player::dumpObjectData()
{
	Character::dumpObjectData();
	
}

void Player::writeFragment(ostream & output)
{
	output<<" <Player>" <<endl;
	writeDataAsFragment(output);
	output<< " </Player>"<<endl;
}

void Player::writeDataAsFragment(ostream & output)
{
	Character::writeDataAsFragment(output);
	
}

void Player::setElementData(string sElementName, string sValue)
{
	Character::setElementData(sElementName,sValue);
	
}
