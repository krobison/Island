#include "driver.h"
#include "K_formatting.h"
#include "K_colors.h"
#include "K_msg_constants.h"
#include <vector>
#include <sstream>
#include <fstream>

void Driver::initRooms() {
	Room r_default(0,0,"default","Ifyousee this you are in a bad place");
		r_default.setColors("white","black");
		rooms.push_back(r_default);
	//50,50
	Room r_start(50,50,"Dull Room"," You wake up with your face pressed hard against the concrete floor. You open   your eyes to find yourself in a dimly lit, faded white room with no apparent windows or doors. There is a flickering light bulb in the middle of the      ceiling. You don't know how you got here, or where here really is, but you    have a bad feeling about it.  ");
		r_start.setColors("black","gray");
		rooms.push_back(r_start);
	//50,49
	Room r_hallway(50,49,"Hallway"," You step out into a hallway that stretches to the east and west. Long          ceiling lights emit a greenish glow. Large plastic pipes are running the    length of the hallway.  ");
		r_hallway.setColors("black","green");
		rooms.push_back(r_hallway);

}
void Driver::initExits() {
	Exit e(0,0,50,49,"");
		e.setMsg("You go north","It is locked");
		exits.push_back(e);
	//50,50
	Exit e1(50,50,50,49,"north");
		e1.setMsg("You go north",fmsg_godir);
		e1.lock();
		exits.push_back(e1);
	//50,49
	Exit e2(50,49,50,50,"south");
		exits.push_back(e2);
}
void Driver::initItems() {
	//###### 50 , 50 ######
		Item i_rock("rock","A",50,50,true,false);
			i_rock.msgLookAt						= "It is an ordinary gray rock.";
			i_rock.msgTake							= "You pick the rock up.";
			i_rock.msgDrop							= "You drop the rock.";
			i_rock.msgLookAtOwned					= "You have a baseball size gray rock in your hand.";
			i_rock.msgHit							= "You dont want to hurt your hand.";
			i_rock.alternatives.push_back("grey rock");
			i_rock.alternatives.push_back("gray rock");
			objects.push_back(i_rock);
		Item i_lightbulb("lightbulb","A",50,50,false,false);
			i_lightbulb.hide();
			i_lightbulb.msgLookAt						= "It is so dim it doesn't hurt the eye to look at.";
			i_lightbulb.msgTake							= "You reach for it, but the bulb burns your fingers.";
			i_lightbulb.msgDrop							= "";
			i_lightbulb.msgLookAtOwned					= "";
			i_lightbulb.msgHit							= "You don't want to injure your hand.";
			i_lightbulb.alternatives.push_back("light bulb");
			i_lightbulb.alternatives.push_back("light");
			i_lightbulb.alternatives.push_back("bulb");
			objects.push_back(i_lightbulb);
		Item i_wall5050("wall","A",50,50,false,false);
			i_wall5050.hide();
			i_wall5050.msgLookAt						= "It is a faded white color";
			i_wall5050.msgTake							= "You do not yet posses the ability to carry walls.";
			i_wall5050.msgDrop							= "";
			i_wall5050.msgLookAtOwned					= "";
			i_wall5050.msgHit							= "You don't want to injure your hand.";
			i_wall5050.alternatives.push_back("side");
			objects.push_back(i_wall5050);
		Item i_floor5050("floor","the",50,50,false,false);
			i_floor5050.hide();
			i_floor5050.msgLookAt						= "It is concrete and dirty";
			i_floor5050.msgTake							= "That is just silly.";
			i_floor5050.msgDrop							= "";
			i_floor5050.msgLookAtOwned					= "";
			i_floor5050.msgHit							= "You don't want to injure your hand.";
			i_floor5050.alternatives.push_back("ground");
			i_floor5050.alternatives.push_back("concrete");
			objects.push_back(i_floor5050);
		Item i_valve("valve","a",50,49,false,false);
			i_valve.msgLookAt							= "There is a bright red valve sticking out of a pipe.";
			i_valve.msgTake								= "It is firmly fastened to the pipe.";
			i_valve.msgDrop								= "";
			i_valve.msgLookAtOwned						= "";
			i_valve.msgHit								= "You may want to try turning it instead.";
			i_valve.alternatives.push_back("wheel");
			i_valve.alternatives.push_back("red wheel");
			i_valve.alternatives.push_back("red valve");
			objects.push_back(i_valve);
}

void Driver::start() {
	setColor("red","gray");
	cout << getIntro();

	cout << string(2,'\n');

	setColor("gray","black");
	cout << cmsg_name;

	string name;
	getline(std::cin,name);
	if (name == "quit") {exit(1);}

	player.setName(name);
	player.setRoom(getRoom(50,50));
	system("cls");
}

void Driver::saveFile(){

	std::string file1 =(player.getName()+".dat1");
	std::string file2 = (player.getName()+".dat2");
	ofstream file_save1(file1.c_str());
	ofstream file_save2(file2.c_str());
	if (!file_save1){
		cout << "error writing to save file 1."<<endl;
		exit(4);
	}
	if (!file_save2){
		cout << "error writing to save file 2."<<endl;
			exit(4);
	}

	file_save1 << player.getName() << "\t" 
		<< player.getHealth() << "\t" 
		<< player.getThirst() << "\t" 
		<< player.getScore() << "\t" 
		<< player.getTurns() << "\t"
		<< player.getCurrentRoom().getX()<<"\t"<<player.getCurrentRoom().getY()<<"\n";
	for (size_t i = 0;i<inventory.size();i++){
		file_save2 << inventory[i].getName()<<"\t";
	}
	cout << "File Saved as '"<<player.getName()<<"'. Use load + your file name in order to load it.";
}

