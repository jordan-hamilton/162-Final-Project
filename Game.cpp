#include "Game.hpp"

using std::cout;
using std::endl;
using std::string;

enum Direction {North, East, South, West};
enum SpaceType {brushSpace, campSpace, clearingSpace, peakSpace};

/***********************************************************************************************
** Description: Default constructor that initializes data members.
***********************************************************************************************/
Game::Game() {
  maxRows = 25;
  maxCols = 25;
  player = nullptr;
  map = nullptr;
}


/***********************************************************************************************
** Description: Destructor that calls delete on pointers to free dynamically allocated memory
** for the map and player if this step has not been completed at the end of the play method.
***********************************************************************************************/
Game::~Game() {
  endGame();
}


void Game::play() {

  string prompt = "\nWelcome to Search & Rescue!\n\nYou're a wilderness survival expert searching for \
a lost hiker.\nYour goal is to explore the wilderness in search of the lost hiker before you run out \
of energy.\nAs you explore, you can search your current location for sustenance and try to scout out \
your surroundings.\nYou can also try to explore the map without searching, but you may become too \
fatigued to find the missing hiker if you don't strategically choose which areas to explore.";

  cout << prompt << endl;

  player = new Player;
  createMap();

  setStartingLocation();

  printMap();

  endGame();

}


/***********************************************************************************************
** Description: This method randomly selects a side of the map for to start the player on, then
** selects a random Space on that side of the map for that player to be placed to start from.
***********************************************************************************************/
void Game::setStartingLocation() {

  switch ( generateNumber(4) ) {

    case North: player->setRow(0);
                player->setCol( generateNumber(maxCols) );
                break;
    case East:  player->setRow( generateNumber(maxRows) );
                player->setCol( maxCols - 1 );
                break;
    case South: player->setRow( maxRows - 1 );
                player->setCol( generateNumber(maxCols) );
                break;
    case West:  player->setRow( generateNumber(maxRows) );
                player->setCol(0);
                break;
  }

  map[player->getRow()][player->getCol()]->setPlayerHere(true);

}


/***********************************************************************************************
** Description: This method randomly selects a side of the map for to start the player on, then
** selects a random Space on that side of the map for that player to be placed to start from.
***********************************************************************************************/
void Game::createMap() {

  map = new Space**[maxRows];

  for (int i = 0; i < maxRows; i++) {

    map[i] = new Space*[maxCols];

    for (int j = 0; j < maxCols; j++) {

      switch ( generateNumber(4) ) {

        case brushSpace:    map[i][j] = new Brush;
                            break;
        case campSpace:     map[i][j] = new Camp;
                            break;
        case clearingSpace: map[i][j] = new Clearing;
                            break;
        case peakSpace:     map[i][j] = new Peak;
                            break;

      }

    }

  }

}


/***********************************************************************************************
** Description: Loops through the 2D array to free dynamically allocated memory for Space
** objects.
***********************************************************************************************/
void Game::cleanMap() {

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


/***********************************************************************************************
** Description: This method resets the map and player at the end of the play method, so the
** positions and energy for the character and the map layout can be reset if another game is
** played.
***********************************************************************************************/
void Game::endGame() {

  if (map) {
    cleanMap();
  }

  if (player) {
    delete player;
    player = nullptr;
  }

}


void Game::printMap() {
  for (int i = 0; i < maxRows; i++) {

    for (int j = 0; j < maxCols; j++) {
      cout << map[i][j]->getIcon() << " ";
    }
    cout << endl;
  }

}

/***********************************************************************************************
** Description: Takes a constant reference to an integer for the maximum random value to return,
** then generates and returns a random integer between 0 and that value.
***********************************************************************************************/
int Game::generateNumber(const int &max) {
  return rand() % max;
}

  /*
  1st space:  if row is not 0, setNorth (row - 1) and setSouth (row - 1) to i

  if col is not 0, setWest(col - 1) and setEast of (col - 1) to i

  */
