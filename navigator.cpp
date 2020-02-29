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

#include "navigator.h"

Navigation::Navigation(World *toNav)
{
  /*
  A standard constructor for the Navigation object.
  */
  toNavigate = toNav;
  toCheck = new priority_queue<pair<pair<int, int>, float>, vector<pair<pair<int, int>, float>>, MinDistFirst>();
  priorSeen = new map<pair<int, int>, pair<int, int>>();
  priorCost = new map<pair<int, int>, float>();
}

Navigation::~Navigation()
{
  /*
  A standard deconstructor for the Navigation class.  Deletes the allocated
  objects.
  */
  if (toCheck != NULL) {
    delete toCheck;
  }
  if (priorSeen != NULL) {
    delete priorSeen;
  }
  if (priorCost != NULL) {
    delete priorCost;
  }
}

void Navigation::navigate(int navMethod)
{
  /*
  The driver method for the program.  Continueously calls the "successor"
  function, allowing the priority queue to effectively handle backtracking
  automatically.  Once the goal is reached, the program prints the path found
  as well as statistics about the path.

  Keyword Arguments:
    navMethod (int): A flag to determine which navigation method to use.
  */
  if (toNavigate != NULL) {
    priorSeen->clear();
    priorCost->clear();
    delete toCheck;
    toCheck = new priority_queue<pair<pair<int, int>, float>, vector<pair<pair<int, int>, float>>, MinDistFirst>();
    pair<int, int> currPos = toNavigate->getStartPos();
    pair<int, int> goalPos = toNavigate->getGoalPos();
    priorSeen->insert({currPos, {-1, -1}});
    float currCost = 0;
    int steps = 1;
    while (currPos != goalPos) {
      successor(currPos, currCost, navMethod);
      currPos = toCheck->top().first;
      currCost = toCheck->top().second;
      toCheck->pop();
      ++steps;
    }
    toNavigate->printGameboard(assemblePath(currPos));
    cout << "Number of steps made: " << steps << "\n";
    cout << "Number of nodes visited in path: " << assemblePath(currPos)->size() << "\n";
    cout << "Number of nodes in search tree: " << priorSeen->size() << "\n";
    cout << "Current Cost: " << currCost << "\n";
  } else {
    cout << "There was an error initializing your game world.\n";
  }
}

list<pair<int, int>> *Navigation::assemblePath(pair<int, int> pos)
{
  /*
  A helper method which find the path generated to a specific node.  Generally
  used after the navigation method has found a path to the goal to produce the
  optimal path.

  Keyword Arguments:
    pos (pair<int, int>): The end position navigated to.
  */
  list<pair<int, int>> *path = new list<pair<int, int>>();
  if (priorSeen->find(pos) != priorSeen->end()) {
    pair<int, int> currState = pos;
    pair<int, int> endState = {-1, -1};
    while (currState != endState) {
      path->push_back(currState);
      currState = priorSeen->at(currState);
    }
  } else {
    cout << "Error: Invalid choice of position.\n";
  }
  return path;
}

