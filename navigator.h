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
Last Date Modified: 02/26/2020
*******************************************************************************/

/*
Navigation class for robot decision-making.  This program makes accesses to the
world class to determine how to move about the game board.  The program takes
an input of a world object and a navigation method, then traverses the world
based on the given criteria.
*/

#include <utility>
#include <list>
#include <queue>
#include <memory>
#include <utility>
#include <cmath>
#include "world.h"

using namespace std;

struct MinDistFirst
{
  /*
  A structure that defines the method of sorting for a
  priority queue of pairs, where one component of the pair is the
  gameboard location and the other is the cost of moving to that location.
  */
  bool operator()(const pair<pair<int, int>, float>& p1,
    const pair<pair<int, int>, float>& p2)
  {
    return get<1>(p1) > get<1>(p2);
  }
};

class Navigation
{
  public:
    Navigation(World *toNav);
    ~Navigation();
    void navigate(int navMethod);
    list<pair<int, int>> *assemblePath(pair<int, int> pos);
  private:
    priority_queue<pair<pair<int, int>, float>, vector<pair<pair<int, int>, float>>, MinDistFirst> *toCheck;
    map<pair<int, int>, pair<int, int>> *priorSeen;
    map<pair<int, int>, float> *priorCost;
    World *toNavigate;
    void successor(pair<int, int> currentPos, float priorCost, int navMethod);
    float euclidDist(pair<int, int> pos1, pair<int, int> pos2);
    float manhattanDist(pair<int, int> pos1, pair<int, int> pos2);
    void printPath();
};
