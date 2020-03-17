// Ryan Hutton
// Final Project - Farkle Game
// SNHU IT 312 - Software Development with C++
// 2/23/2020

#include <iostream>
#include <fstream>
#include <string>

#include "GamePlay.h"

using namespace std;

void ReadGameRules();

int main()
{
	ReadGameRules();
	GamePlay game;
	game.RunGame();

	return 0;
}

void ReadGameRules()
{
	// Open .txt file and pass it to infile.
	ifstream infile("FarkleGameRules.txt");

	// This checks if the file fails to open.
	if (infile.fail())
	{
		// cerr is a unique output command for errors.
		cerr << "Error opening file" << endl;
		exit(1); // exit the file.
	}

	string line;

	// Loop the file until the loop reaches the end of file (eof)
	while (!infile.eof())
	{
		getline(infile, line);
		cout << line << endl;
	}

	// Close the file.
	infile.close();
}