void Navigation::successor(pair<int, int> currentPos, float currentCost, int navMethod)
{
  /*
  The "successor" method for the search problem.  Finds all the adjacent nodes,
  then uses the prescribed distance metric to determine the cost of moving to
  them.  These are then added to both the map of all values and their minimum
  cost, as well as the priority queue which functions as the fringe.

  Keyword Arguments:
    currentPos (pair<int, int>): The location to produce successors from.
    currentCost (float): the cost assumed by moving to the current postion.
    navMethod (int): A flag to determine which navigation method to use.
  */
  pair<int, int> *adjacent = new pair<int,int>[4];
  adjacent[0] = {currentPos.first, currentPos.second - 1};
  adjacent[1] = {currentPos.first, currentPos.second + 1};
  adjacent[2] = {currentPos.first - 1, currentPos.second};
  adjacent[3] = {currentPos.first + 1, currentPos.second};
  pair<int, int> goal = toNavigate->getGoalPos();
  if (navMethod == 1) {
    // Euclidean distance
    for (int i = 0; i < 4; ++i) {
      if (toNavigate->evaluatePos(adjacent[i].first, adjacent[i].second) != 3) {
        float adjCost = euclidDist(adjacent[i], goal);
        if (priorCost->find(adjacent[i]) == priorCost->end()) {
          priorSeen->insert({adjacent[i], currentPos});
          priorCost->insert({adjacent[i], adjCost});
          toCheck->push({adjacent[i], adjCost});
        } else if (priorCost->at(adjacent[i]) > adjCost) {
          priorSeen->at(adjacent[i]) = currentPos;
          priorCost->at(adjacent[i]) = adjCost;
          toCheck->push({adjacent[i], adjCost});
        }
      }
    }
  } else if (navMethod == 2) {
    // Manhattan Distance
    for (int i = 0; i < 4; ++i) {
      if (toNavigate->evaluatePos(adjacent[i].first, adjacent[i].second) != 3) {
        float adjCost = manhattanDist(adjacent[i], goal);
        if (priorCost->find(adjacent[i]) == priorCost->end()) {
          priorSeen->insert({adjacent[i], currentPos});
          priorCost->insert({adjacent[i], adjCost});
          toCheck->push({adjacent[i], adjCost});
        } else if (priorCost->at(adjacent[i]) > adjCost) {
          priorSeen->at(adjacent[i]) = currentPos;
          priorCost->at(adjacent[i]) = adjCost;
          toCheck->push({adjacent[i], adjCost});
        }
      }
    }
  } else if (navMethod == 3) {
    // Euclidean Distance with prior cost
    for (int i = 0; i < 4; ++i) {
      if (toNavigate->evaluatePos(adjacent[i].first, adjacent[i].second) != 3) {
        float adjCost = euclidDist(adjacent[i], goal) + currentCost;
        if (priorCost->find(adjacent[i]) == priorCost->end()) {
          priorSeen->insert({adjacent[i], currentPos});
          priorCost->insert({adjacent[i], adjCost});
          toCheck->push({adjacent[i], adjCost});
        } else if (priorCost->at(adjacent[i]) > adjCost) {
          priorSeen->at(adjacent[i]) = currentPos;
          priorCost->at(adjacent[i]) = adjCost;
          toCheck->push({adjacent[i], adjCost});
        }
      }
    }
  } else if (navMethod == 4) {
    // Manhattan distance with prior cost
    for (int i = 0; i < 4; ++i) {
      if (toNavigate->evaluatePos(adjacent[i].first, adjacent[i].second) != 3) {
        float adjCost = manhattanDist(adjacent[i], goal) + currentCost;
        if (priorCost->find(adjacent[i]) == priorCost->end()) {
          priorSeen->insert({adjacent[i], currentPos});
          priorCost->insert({adjacent[i], adjCost});
          toCheck->push({adjacent[i], adjCost});
        } else if (priorCost->at(adjacent[i]) > adjCost) {
          priorSeen->at(adjacent[i]) = currentPos;
          priorCost->at(adjacent[i]) = adjCost;
          toCheck->push({adjacent[i], adjCost});
        }
      }
    }
  }
}

float Navigation::euclidDist(pair<int, int> pos1, pair<int, int> pos2)
{
  /*
  A helper method which finds the Euclidean distance between two pairs.

  Keyword Arguments:
    pos1 (pair<int, int>): The first position.
    pos2 (pair<int, int>): The second position.
  */
  float deltax = float(pos2.first - pos1.first);
  float deltay = float(pos2.second - pos1.second);
  return sqrt(deltax*deltax + deltay*deltay);
}

float Navigation::manhattanDist(pair<int, int> pos1, pair<int, int> pos2)
{
  /*
  A helper method which finds the Manhattan distance between two pairs.

  Keyword Arguments:
    pos1 (pair<int, int>): The first position.
    pos2 (pair<int, int>): The second position.
  */
  float deltax = float(pos2.first - pos1.first);
  float deltay = float(pos2.second - pos1.second);
  return (abs(deltax) + abs(deltay));
}
