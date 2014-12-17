
#ifndef Room_H_INCLUDED
#define Room_H_INCLUDED


class Room
{
public:
	Room(int xc, int yc, int wide, int high);

	int x() const;
	int y() const;
	int h()const;
	int w()const;
	void set_h(int new_h);
	void set_w(int new_w);
	void set_x(int new_x);
	void set_y(int new_y);

	bool inBounds();
	bool intersect(Room* Other);
	bool moreThanSixteen();
private:
	int xcoord;
	int ycoord;
	int height;
	int width;
};

#endif
