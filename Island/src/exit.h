#pragma once
#include <string>

class Exit{
public:
	//CONSTRUCTORS
	Exit();
	Exit(int xpos,int ypos,int xpos2,int ypos2,std::string d) : x(xpos),y(ypos),newX(xpos2),newY(ypos2),open(true),direction(d),success(""),fail("") {}
	//GETTERS
	int getX() {return x;}
	int getY() {return y;}
	int getX2() {return newX;}
	int getY2() {return newY;}
	std::string getDirection() {return direction;}
	bool isOpen() {return open;}
	std::string getMsgSuccess() {return success;}
	std::string getMsgFail()	{return fail;}
	//SETTERS
	void setMsg(std::string su,std::string fa);
	void toggleLock()	{open = !open;}
	void unlock()		{open = true;}
	void lock()			{open = false;}
	//OPERATORS
	friend bool operator ==(Exit& e1,Exit& e2) {return ( (e1.getX() == e2.getX() )&&(e1.getY() == e2.getY() ) );}
	friend bool operator !=(Exit& e1,Exit& e2) {return !(e1 == e2);}
private:
	int x,y;
	std::string direction;
	int newX,newY;
	bool open;
	std::string success;
	std::string fail;
};