void Driver::loadFile(std::string target){
	std::string file1 =(target+".dat1");
	std::string file2 = (target+".dat2");
	ifstream file_save1(file1.c_str());
	ifstream file_save2(file2.c_str());

	if (!file_save1){
		cout << "error reading from save file 1."<<endl;
		exit(5);
	}
	if (!file_save2){
		cout << "error reading from save file 1."<<endl;
		exit(5);
	}
	double load_health, load_thirst, load_score, load_turns;
	int load_x,load_y;
	vector<std::string> load_inv;
	file_save1 >> load_health >> load_thirst >> load_score >> load_turns >> load_x >> load_y;
	std::string temp;
	while (file_save2 >> temp){
		load_inv.push_back(temp);
	}


	for (size_t i = 0;i<inventory.size();i++){
		inventory.erase(inventory.begin()+i);
	}
	for (size_t i = 0;i<rooms.size();i++){
		rooms.erase(rooms.begin()+i);
	}
	for (size_t i = 0;i<exits.size();i++){
		exits.erase(exits.begin()+i);
	}
	for (size_t i = 0;i<objects.size();i++){
		objects.erase(objects.begin()+i);
	}
	itWord = "";




	player.setName(target);

	player.setHealth(load_health);
	player.setThirst(load_thirst);

	player.setScore(load_score);
	player.setTurns(load_turns);

	initItems();
	initRooms();
	initExits();

	player.setRoom(getRoom(load_x,load_y));

	for (size_t i = 0;i<load_inv.size();i++){
		for (size_t j = 0;j<objects.size();j++){
			if (load_inv[i] == objects[i].getName()){
				inventory.push_back(objects[i]);
				objects[i].take();
			}
		}
	}

	actions_clear();
	printRoom();

	cout << "\nFile Loaded!";
}

void Driver::death(std::string diemsg){
	cout << diemsg << endl;
	setColor("black","light red");
	string temp;
	addShade(temp,"dark",WIDTH);
	addBlankBorder(temp,"dark");
	addCenteredText(temp,dmsg_dead,true);
	addBlankBorder(temp,"dark");
	addShade(temp,"dark",WIDTH);
	cout <<temp;
	resetColor();
	system("pause");
	exit(1);
}

std::string Driver::getIntro() {
	string intro = "";
	addShade(intro,"dark",WIDTH);
	addBlankBorder(intro,"dark");
	addCenteredText(intro,"WELCOME DARING ADVENTURER!",true);
	addBlankBorder(intro,"dark");
	addCenteredText(intro,"Before you lies a daunting quest of danger, humor, and reward.",true);
	addCenteredText(intro,"Only the bravest adventurers will pass the tests and survive.",true);
	addBlankBorder(intro,"dark");
	addShade(intro,"dark",WIDTH);
	return intro;
}

Room Driver::getRoom(int x,int y) {
	for (std::size_t i = 0;i<rooms.size();i++) {
		if ( (rooms[i].getX() == x)&&(rooms[i].getY() == y) ) {
			return rooms[i];
		}
	}
	return rooms[0];
}
int Driver::getRoomIndex(int x,int y) {
	for (std::size_t i = 0;i<rooms.size();i++) {
		if ( (rooms[i].getX() == x)&&(rooms[i].getY() == y) ) {
			return i;
		}
	}
	return 0;
}
Exit Driver::getExit(int x,int y,std::string dir) {
	for (std::size_t i = 0;i<exits.size();i++) {
		if ( (exits[i].getX() == x)&&(exits[i].getY() == y)&&(exits[i].getDirection() ==dir) ) {
			return exits[i];
		}
	}
	return exits[0];
}

bool Driver::checkLiving(){
	for (size_t i = 0; i <objects.size(); i++){
		if (itemIsHere(objects[i]) ) {
			if (objects[i].isAlive()){
				return true;
			}
		}
	}
	return false;
}

int Driver::getAnyCharacterIndex() {
	for (size_t i = 0; i <objects.size(); i++){
		if (itemIsHere(objects[i]) ) {
			if (objects[i].isAlive()){
				return i;
			}
		}
	}
	return 0;
}

bool Driver::itemIsHere(Item i) {
	if (i.getX() == player.getCurrentRoom().getX() && i.getY() == player.getCurrentRoom().getY()) {
		return true;
	}
	else{
		return false;
	}
}
bool Driver::itemIsOwned(Item i) {
	for (std::size_t a = 0;a<inventory.size();a++) {
		if (inventory[a].getName() == i.getName()) {
			return true;
		}
	}
	return false;
}

bool Driver::yesNo() {
	string answer = " ";
	while (answer[0] != 'y' && answer[0] != 'n') {
		cout << cmsg_general_question;
		cin >> answer;
		for (std::size_t i = 0;i< answer.length();i++) {
			answer[i] = tolower(answer[i]);
		}
		string nothingland;
		getline(std::cin,nothingland);
		continue;
	}
	if (answer[0] == 'y' || answer[0] == 'Y') {
		return true;
	}
	return false;
}

