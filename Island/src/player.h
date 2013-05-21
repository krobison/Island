#pragma once
#include "room.h"


class Player{
public:
	//CONSTRUCTORS
	Player() : health(100),thirst(100),name(""),score(0),turns(0) {}
	Player(std::string playerName,Room startingRoom,double playerHealth = 100,double playerThirst = 100) : name(playerName),currentRoom(startingRoom),health(playerHealth),thirst(playerThirst) {}
	//GETTERS
	std::string getName()	{return name;}
	Room getCurrentRoom()	{return currentRoom;}
	Room* getCurrentRoomPtr()	{return &currentRoom;}
	double getHealth()		{return health;}
	double getThirst ()		{return thirst;}
	double getScore	 ()		{return score;}
	double getTurns	 ()		{return turns;}
	//SETTERS
	void setName(std::string n) {name = n;}
	void setRoom(Room r) {currentRoom = r;}
	void setHealth(double x)			 {health = x;}
	void setThirst(double x)			 {thirst = x;}
	void addScore (double x)			 {score += x;}
	void addTurn()						 {turns ++;}
	void hurt(double x)					 {health -= x;}

	void setScore (double x)	{score = x;}
	void setTurns (double x)	{turns = x;}
	//OPERATORS
private:
	std::string name;
	Room currentRoom;
	double health,thirst;
	double score, turns;

};