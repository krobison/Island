#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

#include "driver.h"



using namespace std;

void main() {
	Driver game;

	game.initRooms();
	game.initExits();
	game.initItems();
	game.start();
	game.printRoom();
	game.getPlayerPtr()->getCurrentRoomPtr()->setDescription(" This is a dimly lit, faded white room with no apparent windows or doors. In     fact, the entire room seems void of all objects except a dim, flickering    light bulb in the middle of the ceiling.  ");
	while (1){
		game.captureCommand();
	}
}


/*
Idea list:

need:


complete:
throw at command
add a function for confirming yes or no and call it with self kill and quit and load game, and hit self
add some non-visible room items
add a function for decrementing health and make it graphical and have it accept an argument (how much health to take away)

*/