void Driver::hurtPlayer(int amount){
	std::string temp;
	cout <<endl;
	stringstream test; 
	player.hurt(amount);
	test << "You have lost " << amount << " health points";
	addCenteredText(temp,test.str());
	setColor("red","blue");
	cout << temp;
	temp = "";
	stringstream test2;
	if (player.getHealth() > 0) {
		test2 << "You have " << player.getHealth() << " health points remaining.";
		addCenteredText(temp,test2.str());
		cout << temp;
		resetColor();
	}
	else {
		resetColor();
		death("");
	}
}

void Driver::addToInventory(Item i){
	inventory.push_back(i);
}
void Driver::removeFromInventory(Item i){
	for(std::size_t a = 0;a< inventory.size();a++){
		if (inventory[a].getName() == i.getName()) {
			inventory.erase(inventory.begin()+a);
		}
	}
}

void Driver::printRoom() {
	string temp;
	Room tempRoom(player.getCurrentRoom());

	setColor(tempRoom.getFColor(),tempRoom.getBColor());

	addShade(temp,"dark",WIDTH);
	addCenteredText(temp,tempRoom.getName(),true);
	addBlankBorder(temp,"dark");
	addCenteredText(temp,tempRoom.getDescription(),true);
	addBlankBorder(temp,"dark");

	addLeftText(temp,dmsg_inroom,"dark");
	addBlankBorder(temp,"dark");
	int counter = 0;
	for(std::size_t i = 0;i<objects.size();i++){
		if(objects[i].getX()==player.getCurrentRoom().getX() && objects[i].getY()==player.getCurrentRoom().getY() && objects[i].isOwned() == false && objects[i].isShown()) {
			addLeftText(temp,objects[i].getArticle()+' '+objects[i].getName(),"dark");
			counter++;
		}
	}
	if (counter == 0){
		addLeftText(temp,"Nothing","dark");
	}

	addShade(temp,"dark",WIDTH);

	temp.erase(temp.length()-1,1);
	cout << temp;
	setColor("grey","black");
}

void Driver::captureCommand() {

	cout << string(2,'\n');
	setColor("grey","black");
	cout << cmsg_command;
	string command;
	getline(std::cin,command);
	for (std::size_t i = 0;i< command.length();i++) {
		command[i] = tolower(command[i]);
	}

	command = stripStupid(command);
	command = replaceIt(command);

if (!check_triggers_null() && !check_triggers_commands(command)){
	bool valid = false;
	if (interpreter_checkSingle(command) ){
		valid = true;
	}
	else if (interpreter_checkShort(command)) {
		valid = true;
	}
	else if (interpreter_checkLong(command)) {
		valid = true;
	}
	
	if (command != ""){
		if (!valid){
			cout <<cfmsg_noCommand;
		}
		else {
			player.addTurn();
		}
	}
}
}

std::string Driver::stripStupid(std::string string) {
	vector<std::string> badList;
	badList.push_back(" to ");
	badList.push_back(" and ");
	badList.push_back(" the ");
	badList.push_back(" my ");
	badList.push_back(" a ");
	//badList.push_back(" at ");

	int testValue;

	for (std::size_t i = 0;i< badList.size();) {
		testValue = string.find(badList[i]);
		if (testValue != -1) {
			string.erase(testValue,badList[i].length()-1);
		}
		else { i++; }
	}

	vector<std::string> punctuation;
	punctuation.push_back(".");
	punctuation.push_back("!");
	punctuation.push_back(",");
	punctuation.push_back("?");

	for (std::size_t i = 0;i< punctuation.size();) {
		testValue = string.find(punctuation[i]);
		if (testValue != -1) {
			string.erase(testValue,1);
		}
		else { i++; }
	}

	return string;
}
std::string Driver::replaceIt(std::string string){
	
	int pos = string.find(" it ");
	while (pos != string::npos){
		pos = string.find(" it ");
		if (pos == string::npos){break;}
		string.replace(pos+1,2,itWord);
	}
	pos = string.find(" it");
	if (pos == string::npos){return string;}
	if (string.length() == pos+3) {
		string.replace(pos+1,2,itWord);
	}
	return string;

}

//############################################################################
//############################################################################
//############################################################################
bool Driver::interpreter_checkSingle(std::string command) {
	if (	 interpreter_checkDirections(command)		 ) {
		return true;
	}
	else if (	 interpreter_checkBasic(command)			){
		return true;
	}
	else if (	 interpreter_checkSwear(command)			){
		return true;
	}
	else
		return false;
}
bool Driver::interpreter_checkShort(std::string command) {
	if (	 interpreter_checkPhrases(command)		 ){
		return true;
	}
	else
		return false;
}
bool Driver::interpreter_checkLong(std::string command) {
	if (		interpreter_checkPreposition(command)		) {
		return true;
	}
	else if (		interpreter_checkTwoVerb(command)		) {
		return true;
	}
	else if (		interpreter_checkVerb(command)		) {
		return true;
	}
	else {
		return false;
	}
}

