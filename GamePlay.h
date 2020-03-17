// Ryan Hutton
// Final Project - Farkle Game
// SNHU IT 312 - Software Development with C++
// 2/23/2020


#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <iostream>
#include <string>

using namespace std;

class GamePlay
{
private:
	int dice[6];
	std::string players[5];
	bool rollAgainPos[6] = { false };
	int score, totalDice, rerollDice, firstScore, totalScore;

public:

	GamePlay();
	~GamePlay();

	// Accessors and modifiers for private variables
	//void setDice(int newDicePos);
	int getDice(int index);

	//void setPlayers(std::string newPlayers[]);
	std::string getPlayers(int index);

	//void setRollAgainPos(bool newPosition[]);
	bool getRollAgainPos(int index);

	void setScore(int newScore);
	int getScore();

	void setTotalDice(int newTotalDice);
	int getTotalDice();

	void setFirstScore(int newFirstScore);
	int getFirstScore();

	void setTotalScore(int newTotalScore);
	int getTotalScore();

	// GamePlay Methods below
	int* rollDice(); 
	int* rollAgain(); 
	void displayRoll(); 
	std::string* collectNames(int numPlayers); 
	int calculateScore(int* playerScore); 
	int eachPlayerTurn(int numPlayers, int* playerScore); 
	int initialTurn(int* playerScore); 
	int RunGame();	// Let's begin the game!
};

#endif