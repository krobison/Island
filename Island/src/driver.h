#pragma once
#include <vector>
#include "player.h"
#include "room.h"
#include "exit.h"
#include "item.h"

class Driver{
public:
	Driver() : itWord("") {}
	void initRooms();
	void initExits();
	void initItems();
	void start();
	void death(std::string diemsg);
	Room getRoom(int x,int y);
	int getRoomIndex(int x,int y);
	Exit getExit(int x,int y,std::string dir);
	Player getPlayer() {return player;}
	Player* getPlayerPtr() {return &player;}

	bool itemIsHere(Item i);
	bool itemIsOwned(Item i);

	bool checkLiving();
	int getAnyCharacterIndex();


	void addToInventory(Item i);
	void removeFromInventory(Item i);

	void hurtPlayer(int amount);

	bool yesNo();

	void printRoom();
	void captureCommand();
	std::string getIntro();

	std::string stripStupid(std::string string);
	std::string stripStupidAfterPreposition(std::string string);
	std::string replaceIt(std::string string);


	//####INTERPRETER####//
		bool interpreter_checkSingle(std::string command);
			bool interpreter_checkDirections(std::string command);
			bool interpreter_checkBasic(std::string command);
			bool interpreter_checkSwear(std::string command);
		bool interpreter_checkShort(std::string command);
			bool interpreter_checkPhrases(std::string command);
		bool interpreter_checkLong(std::string command);
			bool interpreter_checkVerb(std::string command);
			bool interpreter_checkTwoVerb(std::string command);
			bool interpreter_checkPreposition(std::string command);
	//####ACTIONS####//
		void actions_north();
		void actions_south();
		void actions_east();
		void actions_west();

		void actions_look(std::string target);
			void actions_look_at(std::string target);
		void actions_stats();
		void actions_clear();
		void actions_quit();
		void actions_inventory();

		void actions_kill(std::string target);
			void actions_kill_object(std::string target,std::string with);
			void actions_kill_self(std::string msg);

		void actions_go(std::string target);

		void actions_swear();

		void actions_take(std::string target);
			void actions_pick_up(std::string target) {actions_take(target);}

		void actions_drop(std::string target);
			void actions_set_down(std::string target)	{actions_drop(target);}
			//void actions_put_down(std::string target)	{actions_drop(target);}		(taken care of in verb checking)
			//void actions_drop_down(std::string target)	{actions_drop(target);} (taken care of in verb checking)

		void actions_throw(std::string target);
		void actions_throw_at(std::string target,std::string weapon);

		void actions_hit(std::string target);
		void actions_hit_with(std::string target,std::string weapon);

		void actions_turn(std::string target);

		void actions_say(std::string text);
		void actions_say_to(std::string text,std::string target);

		//####TRIGGERS####//

		bool check_triggers_null();
		bool check_triggers_commands(std::string target);

		//###FILEIO###//
		void saveFile();
		void loadFile(std::string target);


private:
	std::vector<Room> rooms;
	std::vector<Exit> exits;
	std::vector<Item> inventory;
	std::vector<Item> objects;

	std::string itWord;

	Player player;
};