bool Driver::interpreter_checkDirections(std::string command) {
	if (command == "north" || command =="n") {
		actions_north();
		return true;
	}
	else if (command == "south" || command =="s") {
		actions_south();
		return true;
	}
	else if (command == "west" || command =="w") {
		actions_west();
		return true;
	}
	else if (command == "east" || command =="e") {
		actions_east();
		return true;
	}
	else 
		return false;
}
bool Driver::interpreter_checkBasic(std::string command) {
	if (command == "look" || command =="l") {
		actions_look("room");
		return true;
	}
	else if (command == "stat" || command == "stats" || command =="st") {
		actions_stats();
		return true;
	}
	else if (command == "clear" || command == "cl" || command =="cls" || command == "clean" || command =="wipe") {
		actions_clear();
		return true;
	}
	else if (command == "exit" || command == "quit" || command == "q") {
		actions_quit();
		return true;
	}
	else if (command == "inventory" || command == "inv" || command == "i" || command == "in") {
		actions_inventory();
		return true;
	}
	else if (command == "kill" || command == "murder") {
		actions_kill("");
		return true;
	}
	else if (command == "save" || command == "save game" ||command == "s") {
		saveFile();
		return true;
	}
	else 
		return false;
}
bool Driver::interpreter_checkSwear(std::string command) {
	if (command == "fuck"		|| 
		command == "shit"		||
		command == "piss"		||
		command == "bitch"		||
		command == "ass"		||
		command == "asshole"	||
		command == "tits"		||
		command == "cock"		||
		command == "dick"		||
		command == "whore"		||
		command == "slut"		||
		command == "nigger"		||
		command == "fucker"		||
		command == "fucking"	||
		command == "bastard"	||
		command == "fagot"		||
		command == "fag"		||
		command == "pussy"		||
		command == "cunt") {
		actions_swear();
		return true;
	}
	else 
		return false;
}

