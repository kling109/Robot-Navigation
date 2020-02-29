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

using namespace std;

int main(int argc, char **argv)
{
  // Check for correct number of arguments
  if (argc != 2) {
    cout << "Invalid arguments; run the program as './robotnavigation [FILEPATH]'";
    return 1;
  } else {
    // When the correct number of arguments is found, attempt to create the
    // World object.
    World *locationToNavigate = new World(argv[1]);
    Navigation *navTest = new Navigation(locationToNavigate);
    cout << "Using method 1:\n";
    navTest->navigate(1);
    cout << "\n";
    cout << "-------\n";
    cout << "\n";
    cout << "Using method 2:\n";
    navTest->navigate(2);
    cout << "\n";
    cout << "-------\n";
    cout << "\n";
    cout << "Using method 3:\n";
    navTest->navigate(3);
    cout << "\n";
    cout << "-------\n";
    cout << "\n";
    cout << "Using method 4:\n";
    navTest->navigate(4);
    delete navTest;
    delete locationToNavigate;
    return 0;
  }
}
