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
Navigation class for robot decision-making.  This program makes accesses to the
world class to determine how to move about the game board.  The program takes
an input of a world object and a navigation method, then traverses the world
based on the given criteria.
*/

#include <pair>
#include <list>
#include <memory>
#include "world.h"

using namespace std;

class Navigation {
  public:
    Navigation(World toNav, int navMethod);
    ~Navigation();
    void navigate();
  private:
    shared_ptr<list<shared_ptr<pair<int, int>>>> navPath;
    shared_ptr<pair<int, int>> successor(shared_ptr<pair<int, int>>
      currentPos, int navMethod);
    float euclidDist(shared_ptr<pair<int, int>> pos1,
      shared_ptr<pair<int, int>> pos2);
    float manhattanDist(shared_ptr<pair<int, int>> pos1,
      shared_ptr<pair<int, int>> pos2);
    void printPath();

}
