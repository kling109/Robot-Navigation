/*******************************************************************************
Robot Navigator

A simple robot navigation program.  The program takes an input of a gameboard,
represented by a text file, and a specification of a type of search algorithm.
The program then determines the best path for the robot to take based on the
chosen search paradigm.

Author: Trevor Kling
Email: kling109@mail.chapman.edu
Course: CPSC 390 Artificial Intelligence
Student ID: 002270716
Last Date Modified: 02/29/2020
*******************************************************************************/

/*
Gameboard class for robot navigation.  This class handles reading in the file,
creating the gameboard, and performing all accesses to the gameboard.
*/

#include <utility>
#include <list>
#include <memory>
#include <map>
#include <fstream>
#include <iostream>

using namespace std;

class World
{
  public:
    World(string filePath);
    ~World();
    pair<int, int> getStartPos();
    pair<int, int> getGoalPos();
    int getGameBoardSize();
    int evaluatePos(int x, int y);
    void printGameboard(list<pair<int, int>> *navPath);
  private:
    int** gameboard;
    int gameboardSize;
    pair<int, int> *startPos;
    pair<int, int> *goalPos;
    void buildGameBoard(string filePath);
};
