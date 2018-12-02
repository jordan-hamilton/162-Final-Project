#include "Game.hpp"

enum Direction {North, South, East, West};
enum SpaceType {brush, camp, clearing, peak};

Game::Game() {
  maxRows = 25;
  maxCols = 25;
  map = nullptr;
  createMap();
}


Game::~Game() {

  for (int i = 0; i < maxRows; i++) {

   for (int j = 0; j < maxCols; j++) {
       delete map[i][j];
       map[i][j] = nullptr;
     }

     delete[] map[i];
     map[i] = nullptr;

   }

  delete [] map;
  map = nullptr;

}

void Game::setStartingLocation() {

}

void Game::createMap() {

  map = new Space**[maxRows];

  for (int i = 0; i < maxRows; i++) {

    map[i] = new Space*[maxCols];

    for (int j = 0; j < maxCols; j++) {
      map[i][j] = new Camp;
    }

  }
}


/***********************************************************************************************
** Description: Takes a constant reference to an integer for the maximum random value to return,
** then generates and returns a random integer between 0 and that value.
***********************************************************************************************/
int generateNumber(const int &max) {
  return rand() % max;
}

  /*
  1st space:  if row is not 0, setNorth (row - 1) and setSouth (row - 1) to i

  if col is not 0, setWest(col - 1) and setEast of (col - 1) to i

  */
