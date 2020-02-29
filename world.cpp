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

#include "world.h"

using namespace std;

World::World(string filePath)
{
  /*
  Basic constructor of the World class.  Takes a file path to produce the
  important varables from.

  Keyword Arguments:
    filePath (string): The path to the file specifying the game world.

  Returns:
    World Object
  */
  buildGameBoard(filePath);
}

World::~World()
{
  /*
  Basic deconstructor of the World class.
  */
  if (gameboard != NULL) {
    delete gameboard;
  }
  if (startPos != NULL) {
    delete startPos;
  }
  if (goalPos != NULL) {
    delete goalPos;
  }
}

void World::buildGameBoard(string filePath)
{
  /*
  Builds the gameboard information using the given file.  The program creates
  a file reader with the file, then uses the first line to get the size of the
  game board.  The program then iterates through the rowas and columns of the
  input file, reading in the characters and assigning a corresponding number.

  Keyword Arguments:
    filePath (string): A path to the file to be used to specify the world.
  */
  ifstream fin;
  fin.open(filePath);
  if (fin.is_open()) {
    char *gameboardSizeStr = new char[20];
    fin.getline(gameboardSizeStr, '\n');
    gameboardSize = atoi(gameboardSizeStr);
    string locations;
    gameboard = new int*[gameboardSize];
    for (int i = 0; i < gameboardSize; ++i) {
      getline(fin, locations);
      int* toAdd = new int[gameboardSize];
      for (int j = 0; j < gameboardSize; ++j) {
        char curr = locations[j];
        if (curr == '.') {
          // Traversable
          toAdd[j] = 0;
        } else if (curr == 'i') {
          // Initial space
          toAdd[j] = 1;
          startPos = new pair<int, int>(j, i);
        } else if (curr == 'g') {
          toAdd[j] = 2;
          goalPos = new pair<int, int>(j, i);
        } else {
          toAdd[j] = 3;
        }
      }
      gameboard[i] = toAdd;
    }
  }
}

void World::printGameboard(list<pair<int, int>> *navPath)
{
  /*
  Prints the gameboard to the console.  The program takes in a "navPath" object
  to place movement coins onto the gameboard as it is printed.

  Keyword Argument:
    navPath (list<pair<int, int>>): A list of all the positions visited by the
      robot.
  */
  map<pair<int, int>, int> *path = new map<pair<int, int>, int>();
  for (int l = 0; l < navPath->size(); ++l) {
    pair<int, int> toCycle = navPath->front();
    path->insert({toCycle, 1});
    navPath->pop_front();
    navPath->push_back(toCycle);
  }
  cout << "-- Current Board Position --\n";
  for (int i = 0; i < gameboardSize; ++i) {
    for (int j = 0; j < gameboardSize; ++j) {
      if (gameboard[i][j] == 1) {
        cout << "i";
      } else if (gameboard[i][j] == 2) {
        cout << "g";
      } else if (path->find({j, i}) != path->end()) {
        cout << "o";
      } else if (gameboard[i][j] == 0) {
        cout << ".";
      } else {
        cout << "+";
      }
    }
    cout << "\n";
  }
  delete path;
}

pair<int, int> World::getStartPos()
{
  /*
  Accessor method for the starting position.
  */
  return *startPos;
}

pair<int, int> World::getGoalPos()
{
  /*
  Accessor method for the goal position.
  */
  return *goalPos;
}

int World::evaluatePos(int x, int y)
{
  /*
  Accessor method for a position on the game board.
  */
  if (0 <= x && x < gameboardSize && 0 <= y && y < gameboardSize)
  {
    return gameboard[y][x];
  } else {
    return 3;
  }

}

int World::getGameBoardSize()
{
  /*
  Accessor method for the dimension of the game board.
  */
  return gameboardSize;
}