bool Driver::interpreter_checkPhrases(std::string command) {
	if (command == "look around" ||command ==  "where am i" ||command ==  "what room" ||command ==  "room" ||command ==  "where am i?" ||command ==  "glance around") {
		actions_look("room");
		return true;
	}
	else if (command == "clear screen" || command == "clean screen" || command == "wipe screen") {
		actions_clear();
		return true;
	}
	else 
		return false;
}
bool Driver::interpreter_checkVerb(std::string command) {
	int pos = command.find_first_of(' ');
	std::string verb = command.substr(0,pos);
	std::string remainder = command.substr(pos+1,command.length()-(pos+1) );
	if (verb == "go") {
		actions_go(remainder);
		return true;
	}
	else if (verb == "look") {
		actions_look(remainder);
		return true;
	}
	else if (verb == "take"||verb == "grab"||verb == "get") {
		actions_take(remainder);
		return true;
	}
	else if (verb == "drop") {
		actions_drop(remainder);
		return true;
	}
	else if (verb == "load") {
		loadFile(remainder);
		return true;
	}
	else if (verb == "hit"||verb == "whack"||verb == "knock"||verb == "punch"||verb=="smash") {
		actions_hit(remainder);
		return true;
	}
	else if (verb == "throw" || verb == "toss"){
		actions_throw(remainder);
		return true;
	}
	else if (verb == "turn"||verb == "twist"||verb == "rotate"){
		actions_turn(remainder);
		return true;
	}
	else if (verb == "say"){
		actions_say(remainder);
		return true;
	}
	else{
		return false;
	}
}
bool Driver::interpreter_checkTwoVerb(std::string command) {
	int pos = command.find_first_of(' ');
	std::string verb = command.substr(0,pos);
	std::string remainder = command.substr(pos+1,command.length()-(pos+1) );
	pos = remainder.find_first_of(' ');
	std::string verbTwo = remainder.substr(0,pos);
	remainder = remainder.substr(pos+1,remainder.length()-(pos+1) );

	if (verb == "look"){
		if (verbTwo == "at") {
			actions_look_at(remainder);
			return true;
		}
		else {
			return false;
		}
	}
	else if (verb == "pick"){
		if (verbTwo == "up") {
			actions_pick_up(remainder);
			return true;
		}
		else {
			return false;
		}
	}
	else if (verb == "kill" || verb == "murder"){
		actions_kill("THISISAHIDDENMESSAGE");
		return true;
	}


	else if (verbTwo == "down"){
		if (verb == "set"||verb == "put"||verb == "drop") {
			actions_set_down(remainder);
			return true;
		}
		else {
			return false;
		}
	}


	else{
		return false;
	}
}
bool Driver::interpreter_checkPreposition(std::string command) {
	std::string preposition = "";
	std::vector<std::string> prepositions;
	prepositions.push_back("with");
	prepositions.push_back("up");
	prepositions.push_back("down");
	prepositions.push_back("at");

	int pos = command.find_first_of(' ');
	std::string verb = command.substr(0,pos);
	std::string remainder = command.substr(pos+1,command.length()-(pos+1) );

	bool found = false;
	for (std::size_t i = 0;i<prepositions.size();i++){
		if (remainder.find(prepositions[i]) != string::npos) {
			if (command[command.find(prepositions[i])-1] == ' '){	//check if char before is a space
				if ((remainder.length() == remainder.find(prepositions[i])+prepositions[i].length())) {	//check if char after is a space or that the prep is the last word of the string (both acceptable)
					pos = remainder.find(prepositions[i]);
					preposition = remainder.substr(pos,prepositions[i].length());
					//remainder = remainder.substr(pos+prepositions[i].length()+1,remainder.length()-(pos+prepositions[i].length()+1));
					found = true;
					break;
				}
				else if (remainder[remainder.find(prepositions[i])+prepositions[i].length()] == ' ') {
					pos = remainder.find(prepositions[i]);
					preposition = remainder.substr(pos,prepositions[i].length());
					//remainder = remainder.substr(pos+prepositions[i].length()+1,remainder.length()-(pos+prepositions[i].length()+1));
					found = true;
					break;
				}
			}
		}
	}
	if (!found){ return false;}

	if ((command.find(preposition)-verb.length()-2) > 256 ) {return false;}

	std::string after;

	std::string between = command.substr(verb.length()+1,command.find(preposition)-verb.length()-2);
	if ( (command.length()-command.find(preposition)-preposition.length()-1) > 256 ) {
		after = "";
	}
	else {
		after = command.substr(command.find(preposition)+preposition.length()+1,command.length()-command.find(preposition)-preposition.length()-1);
	}




	if ( (verb == "kill" || verb == "murder")&& (preposition == "with") ){
		actions_kill_object(between,after);
		return true;
	}
	else if ( (verb == "hit"||verb == "whack"||verb == "knock"||verb == "punch"||verb=="smash")&& (preposition == "with") ){
		if (after == "hand" || after == "fist" || after == "self" || after == "arm" || after == "hands" || after == "fists"){
			actions_hit(between);
			return true;
		}
		actions_hit_with(between,after);
		return true;
	}
	else if ( (verb == "throw" || verb == "toss") && (preposition == "at")) {
		actions_throw_at(after,between);
		return true;
	}
	else if ( (verb == "pick"||verb == "take")&&(preposition == "up")){
		actions_take(between);
		return true;
	}
	else if ( (verb == "set"||verb == "put"||verb == "lay"||verb == "drop")&&(preposition == "down")){
		actions_drop(between);
		return true;
	}
	else if ( (verb == "say")&&(preposition == "at")){
		actions_say_to(between,after);
		return true;
	}
	else{
		return false;
	}
}
//############################################################################
//############################################################################
//############################################################################
void Driver::actions_north() {
	Room room = getRoom(player.getCurrentRoom().getX(),player.getCurrentRoom().getY() );
	Exit exit = getExit(player.getCurrentRoom().getX(),player.getCurrentRoom().getY(),"north");
	if ( (room != rooms[0])&&(exit != exits[0]) ){
		if(exit.isOpen()) {
			if (exit.getMsgSuccess() != ""){
				cout <<exit.getMsgSuccess()<<endl<<endl;}
			else{
				cout <<emsg_north<<endl<<endl;
			}
			player.setRoom(getRoom(exit.getX2(),exit.getY2()));
			printRoom();
		}
		else{
			if (exit.getMsgSuccess() != "") {
				cout <<exit.getMsgFail();
			}
			else {
				cout <<emsg_fail;
			}
		}
	}
	else {
		cout << fmsg_godir;
	}
}
void Driver::actions_south() {
	Room room = getRoom(player.getCurrentRoom().getX(),player.getCurrentRoom().getY() );
	Exit exit = getExit(player.getCurrentRoom().getX(),player.getCurrentRoom().getY(),"south");
	if ( (room != rooms[0])&&(exit != exits[0]) ){
		if(exit.isOpen()) {
			if (exit.getMsgSuccess() != ""){
				cout <<exit.getMsgSuccess()<<endl<<endl;}
			else{
				cout <<emsg_south<<endl<<endl;
			}
			player.setRoom(getRoom(exit.getX2(),exit.getY2()));
			printRoom();
		}
		else{
			if (exit.getMsgSuccess() != "") {
				cout <<exit.getMsgFail();
			}
			else {
				cout <<emsg_fail;
			}
		}
	}
	else {
		cout << fmsg_godir;
	}
}
void Driver::actions_east() {
	Room room = getRoom(player.getCurrentRoom().getX(),player.getCurrentRoom().getY() );
	Exit exit = getExit(player.getCurrentRoom().getX(),player.getCurrentRoom().getY(),"east");
	if ( (room != rooms[0])&&(exit != exits[0]) ){
		if(exit.isOpen()) {
			if (exit.getMsgSuccess() != ""){
				cout <<exit.getMsgSuccess()<<endl<<endl;}
			else{
				cout <<emsg_east<<endl<<endl;
			}
			player.setRoom(getRoom(exit.getX2(),exit.getY2()));
			printRoom();
		}
		else{
			if (exit.getMsgSuccess() != "") {
				cout <<exit.getMsgFail();
			}
			else {
				cout <<emsg_fail;
			}
		}
	}
	else {
		cout << fmsg_godir;
	}
}
void Driver::actions_west() {
	Room room = getRoom(player.getCurrentRoom().getX(),player.getCurrentRoom().getY() );
	Exit exit = getExit(player.getCurrentRoom().getX(),player.getCurrentRoom().getY(),"west");
	if ( (room != rooms[0])&&(exit != exits[0]) ){
		if(exit.isOpen()) {
			if (exit.getMsgSuccess() != ""){
				cout <<exit.getMsgSuccess()<<endl<<endl;}
			else{
				cout <<emsg_west<<endl<<endl;
			}
			player.setRoom(getRoom(exit.getX2(),exit.getY2()));
			printRoom();
		}
		else{
			if (exit.getMsgSuccess() != "") {
				cout <<exit.getMsgFail();
			}
			else {
				cout <<emsg_fail;
			}
		}
	}
	else {
		cout << fmsg_godir;
	}
}

void Driver::actions_look(std::string target) {
	if (target == "room") {
		printRoom();
	}
	else{
		for (std::size_t i = 0;i<objects.size();i++) {
			if (objects[i].checkName(target)){
				if ( itemIsHere(objects[i]) && !itemIsOwned(objects[i])) {
					cout << objects[i].msgLookAt;
					itWord = objects[i].getName();
					return;
				}
				else if (itemIsOwned(objects[i])) {
					cout << objects[i].msgLookAtOwned;
					itWord = objects[i].getName();
					return;
				}
			}
		}
		cout << fmsg_look;
		return;
	}
}
void Driver::actions_look_at(std::string target) {actions_look(target);}


