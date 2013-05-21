#include <string>
#include <Windows.h>

using namespace std;


const int WIDTH = 80;
const char dark	= 178;
const char medium = 177;
const char light	= 176;

void addCenteredText(string& original,string text,bool withShade = false,string type = "dark");
void addShade(string& stringToAdd,string type,int amount);
void addBlankBorder(string& original,string type);
void setColor(string foreground,string background);
void resetColor();
void printIntro();
string getIntro();


void addShade(string& stringToAdd,string type,int amount) {
	if (type == "dark") {
		stringstream out;
		for (int i = 0;i<amount;i++) {
			out << dark;
		}
		stringToAdd += out.str();
	}
	else if (type == "medium") {
		stringstream out;
		for (int i = 0;i<amount;i++) {
			out << medium;
		}
		stringToAdd += out.str();
	}
	else if (type == "light") {
		stringstream out;
		for (int i = 0;i<amount;i++) {
			out << light;
		}
		stringToAdd += out.str();
	}
}

void addCenteredText(string& original,string text,bool withShade,string type) {
if ((!withShade)&&(text.length() < WIDTH)) {
	int offset = (WIDTH - text.length())/2;
	for (int i = 0;i < offset;i++) {
		original+=" ";
	}
	original += text;
	for (int i = 0;i < offset;i++) {
		original+=" ";
	}
	if ( text.length() % 2 == 1 ) {
		original += " ";
	}
}
else if (text.length() < WIDTH) {
	int offset = (WIDTH - text.length()-2)/2;
	addShade(original,type,1);
	for (int i = 0;i < offset;i++) {
		original+=" ";
	}
	original += text;
	for (int i = 0;i < offset;i++) {
		original+=" ";
	}
	if ( text.length() % 2 == 1 ) {
		original += " ";
	}
	addShade(original,type,1);
}
else if ((!withShade)&&(text.length() >= WIDTH)) {
	int count = text.length();
	for(int a = 0;a < (text.length() / WIDTH)+1; a++) {
		if (count > WIDTH) {
			for (int i = 0;i < WIDTH;i++) {
				original += text[a*WIDTH+i];
				count -= 1;
			}
		}
		else{
				int offset = (WIDTH - count)/2;
				for (int i = 0;i < offset;i++) {
					original+=" ";
				}
				for (int i = 0;i < count;i++) {
					original += text[a*WIDTH+i];
				}
				for (int i = 0;i < offset;i++) {
					original+=" ";
				}
				if ( count % 2 == 1 ) {
					original += " ";
				}
		}
	}
}
else if ((withShade)&&(text.length() >= WIDTH)) {
	int count = text.length();
	for(int a = 0;a < (text.length() / WIDTH)+1; a++) {
		if (count > WIDTH) {
			addShade(original,type,1);
			for (int i = 0;i < (WIDTH-2);i++) {
				original += text[a*WIDTH+i-2*a];
				count -= 1;
			}
			addShade(original,type,1);
		}
		else{
				addShade(original,type,1);
				int offset = (WIDTH - count-2)/2;
				for (int i = 0;i < offset;i++) {
					original+=" ";
				}
				for (int i = 0;i < count-2;i++) {
					original += text[a*WIDTH+i-2*a];
				}
				for (int i = 0;i < offset;i++) {
					original+=" ";
				}
				if ( count % 2 == 1 ) {
					original += " ";
				}
				original += "  ";
				addShade(original,type,1);
		}
	}
}
}

void addBlankBorder(string& original,string type) {
	addCenteredText(original,"",true,type);
}

void setColor(string foreground,string background) {
	HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
	int F,B;

	if		(foreground == "black")			{F = 0x0000;}
	else if (foreground == "blue")			{F = 0x0001;}
	else if (foreground == "green")			{F = 0x0002;}
	else if (foreground == "aqua")			{F = 0x0003;}
	else if (foreground == "red")			{F = 0x0004;}
	else if (foreground == "purple")		{F = 0x0005;}
	else if (foreground == "yellow")		{F = 0x0006;}
	else if (foreground == "white")			{F = 0x0007;}
	else if ( (foreground == "grey")||(foreground =="gray"))				{F = 0x0008;}
	else if (foreground == "light blue")	{F = 0x0009;}
	else if (foreground == "light green")	{F = 0x000A;}
	else if (foreground == "light aqua")	{F = 0x000B;}
	else if (foreground == "light red")		{F = 0x000C;}
	else if (foreground == "light purple")	{F = 0x000D;}
	else if (foreground == "light yellow")	{F = 0x000E;}
	else if (foreground == "light white")	{F = 0x000F;}
	else return;								 

	if		(background == "black")			{B = 0x0000;}
	else if (background == "blue")			{B = 0x0010;}
	else if (background == "green")			{B = 0x0020;}
	else if (background == "aqua")			{B = 0x0030;}
	else if (background == "red")			{B = 0x0040;}
	else if (background == "purple")		{B = 0x0050;}
	else if (background == "yellow")		{B = 0x0060;}
	else if (background == "white")			{B = 0x0070;}
	else if((background == "grey")||(background =="gray"))				{B = 0x0080;}
	else if (background == "light blue")	{B = 0x0090;}
	else if (background == "light green")	{B = 0x00A0;}
	else if (background == "light aqua")	{B = 0x00B0;}
	else if (background == "light red")		{B = 0x00C0;}
	else if (background == "light purple")	{B = 0x00D0;}
	else if (background == "light yellow")	{B = 0x00E0;}
	else if (background == "light white")	{B = 0x00F0;}
	else return;

	SetConsoleTextAttribute(h,F+B);
}

void resetColor() {
	HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute ( h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void printIntro() {
	setColor("red","gray");
	cout << getIntro();

	cout << string(2,'\n');

	setColor("gray","black");
	cout << "Please enter your name to start, or 'quit' to quit\n\n>";
}

string getIntro() {
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
