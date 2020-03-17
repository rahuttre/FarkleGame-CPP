// Ryan Hutton
// Final Project - Farkle Game
// SNHU IT 312 - Software Development with C++
// 2/23/2020

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

#include "GamePlay.h"

using namespace std;

GamePlay::GamePlay()
{
    int dice[6];
    std::string* players[5];
    bool rollAgainPos[6] = { false };
    int score, totalDice, rerollDice, firstScore, totalScore;
}

GamePlay::~GamePlay() 
{

}

// Accessors and modifiers for private variables
/*void GamePlay::setDice(int newDice[])
{
    dice[] = newDice[];
}
*/

int GamePlay::getDice(int index)
{
    return dice[index];
}

//void GamePlay::setPlayers(string newPlayers[]);

std::string GamePlay::getPlayers(int index)
{
    return players[index];
}

//void setRollAgainPos(bool newPosition[])

bool GamePlay::getRollAgainPos(int index)
{
    return rollAgainPos[index];
}

void GamePlay::setScore(int newScore)
{
    score = newScore;
}

int GamePlay::getScore()
{
    return score;
}

void GamePlay::setTotalDice(int newTotalDice)
{
    totalDice = newTotalDice;
}

int GamePlay::getTotalDice()
{
    return totalDice;
}

void GamePlay::setFirstScore(int newFirstScore)
{
    firstScore = newFirstScore;
}

int GamePlay::getFirstScore()
{
    return firstScore;
}

void GamePlay::setTotalScore(int newTotalScore)
{
    totalScore = newTotalScore;
}

int GamePlay::getTotalScore()
{
    return totalScore;
}

int* GamePlay::rollDice() //Dice roll function, restricts possible numbers between 1 and 6
{
    for (int i = 0; i < 6; i++)
    {
        dice[i] = (rand() % 6 + 1); //Numbers restricted to between 1 and 6 to simulate dice
    }

    //return dice[6]; //Returns roll values
    return dice;
}

int* GamePlay::rollAgain() // Reroll function, usees rerollPosition bool array to only reroll the positions that don't score the first time
{
    for (int i = 0; i < 6; i++)
    {
        if (rollAgainPos[i] == true)
        {
            dice[i] = (rand() % 6 + 1);
        }
    }
    //return dice[6];
    return dice;
}

void GamePlay::displayRoll()
{
    for (int i = 0; i <= 5; i++) // Prints dice values from the roll
    {
        cout << dice[i] << "   ";
    }
}

std::string* GamePlay::collectNames(int numPlayers) //Function to establish player name array, set it's size and take name input
{
    for (int i = 0; i <= (numPlayers - 1); i++) //Loop to get the names of all players
    {
        std::cout << "Enter the name of player " << (i + 1) << ": ";
        std::cin >> players[i];
    }
    return players;
}

int GamePlay::calculateScore(int* playerScore) //Scoring function
{
    int count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0, count6 = 0; //Variable counts for each roll possibility

    setScore(0); //Reset score each time the function is run

    rerollDice = 0; // Reset the number of dice to reroll each time the function is run

    for (int i = 0; i < 6; i++) // check for 1's and 5's as well as increment the individual number counters
    {
        switch (dice[i])
        {
        case 1:
            score += 100;
            count1++;
            break;
        case 2:
            count2++;
            rerollDice++;
            rollAgainPos[i] = true;
            break;
        case 3:
            count3++;
            rerollDice++;
            rollAgainPos[i] = true;
            break;
        case 4:
            count4++;
            rerollDice++;
            rollAgainPos[i] = true;
            break;
        case 5:
            score += 50;
            count5++;
            break;
        case 6:
            count6++;
            rerollDice++;
            rollAgainPos[i] = true;
            break;
        }
    }
    if (rerollDice == 6)
    {
        cout << "Farkle! You didn't roll any scoring dice, any score gained this turn is lost" << endl;
        score = 0;
    }
    else
    {
        if (count1 >= 3) // If statements to check for triple rolls and add to the score accordingly
        {
            score = (score - 300) + 1000; //Removes original 300 score before adding 1000
        }
        else if (count2 >= 3)
        {
            score += 200;
            for (int i = 0; i < 6; i++)
            {
                if (dice[i] == 2) { rollAgainPos[i] = false; }
            }
            rerollDice -= 3;
        }
        else if (count3 >= 3)
        {
            score += 300;
            for (int i = 0; i < 6; i++)
            {
                if (dice[i] == 3) { rollAgainPos[i] = false; }
            }
            rerollDice -= 3;
        }
        else if (count4 >= 3)
        {
            score += 400;
            for (int i = 0; i < 6; i++)
            {
                if (dice[i] == 4) { rollAgainPos[i] = false; }
            }
            rerollDice -= 3;
        }
        else if (count5 >= 3)
        {
            score = (score - 150) + 500; //Removes 150 from score before adding 500
        }
        else if (count6 >= 3)
        {
            score += 600;
            for (int i = 0; i < 6; i++)
            {
                if (dice[i] == 6) { rollAgainPos[i] = false; }
            }
            rerollDice -= 3;
        }
    }

    firstScore = score; // Initial turn variable that has to exceed 1000 to continue in the game
    cout << "Score from that roll: " << score << endl;

    return rerollDice, * playerScore;
}