void Driver::actions_go(std::string target) {
	if (target == "nowhere") {
		cout << "Impossible. The speed of the rotation of the Earth about the Sun, coupled with \nthe gravitational pull of the Earth, makes this a no-can-do. You sulk from \ndissapointment.";
	}
	else if (target == "north") {actions_north();}
	else if (target == "south") {actions_south();}
	else if (target == "east")  {actions_east();}
	else if (target == "west")  {actions_west();}
	else if (target == "fuck yourself" || target == "hell" || target == "die") {actions_swear();}
	else {
		cout << fmsg_go;
	}
}

void Driver::actions_kill(std::string target){
	if (target == ""){
		cout << "You must specify what to kill, and what to kill with.";
	}
	else if (target == "with"){
		cout << "You must specify what to kill.";
	}
	else {
		cout << "You must specify what to kill with.";
	}
}
void Driver::actions_kill_object(std::string target,std::string with) {
	if (target == "yourself" ||target == "self" ||target == "myself"||target == "me"||target == "player"||target == player.getName()) {
		if (with == "mind powers"){
			actions_kill_self(lmsg_mindpowers);
			return;
		}
		else {
			cout << fmsg_kill_with;
			return;
		}
	}
	else{
		for (std::size_t i = 0;i<objects.size();i++){
			//INSERT KILLING OBJECTS HERE (if (name == target) then kill it)
			if (itemIsHere(objects[i])||itemIsOwned(objects[i])){
				itWord = objects[i].getName();
				cout << fmsg_kill_item;
				return;
			}
		}
	}
	cout << fmsg_kill;
}
void Driver::actions_kill_self(std::string msg){
	if (yesNo()){
		death(msg);
	}
}

void Driver::actions_take(std::string target) {
	for (std::size_t i = 0;i<objects.size();i++) {
		if (objects[i].checkName(target) && itemIsHere(objects[i])) {
			if (objects[i].canTake()){
				if (!objects[i].isOwned()){
					addToInventory(objects[i]);
					objects[i].take();
					cout << objects[i].msgTake;

					itWord = objects[i].getName();
					return;
				}
				else {
					cout << fmsg_takeOwned;

					itWord = objects[i].getName();
					return;
				}
			}
			else {
				cout <<objects[i].msgTake;
				if (objects[i].getName() == "lightbulb"){
					hurtPlayer(5);
				}

				itWord = objects[i].getName();
				return;
			}
		}
	}
	cout << fmsg_take;
}
void Driver::actions_drop(std::string target) {
	for (std::size_t i = 0;i<objects.size();i++) {
		if (objects[i].checkName(target)) {
			if (objects[i].isOwned()){
				removeFromInventory(objects[i]);
				objects[i].drop(player.getCurrentRoom().getX(),player.getCurrentRoom().getY());
				cout << objects[i].msgDrop;

				itWord = objects[i].getName();
				return;
			}
			else {
				cout << fmsg_drop;
				itWord = objects[i].getName();
				return;
			}
		}
	}
	cout << fmsg_drop;
}

void Driver::actions_hit(std::string target) {
	for (std::size_t i = 0;i<objects.size();i++) {
		if (objects[i].checkName(target) && (itemIsHere(objects[i]) || itemIsOwned(objects[i]) ) ){
			itWord = objects[i].getName();
			if (objects[i].getName() == "wall") {
				cout << objects[i].msgHit<<endl;
				if (yesNo()){
					cout << "You smash your fist into the wall, and feel a shock run through your joints.";
					hurtPlayer(10);
					check_triggers_commands("scream");
				}
				return;
			}
			else if (objects[i].getName() == "lightbulb"){
				cout << objects[i].msgHit<<endl;
				actions_kill_self("You smash your hand up through the glass, badly cutting your hand. You feel high voltage current running through your body.");
				return;
			}
			else if (objects[i].getName() == "floor"){
				cout << objects[i].msgHit<<endl;
				if (yesNo()){
					cout << "You lean down and give the floor a good whack.";
					hurtPlayer(5);
					check_triggers_commands("scream");
					return;
				}
			}
			else if (objects[i].getName() == "valve"){
				cout << objects[i].msgHit<<endl;
				if (yesNo()){
					cout << "You wind up and punch that valve, showing it definitively who is boss.";
					hurtPlayer(10);
					return;
				}
			}
			else{
				cout << objects[i].msgHit;
				return;
			}
		}
	}
	if (target == "yourself" ||target == "self" ||target == "myself"||target == "my self"||target == "me"||target == "player"||target == player.getName()){
		if (yesNo()){
			cout << "You punch yourself in the head.";
			hurtPlayer(10);
			check_triggers_commands("scream");
			return;
		}
		else{
			return;
		}
	}
	cout << fmsg_hit;
}

void Driver::actions_throw(std::string target){
	for (std::size_t i = 0;i<objects.size();i++) {
		if (objects[i].checkName(target) && itemIsOwned(objects[i])) {
			cout << "You throw it to the ground!";
			objects[i].drop(player.getCurrentRoom().getX(),player.getCurrentRoom().getY());
			removeFromInventory(objects[i]);
			itWord = objects[i].getName();
			return;
		}
	}
	cout << fmsg_throw;
}

