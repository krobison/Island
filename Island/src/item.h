#pragma once
#include <string>
#include <vector>


class Item {
public:
	//CONSTRUCTORS
	Item() {}
	Item(std::string iname,std::string itemArticle, int posX,int posY,bool takeable,bool playerHas) : name(iname),article(itemArticle),x(posX),y(posY),canOwn(takeable),owned(playerHas),inList(true),oiled(false),living(false) {}
	//GETTERS
	int  getX()					{return x;}
	int  getY()					{return y;}
	bool canTake()				{return canOwn;}
	bool isOwned()				{return owned;}
	std::string getName()		{return name;}
	bool isShown()				{return inList;}
	std::string getArticle()	{return article;}

	bool isOiled() {return oiled;}
	bool isAlive() {return living;}

	//SETTERS
	void setX(int pos)			{x = pos;}
	void setY(int pos)			{y = pos;}
	void setName(std::string n)	{name = n;}
	void show()					{inList = true;}
	void hide()					{inList = false;}
	void take()					{owned = true;}
	void drop(int posx,int posy);

	void setOiled(bool b)		{oiled = b;}
	void setAlive(bool b)		{living = b;}

	//OTHER
	bool checkName(std::string);
	//MSGS
	std::string msgLookAt;
	std::string msgLookAtOwned;
	std::string msgTake;
	std::string msgDrop;
	std::string msgHit;

	std::vector<std::string> alternatives;

private:
	std::string name;
	int x,y;
	bool canOwn;
	bool owned;

	bool inList;
	std::string article;

	//BEGIN RANDOM PROPERTY STUFFS
	bool oiled;
	bool living;
};