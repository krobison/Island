#pragma once

#include <string>
#include <Windows.h>

using namespace std;


void setColor(string foreground,string background);
void resetColor();

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