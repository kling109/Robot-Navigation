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
Last Date Modified: 02/18/2020
*******************************************************************************/

/*
Gameboard class for robot navigation.  This class handles reading in the file,
creating the gameboard, and performing all accesses to the gameboard.
*/

#include <pair>

using namespace std;

class World {
  public:
    World(string filePath);
    ~World();
    shared_ptr<pair<int, int>> getStartPos();
    shared_ptr<pair<int, int>> getGoalPos();
    int evaluatePos(int x, int y);
  private:
    unique_ptr<array<int>> gameboard;
    unique_prt<array<int>> buildGameBoard(string filePath);
};
