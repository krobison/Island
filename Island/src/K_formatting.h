#pragma once

#include <string>
#include <Windows.h>
#include <sstream>

using namespace std;

const int WIDTH = 80;
const char dark		= char(178);
const char medium	= char(177);
const char light	= char(176);

void addCenteredText(string& original,string text,bool withShade = false,string type = "dark");
void addShade(string& stringToAdd,string type,int amount);
void addBlankBorder(string& original,string type);
void addLeftText(string& original,string text,string type = "dark");

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
	for(std::size_t a = 0;a < (text.length() / WIDTH)+1; a++) {
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
	for(std::size_t a = 0;a < (text.length() / WIDTH)+1; a++) {
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

void addLeftText(string& original,string text,string type){
	std::string origtext = text;
	addShade(original,type,1);
	original += ' ';
	for (int j = 0;j<WIDTH-4;j++) {
		if(text.length()>0){
			original+= text[0];
			text.erase(0,1);
		}
		else{
			break;
		}
	}
	for (std::size_t i = 0;i<WIDTH-origtext.length()-3;i++){
		original += ' ';
	}
	addShade(original,type,1);
}