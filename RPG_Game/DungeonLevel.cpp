
#include "DungeonLevel.h"


DungeonLevel::DungeonLevel()
{
	mt.seed(time(NULL));
	blankCanvas();
	createAllRooms();
	reorderLtoR();
	drawTunnels();
	paintRooms();
	addStairs();
}

vector<vector<Tile>> DungeonLevel::getDungeonMap(){return v_tiles;}
vector<vector<Tile>> * DungeonLevel::changeDungeonMap(){return &v_tiles;}

void DungeonLevel::drawTunnel(Room* one, Room* two){
	if(one->y()<=two->y()){ // room one above room two
			for(int vertMover = one->y();vertMover<=two->y();vertMover++){
				v_tiles[vertMover][one->x()].setTile('#');
			}
			for(int horizontalMover = one->x();horizontalMover<=two->x();horizontalMover++){
				v_tiles[two->y()][horizontalMover].setTile('#');
			}
		}
		else{ // room two above room one
			for(int vertMover = two->y();vertMover<=one->y();vertMover++){
				v_tiles[vertMover][two->x()].setTile('#');
			}
			for(int horizontalMover = one->x();horizontalMover<=two->x();horizontalMover++){
				v_tiles[one->y()][horizontalMover].setTile('#');
			}
		}
}

void DungeonLevel::drawTunnels(){
	for(int i =0;i<randRoom.size()-1;i++){
			drawTunnel(randRoom[i],randRoom[i+1]);	
	}
}

bool DungeonLevel::notEnoughFloorTiles(){
	int numberOfTiles=0;
	for(int i = 0; i <randRoom.size();i++){
		numberOfTiles=numberOfTiles + (randRoom[i]->x()*randRoom[i]->y());
	}
	return numberOfTiles<215;
}

void DungeonLevel::paintRooms(){
	for(int numRooms=0; numRooms<randRoom.size();numRooms++){

		for(int roomHeight=randRoom[numRooms]->y();
			roomHeight<(randRoom[numRooms]->y()+randRoom[numRooms]->h());
			roomHeight++){

			for(int roomWidth=randRoom[numRooms]->x();
				roomWidth<(randRoom[numRooms]->x()+randRoom[numRooms]->w());
				roomWidth++){

				v_tiles[roomHeight][roomWidth].setTile('.');
			}
		}
	}

}

void DungeonLevel::reorderLtoR(){ // selcetion sort with x value low to high
	int min;
	for(int i = 0; i<randRoom.size();i++){
		min=i;
		for(int j = i+1;j<randRoom.size();j++){
			if(randRoom[min]->x()>randRoom[j]->x()){
			min = j;
			}
		}
		swap(randRoom[min],randRoom[i]);
	}


}

int DungeonLevel::checkRooms(){
	int numberDeleted=0;
	int count;
	int rememberK;
	for(int j =0;j<randRoom.size();j++){
		count=0;
		for(int k = j+1;k<randRoom.size();k++){
			if(randRoom[j]->intersect(randRoom[k])){
				count++;
				rememberK=k;
			}
		}
		for(int l = 0;l<j;l++){
			if(randRoom[j]->intersect(randRoom[l])){
				count++;
				rememberK=l;
			}
		}
		if(count>0){
			if(count>1){
				randRoom.erase(randRoom.begin()+j);
				j--;
			}
			else{
				randRoom.erase(randRoom.begin()+rememberK);
			}
			numberDeleted++;
		}
	
	}
	return numberDeleted;
}

Room* DungeonLevel::createRandRoom(){
	Room* room;
	do{
		room = new Room((rand()*mt())%76,(rand()*mt())%17,((rand()*mt())%6)+7,((rand()*mt())%3)+5);
		}while(!room->moreThanSixteen() || !room->inBounds());
	return room;
}

DungeonLevel::~DungeonLevel(){
	for(int i =0; i<randRoom.size();i++){
		delete randRoom[i];
	}
}

void DungeonLevel::displayDungeonLevel()
{
	for(int height =0; height<20;height++){
		for(int width =0; width <79;width++){
			cout<<v_tiles[height][width].getTile();
		}
		cout<<endl;
	}
}

void DungeonLevel::addStairs(){
	
	int downstairX = randRoom[0]->x()+(mt()*rand())%randRoom[0]->w();// in first room
	int downstairY = randRoom[0]->y()+(mt()*rand())%(randRoom[0]->h()-1);
	int upstairX = randRoom[randRoom.size()-1]->x()+(mt()*rand())%randRoom[randRoom.size()-1]->w(); // in last room
	int upstairY = randRoom[randRoom.size()-1]->y()+(mt()*rand())%(randRoom[randRoom.size()-1]->h()-1);

	v_tiles[downstairY][downstairX].setTile('>');
	v_tiles[upstairY][upstairX].setTile('<');
}

void DungeonLevel::blankCanvas(){
	vector<Tile> Vec;
	for(int width =0; width <79;width++){
			Vec.push_back(Tile());
	}
	for(int height =0; height<20;height++){
	v_tiles.push_back(Vec);
	}

}

void DungeonLevel::createAllRooms(){
	unsigned int i_rooms=(mt()%3)+6;
	int numberDel;
	do{
		for(int i= randRoom.size(); i<i_rooms;i++){
			randRoom.push_back(createRandRoom());
		}
		numberDel = checkRooms();
		if(notEnoughFloorTiles()){
			numberDel++;
			i_rooms++;
		}
	}while(numberDel!=0);
}
