#pragma once
#include "actions.h"

#include <string>

void checkSingle(std::string command,Player &player);
void checkDirs(std::string command,Player &player);


void checkSingle(std::string command,Player &player) {
	checkDirs(command,player);
}

void checkDirs(std::string command,Player &player) {
	if (command == "north" || command =="n") {
		action_north(player);
	}
}