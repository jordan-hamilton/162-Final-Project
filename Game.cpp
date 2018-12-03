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
  actionMenu = nullptr;
  dirMenu = nullptr;
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

  string prompt = "\nWelcome to Search & Rescue!\n\nYou're a wilderness survival expert searching \
for a lost hiker.\nYour goal is to explore the terrain in search of the lost hiker before you run \
out of energy.\nAs you explore, you can search your current location for sustenance and try to \
scout out your surroundings.\nYou can also try to explore the map without searching the area where \
you're located, but you may become too fatigued to find the missing hiker if you don't strategically \
choose which areas to explore.\n\n";

  string key = "Map Key:\n* - Your Location\nFrom your location, you can search or move to another \
area on the map, including the areas you've already explored. You can't search in the same area \
twice. Searching can unearth valuable goods to replenish your energy, which allows you to continue \
your search. Searching can also reveal surrounding areas you haven't explored yet and prepare you \
for the type of terrain you'll encounter, or even allow you to spot the lost hiker if he's close. \
Different types of terrain take more energy to traverse, so choose your path wisely.\n\? - \
Unexplored Area\nThis area hasn't been revealed yet. If it's near your current location, you can \
search to try to reveal the type of terrain here and look for the hiker, or you can move to this \
location to reveal it on the map.\n# - Brush\nYou expending 2 energy points navigating through \
brush. Thick brush is hard to see through, so searching rarely reveals your surroundings. You \
may find some hidden items that help replenish your energy, though.\n@ - Camp\nYou don't expend \
any energy visiting a campsite. Searching here will always reveal 1 unexplored area to your north, \
south, east or west, and can usually provide some good loot if you're low on energy. \n_ - Clearing \
\n You expend 1 energy point going through a clearing. Searching from a clearing might reveal 1 or 2 \
unexplored areas, but usually doesn't provide anything to replenish your energy. \n^ - Peak\nYou \
expend 3 energy points climbing a peak, but a search from this height will reveal all unexplored \
areas to the north, south, east and west. At these heights, you probably won't find much to replenish \
your energy.";

  cout << prompt << key << endl;

  player = new Player;
  createMap();

  setStartingLocation();

  printMap();

  endGame();

}


/***********************************************************************************************
** Description: This method randomly selects a side of the map for to start the player on, then
** selects a random Space on that side of the map for that player to be placed to start from.
** Then, a random space on the map is selected as the location for the missing hiker, as long as
** that space is not the same as the player's starting location.
***********************************************************************************************/
void Game::setStartingLocation() {
  int hikerRow = generateNumber(maxRows);
  int hikerCol = generateNumber(maxCols);

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

  while (player->getRow() == hikerRow && player->getCol() == hikerCol) {
    hikerRow = generateNumber(maxRows);
    hikerCol = generateNumber(maxCols);
  }

  map[hikerRow][hikerCol]->setHikerHere(true);

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
      // Set the north of current space to the space above it, and set south of one above to the current
      if (i > 0) {
        map[i][j]->setNorth(map[i - 1][j]);
        map[i - 1][j]->setSouth(map[i][j]);
      }

      if (j > 0) {
        map[i][j]->setWest(map[i][j - 1]);
        map[i][j - 1]->setEast(map[i][j]);
      }

    }

  }

  cout << "map[0][24]'s south space type: " << map[0][24]->getSouth()->getType() << endl;
  cout << "map[24][0]'s north space type: " << map[24][0]->getNorth()->getType() << endl;
  cout << "map[0][0]'s east space type: " << map[0][0]->getEast()->getType() << endl;
  cout << "map[0][24]'s west space type: " << map[0][24]->getWest()->getType() << endl;

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
** location and energy for the player and the map layout can be reset if another game is
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
