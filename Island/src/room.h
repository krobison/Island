#pragma once
#include <iostream>
#include <string>


class Room{
public:
	//CONSTRUCTORS
	Room() {}
	Room(int xpos, int ypos, std::string roomName,std::string roomDescription = "",std::string foreColor = "white",std::string backColor = "black") : x(xpos),y(ypos),name(roomName),description(roomDescription),fColor(foreColor),bColor(backColor) {}
	//GETTERS
	std::string getName() {return name;}
	std::string getDescription() {return description;}
	std::string getFColor() {return fColor;}
	std::string getBColor() {return bColor;}
	int getX() {return x;}
	int getY() {return y;}
	//SETTERS
	void setFColor(std::string color)					{fColor = color;}
	void setBColor(std::string color)					{bColor = color;}
	void setColors(std::string fore,std::string back)	{fColor = fore;bColor = back;}
	void setDescription(std::string d)					{description = d;}
	//OPERATORS
	friend std::ostream& operator <<(std::ostream& out,const Room& r) {return out << r.description;}
	friend bool operator ==(Room& r1,Room& r2) {return ( (r1.getX() == r2.getX() )&&(r1.getY() == r2.getY() ) );}
	friend bool operator !=(Room& r1,Room& r2) {return !(r1 == r2);}
private:
	int x,y;
	std::string name;
	std::string description;
	std::string fColor,bColor;
};