void Driver::actions_throw_at(std::string target,std::string weapon){
	bool hasWeapon = false;
	int wIndex;
	for (std::size_t i = 0;i<objects.size();i++) {
		if (objects[i].checkName(weapon) && (itemIsOwned(objects[i]) )){
			hasWeapon = true;
			wIndex = i;
			break;
		}
	}
	if (!hasWeapon) {
		cout << "You do not own that!";
		return;
	}
	for (std::size_t i = 0;i<objects.size();i++) {
		if (objects[i].checkName(target)){
			if (i == wIndex){
				cout << "You cannot throw something at itself!";
				return;
			}
		}
	}
	for (std::size_t i = 0;i<objects.size();i++) {
		if (objects[i].checkName(target) && (itemIsHere(objects[i]) || itemIsOwned(objects[i]) ) ){
			//if (target == "specific item") {call specific method}
			if (objects[i].getName() == "lightbulb"){
				if (objects[wIndex].getName() == "rock"){
					cout << "You hurl the rock into the lightbulb. The rock hits the floor across the room. The room is plunged into darkness.";
					removeFromInventory(objects[wIndex]);
					objects[wIndex].drop(player.getCurrentRoom().getX(),player.getCurrentRoom().getY());
					check_triggers_commands("scream");
					itWord = objects[wIndex].getName();
					return;
				}
				else {
					cout << "You cannot hit the light with that!";
					return;
				}
			}
			else if (objects[i].getName() == "wall"){
				if (objects[wIndex].getName() == "rock"){
					cout << "You hurl the rock at the wall; it promptly rebounds and hits you in the head.";
					removeFromInventory(objects[wIndex]);
					objects[wIndex].drop(player.getCurrentRoom().getX(),player.getCurrentRoom().getY());
					hurtPlayer(50);
					check_triggers_commands("scream");
					itWord = objects[wIndex].getName();
					return;
				}
				else {
					cout << "You cannot hit the wall with that!";
					return;
				}
			}
			else if (objects[i].getName() == "floor"){
				if (objects[wIndex].getName() == "rock"){
					cout << "You throw the rock towards the ground. A sharp echo resonates throughout the room.";
					removeFromInventory(objects[wIndex]);
					objects[wIndex].drop(player.getCurrentRoom().getX(),player.getCurrentRoom().getY());
					check_triggers_commands("scream");
					itWord = objects[wIndex].getName();
					return;
				}
				else {
					cout << "You cannot hit the floor with that!";
					return;
				}
			}
			else{
				cout << objects[i].msgHit;
				itWord = objects[i].getName();
				return;
			}
		}
	}
	if (target == "yourself" ||target == "self" ||target == "myself"||target == "me"||target == "player"||target == player.getName()){
		if (objects[wIndex].getName() == "rock"){
			if (yesNo()){
				actions_kill_self("You throw the rock into your head as hard as you can, smashing your teeth and nose into your skull");
				return;
			}
			else{
				return;
			}
		}
	}
	cout << fmsg_throw;

}

void Driver::actions_turn(std::string target){
	for (std::size_t i = 0;i<objects.size();i++){
		if (objects[i].checkName(target) && itemIsHere(objects[i])) {
			if (objects[i].getName() == "valve"){
				if (objects[i].isOiled()) {

				}
				else{
					cout << "You try as hard as you can, but the valve won't budge!";
					return;
				}
			}
			else{
				cout << "You cannot turn that!";
				return;
			}
		}
	}
	cout << "You cannot see that here.";
}

void Driver::actions_say(std::string text){
	if (checkLiving()) {
		int i = getAnyCharacterIndex();
		std::string temp = objects[i].getName();
		actions_say_to(text,temp);
		return;
	}
	else{
		cout << char(34) << text << char(34) <<", you say. Nobody hears you.";
		return;
	}
}

void Driver::actions_say_to(std::string text,std::string target){
	for (std::size_t i = 0; i < objects.size(); i++){
		if (objects[i].checkName(target) && itemIsHere(objects[i])){

			if(objects[i].isAlive()){

				if (objects[i].getName() == "lizard"){
					cout << char(34) << text << char(34) <<", you say.\n";
					cout << char(34) << char(34) << ", says the lizard. He doesn't seem to be interested.";
					return;
				}
	
			}
			else {
				cout << char(34) << text << char(34) <<", you say.\n";
				cout << char(34) << char(34) << ", says the "<<objects[i].getName()<<". The "<<objects[i].getName()<<" doesn't seem to be interested.";
				return;
			}

		}
	}
	cout << "You cannot see that here.";
}

