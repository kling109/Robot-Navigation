# Robot-Navigation

A basic robot navigation program.

Trevor Kling

kling109@mail.chapman.edu

CPSC 390: Artificial Intelligence

Last Updated: 02/25/2020

## Introduction

This project implements a simple, heuristic-based robot navigation program.  The program takes in a path to file containing a formatted abstraction of an area to be navigated, then uses a variety of methods to determine a path from the starting position to one of the goal positions.  The four available methods of navigation are Euclidean Distance, Manhattan Distance, Euclidean Distance with prior costs, and Manhattan Distance with prior costs.  The program runs each of these methods, then prints the resulting path along with statistics.

## How to Run

To run, first compile the program using the `make` command.  Then, run the resulting program by typing `./robotnavigation [FILEPATH]` using whatever  desired file path.  Three sample board specifications are included with the program.

## Known Issues

None.
