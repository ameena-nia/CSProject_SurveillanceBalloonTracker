/*
File: proj1.cpp
Project: CMSC 202 Project 1, Spring 2023
Author: Ameena Niamathullah
Date: 2/14/2023
Section: 13
E-mail: hx86253@umbc.edu

Description: This file contains the main driver program for Project 1.This
program will develop the code to create a large map. Based on the map, a balloon
will be hidden somewhere in the map. The user will then guess coordinates for
where the balloon exists. If the user is not successful in guessing where the
balloon is, the application will indicate which direction the balloon is (north,
south, east, or west).
*/

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
using namespace std;

const string guess = " G ";    // string for marked/guessed coordinates
const string notGuess = " $ "; // string for unmarked coordinates

const int width = 20;  // num of grid rows
const int height = 20; // num of grid columns

// prints the map which will show you $ if
// that spot hasn't been guessed or a G if
// that spot has been guessed.
void printMap(string grid[width][height]);

// randomly places the balloon in a random
// location on the map (not visible)
int startBalloon();

// resets the map to all $
void resetMap(string grid[width][height]);

// allows user to enter an x and y location to see if balloon exists there.
// the guess must be a valid value between 0 and 19 (20x20 grid).
int guessLocation(int startX, int startY, string grid[width][height]);

/*
based on guessed location, indicates which direction the balloon is.
if the guess is not on the correct north/south, the function will always
indicate if the balloon is north or south of the current guess.
once the north/south value is correct, then this function will return
the east/west direction.
*/
void guessDirection(int userXGuess, int userYGuess, int startX, int startY);

int main() {
  // seeding the randomizer
  srand(time(NULL));

  // main map
  string gridMap[width][height];
  resetMap(gridMap);

  int xCoordinate, yCoordinate; // variables for balloon's randomized coordinates
  xCoordinate = startBalloon();
  yCoordinate = startBalloon();

  cout << "Welcome to the Surveillance Balloon Tracker!" << endl;
  cout << "You are searching for the survellance balloon." << endl;

  int userChoice; // variable for user input

  // using a while loop that will continue to ask the user
  // how they would like to proceed with the program.
  while (userChoice != 3) {
    cout << "What would you like to do?" << endl;
    cout << "1. Display Map" << endl;
    cout << "2. Guess Location of Balloon" << endl;
    cout << "3. Exit" << endl;
    cin >> userChoice;

    // using a switch statement to keep track of the different function calls
    // for each number the user decides to choose from the list of choices.
    switch (userChoice) {

    case 1:
      printMap(gridMap);
      break;

    case 2:
      guessLocation(xCoordinate, yCoordinate, gridMap);
      break;

    case 3:
      cout << "Thank you for using the Surveillance Balloon Tracker!" << endl;
      break;
    }
  }
  return 0;
}

int startBalloon() {
  // Name: startBalloon
  // Pre-Condition: None
  // Post-Condition: Returns a random number between 0 and 19.

  return rand() % 20;
}

void printMap(string grid[width][height]) {
  // Name: printMap
  // Pre-Condition: the 20 x 20 grid is empty
  // Post-Condition: the 20 x 20 grid will be printed out
  // and will add '$' or 'G' based on user guess.

  int row;     // keeps track of grid width - outer loop
  int column;  // keeps track of grid height - inner loop
  string line; // this string will contain all the '$'

  cout << " ";

  // this for-loop creates the column list (x-axis)
  for (row = 0; row < width; row++) {
    cout << setw(3);
    cout << row;
  }
  cout << endl;

  // this for-loop creates the actual map (with the '$')
  // the outer loop will print out all of the row numbers (y-axis)
  for (row = 0; row < width; row++) {

    if (row >= 0 and row <= 9) {
      cout << setw(2); // padding single digits with a space
      cout << row;

    } else if (row >= 10 and row <= 19) {
      cout << row;
    }
    line = "";

    // the inner loop will concatenate the strings in order
    // to print out the '$' in list form.
    for (column = 0; column < height; column++) {
      line += grid[row][column];
    }
    cout << line << endl;
  }
}

int guessLocation(int startX, int startY, string grid[width][height]) {
  // Name: guessLocation
  // Pre-Condition: the 20 x 20 grid must be filled with '$' and the
  // starting coordinates must be randomized (between 0 - 19).
  // Post-Condition: prints out the whether user guessed correctly or
  // not and will insert a 'G' in the grid based on guessed coordinates.

  int xGuess, yGuess; // stores user coordinates between 0 - 19

  cout << "Where would you like to look for the balloon?" << endl;

  cout << "Enter the X coordinate (between 0 - 19) " << endl;
  cin >> xGuess;

  cout << "Enter the Y coordinate (between 0 - 19) " << endl;
  cin >> yGuess;

  // initializing the user's coordinate guess.
  // setting the value to 'G'
  grid[yGuess][xGuess] = guess;

  // conditions for when the user makes
  // a correct guess or a wrong guess.
  if (xGuess != startX || yGuess != startY) {
    cout << "You didn't find the balloon." << endl;

  } else {
    cout << "You found the balloon!" << endl;
  }

  // function call to specify the direction of the balloon
  // based on coordinates the user entered.
  guessDirection(xGuess, yGuess, startX, startY);

  return 0;
}

void guessDirection(int userXGuess, int userYGuess, int startX, int startY) {
  // Name: guessDirection
  // Pre-Condition: starting coordinates and guessed coordinates must
  // be between 0 and 19.
  // Post-Condition: prints out the direction of balloon depending
  // on the user's coordinates.

  // Case 1: (bigX, bigY)
  if (userXGuess > startX && userYGuess > startY) {
    cout << "The balloon is north of your guess." << endl;
  }
  // Case 2: (smallX, smallY)
  else if (userXGuess < startX && userYGuess < startY) {
    cout << "The balloon is south of your guess." << endl;
  }
  // Case 3: (bigX, smallY)
  else if (userXGuess > startX && userYGuess < startY) {
    cout << "The balloon is south of your guess." << endl;
  }
  // Case 4: (smallY, bigX)
  else if (userXGuess < startX && userYGuess > startY) {
    cout << "The balloon is north of your guess." << endl;
  }
  // Case 5: (smallX, sameY)
  else if (userXGuess < startX && userYGuess == startY) {
    cout << "The balloon is east of your guess." << endl;
  }
  // Case 6: (bigX, sameY)
  else if (userXGuess > startX && userYGuess == startY) {
    cout << "The balloon is west of your guess." << endl;
  }
  // Case 7: (sameX, smallY)
  else if (userXGuess == startX && userYGuess < startY) {
    cout << "The balloon is south of your guess." << endl;
  }
  // Case 8: (sameX, bigY)
  else if (userXGuess == startX && userYGuess > startY) {
    cout << "The balloon is north of your guess." << endl;
  }
}

void resetMap(string grid[width][height]) {
  // Name: resetMap
  // Pre-Condition: grid must be 20 x 20
  // Post-Condition: grid is filled with '$'

  int row;    // keeps track of grid width - outer loop
  int column; // keeps track of grid height - inner loop

  for (row = 0; row < width; row++) {
    for (column = 0; column < height; column++) {
      // to reset the map, each element is assigned with '$'
      grid[row][column] = notGuess;
    }
  }
}