int GamePlay::eachPlayerTurn(int numPlayers, int* playerScore) //Function that handles individual player turns
{
    char rerollCheck; // Variable for Y or N reroll input

    for (int i = 0; i < numPlayers; i++) // Repeats the turn based on how many players are playing
    {
        cout << players[i] << " let's roll the dice: " << endl; //Says which player is currently rolling

        rollDice(); //Dice roll function
        displayRoll(); //Prints dice roll
        calculateScore(playerScore); //Scores the roll

        if (rerollDice == 0)
        {
            std::cout << "All dice are scoring dice, you get to roll all 6 again for more score";
            playerScore[i] += score;
            rollDice();
            displayRoll();
            calculateScore(playerScore);
        }
        else if (rerollDice != 6)
        {
            cout << endl << "Do you want to reroll the " << rerollDice << " non scoring dice? (Y/N)" << endl; //Gives the option to reroll the non scoring dice or not
            cin >> rerollCheck;

            if (rerollCheck == 'y' || rerollCheck == 'Y') //reroll is performed based on the number of non scoring dice
            {
                rollAgain(); //Dice roll function
                displayRoll(); //Print dice roll
                calculateScore(playerScore); //Score reroll
            }
            else if (rerollCheck == 'n' || rerollCheck == 'N') //If user chooses no their turn is over and rerollDice is set to 0 so that the dice total will be reset properl
            {
                std::cout << "Your turn is now over" << endl;
                rerollDice = 0;
            }
        }

        for (int i = 0; i < 6; i++) 
        {
            rollAgainPos[i] = false;
        
        }

        std::cout << players[i] << " your score from that round: " << score << endl;
        playerScore[i] += score; //Adds the score total to the individual player score array
        totalScore += score; //Built the game to work single player to check functionality

        std::cout << "Your total score after that round: " << getTotalScore() << endl << endl;

    }
    return *playerScore;

}

int GamePlay::initialTurn(int* playerScore) // First turn that handles the rolls before the initial 1000+ roll, executes on it's own until it happens
{
    rollDice();
    displayRoll();
    calculateScore(playerScore);
    rerollDice = 0;
    return *playerScore;
}

int GamePlay::RunGame()
{
    srand(time(0)); //Seeds the random number generator

    int numPlayers;

    cout << endl << endl << "How many players are there?" << endl;

    while (!(cin >> numPlayers))//Number of players input
    {
        cin.clear();
        cin.ignore();
        cout << "Please enter a whole number" << std::endl;
    }

    collectNames(numPlayers); // Get the names of the players

    int* playerScore = new int[numPlayers]; // Scoring array to hold individual player scores

    for (int i = 0; i < numPlayers; i++) 
    { 
        playerScore[i] = 0;
    }//Initializes score arry to a 0 value after it's size is determined

    while (firstScore < 1000) 
    {
        initialTurn(playerScore);
    } //First turn won't end until player rolls over 1000 on a single roll
    
    cout << endl; // Basic separation from the first round spam

    while (totalScore < 10000) //Win condition, game lasts until a player hits or exceeds 10,000 points
    {
        std::cout << std::endl;
        eachPlayerTurn(numPlayers, playerScore);
        if (totalScore >= 10000)
        {
            cout << "Congratulations, you win!" << endl << endl;
            break;
        }
    }
    system("PAUSE");
    return 0;
}
