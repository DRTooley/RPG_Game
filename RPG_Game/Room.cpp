
#include "Room.h"


Room::Room(int xc, int yc, int wide, int high)
	: xcoord(xc), ycoord(yc), height(high),width(wide){}
int Room::x() const{return xcoord;}
int Room::y() const{return ycoord;}
int Room::h()const{return height;}
int Room::w()const{return width;}
void Room::set_x(int new_x){xcoord = new_x;}
void Room::set_y(int new_y){ycoord = new_y;}
void Room::set_h(int new_h){height = new_h;}
void Room::set_w(int new_w){width=new_w;}

bool Room::intersect(Room * Other)
{
	bool AboveAndBelow = Other->y()<=ycoord && (Other->y()+Other->w())>=(ycoord+width);
	bool ShareYcoord = ((Other->y() >=ycoord)&&Other->y()<=(ycoord+height))||(((Other->y()+Other->h()) >=ycoord)&&(Other->y()+Other->h())<=(ycoord+height));

	if((Other->x()>=xcoord)&&(Other->x()<=(xcoord+width+1))&& // if other top left is inside of current
		(Other->y()>=ycoord)&&(Other->y()<=(ycoord+height+1)))
		return true;
	else if((xcoord+width+1)>=Other->x()&&Other->x()>=xcoord&& //if other bottom left is inside of current
		ycoord<=(Other->y()+Other->h())&&(ycoord+height+1)>=(Other->y()+Other->h()))
		return true;
	else if(Other->x()<=xcoord&&(Other->x()+Other->w())>=(xcoord+width)&&
		(AboveAndBelow||ShareYcoord))
		return true;
	else 
		return false;
}

bool Room::inBounds()
{
	if((xcoord+width)<79 &&(ycoord+height)<20)
		return true;
	else
		return false;
}

bool Room::moreThanSixteen()
{
	if((width*height)>=16)
		return true;
	else
		return false;
}