void Driver::actions_hit_with(std::string target,std::string weapon) {
	bool hasWeapon = false;
	int wIndex;
	for (std::size_t i = 0;i<objects.size();i++) {
		if (objects[i].checkName(weapon) && (itemIsOwned(objects[i]) )){
			hasWeapon = true;
			wIndex = i;
			break;
		}
	}
	if (!hasWeapon) {
		cout << "You do not own that!";
		return;
	}
	for (std::size_t i = 0;i<objects.size();i++) {
		if (objects[i].checkName(target)){
			if (i == wIndex){
				cout << "You cannot hit something with itself!";
				return;
			}
		}
	}
	for (std::size_t i = 0;i<objects.size();i++) {
		if (objects[i].checkName(target) && (itemIsHere(objects[i]) || itemIsOwned(objects[i]) ) ){
			//if (target == "specific item") {call specific method}
			if (objects[i].getName() == "lightbulb"){
				if (objects[wIndex].getName() == "rock"){
					cout << "You smash the light bulb with the rock. The room is plunged into darkness.";
					check_triggers_commands("scream");
					itWord = objects[wIndex].getName();
					return;
				}
				else {
					cout << "You cannot hit the light with that!";
					return;
				}
			}
			else if (objects[i].getName() == "wall"){
				if (objects[wIndex].getName() == "rock"){
					cout << "You slam the rock into the wall, creating a deafening echo in the small room.";
					check_triggers_commands("scream");
					itWord = objects[wIndex].getName();
					return;
				}
				else {
					cout << "You cannot hit the wall with that!";
					return;
				}
			}
			else if (objects[i].getName() == "floor"){
				if (objects[wIndex].getName() == "rock"){
					cout << "You slam the rock into the concrete floor, creating a deafening echo in the small room.";
					check_triggers_commands("scream");
					itWord = objects[wIndex].getName();
					return;
				}
				else {
					cout << "You cannot hit the floor with that!";
					return;
				}
			}
			else{
				cout << objects[i].msgHit;
				itWord = objects[i].getName();
				return;
			}
		}
	}
	if (target == "yourself" ||target == "self" ||target == "myself"||target == "me"||target == "player"||target == player.getName()){
		if (objects[wIndex].getName() == "rock"){
			if (yesNo()){
				cout << "You smack the rock against your forehead with great velocity.";
				hurtPlayer(25);
				return;
			}
			else{
				return;
			}
		}
	}
	cout << fmsg_hit;
}

void Driver::actions_swear() {
	cout << amsg_swear;
}

void Driver::actions_stats() {
	system("cls");

	setColor("black","white");
	cout << "Player "<<player.getName()<<"'s stats:\n";
	setColor("light red","black");
		cout << "\tHealth: "<<player.getHealth()<<endl;
	setColor("light blue","black"); 
		cout << "\tThirst: "<<player.getThirst()<<endl<<endl;
	setColor("light yellow","black");
		cout << "\tTurns: "<<player.getTurns()<<endl;
	setColor("light green","black");
		cout << "\tScore: "<<player.getScore()<<endl;
	resetColor();
	system("pause");
	system("cls");
	printRoom();
}
void Driver::actions_inventory(){
	system("cls");
	std::string temp;
	setColor("black","light white");
	addShade(temp,"light",WIDTH);
	addLeftText(temp,dmsg_inventory,"light");
	addBlankBorder(temp,"light");
	for (std::size_t i = 0;i<inventory.size();i++){
		addLeftText(temp,inventory[i].getArticle()+" "+inventory[i].getName(),"light");
	}
	addBlankBorder(temp,"light");
	addShade(temp,"light",WIDTH);

	cout << temp;
	resetColor();
	system("pause");
	system("cls");
	printRoom();
}

void Driver::actions_clear() {
	system("cls");
	printRoom();
}

void Driver::actions_quit() {
	if (yesNo()){
		exit(1);
	}
}


//############################################################################
//############################################################################
//############################################################################




bool Driver::check_triggers_null() {
	//TRIGGER 1a: Check if player stays in first room too long (8 turns). If so, deal punishment
	if (player.getCurrentRoom().getX() == 50 && player.getCurrentRoom().getY() == 50 && player.getTurns() == 8){
		for (std::size_t i = 0;i < exits.size();i++){
			if (exits[i].getX() == 50 && exits[i].getY() == 50 && exits[i].getDirection() == "north" && exits[i].isOpen() == false){
				death("\tSuddenly a voice sounds through a loudspeaker:\n\n'It has come to our attention that you may not, in fact, be the right man for   the job. You take too long! Appropriate measures will be taken.'\n\nA yellowish gas begins to spray in through the corners   of the room. You cover your mouth, but it is too late. You fall to the ground and feel the darkness    setting in.\n\n");
				return true;
			}
		}
		return false;
	}
	else {
		return false;
	}
}	
bool Driver::check_triggers_commands(std::string target){
	int pos = target.find_first_of(' ');
	std::string first = target.substr(0,pos);
	//TRIGGER 1b: Check if player screams when in the first room. If so, unlock the door
	if (player.getCurrentRoom().getX() == 50 && player.getCurrentRoom().getY() == 50 && (first == "scream" || first == "yell" || first == "shout" )){
		for (std::size_t i = 0;i<exits.size();i++){
			if (exits[i].getX() == 50 && exits[i].getY() == 50 && exits[i].getDirection() == "north" && exits[i].isOpen() == false) {
				cout << "\nSuddenly, the northern wall of the room lowers.\n A voice raises over an unseen loudspeaker:\n'Congratulations, you have passed the first test. We wanted to make sure you    were vulnerable to anger and frustration, or this whole thing would be no fun.'\n";
				getPlayerPtr()->getCurrentRoomPtr()->setDescription(" This is a dimly lit, faded white room with no apparent windows and a small     door to the north. In fact, the entire room seems void of all objects except     a dim, flickering light bulb in the middle of the ceiling.  ");
				rooms[getRoomIndex(player.getCurrentRoom().getX(),player.getCurrentRoom().getY())].setDescription(" This is a dimly lit, faded white room with no apparent windows and a small     door to the north. In fact, the entire room seems void of all objects except     a dim, flickering light bulb in the middle of the ceiling.  ");
				std::string temp;
				addCenteredText(temp,gmsg_dirn);
				setColor("black","light green");
				cout << temp;
				resetColor();
				exits[i].unlock();
				return true;
			}
		}
		return false;
	}
	else {
		return false;
	}
}

