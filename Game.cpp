#include "Game.hpp"

using std::cout;
using std::endl;
using std::string;

/***********************************************************************************************
** Description: Default constructor that initializes data members.
***********************************************************************************************/
Game::Game() {

  maxRows = 20;
  maxCols = 20;
  actionMenu = new Menu("What would you like to do in this area?");;
  dirMenu = new Menu("Select a direction to explore:");
  populateMenus();
  player = nullptr;
  currentSpace = nullptr;
  map = nullptr;

}


/***********************************************************************************************
** Description: Destructor that calls delete on pointers to free dynamically allocated memory
** for the map and player if this step has not been completed at the end of the play method.
** Memory for Menu objects is freed is the menus are valid pointers.
***********************************************************************************************/
Game::~Game() {

  endGame();

  if (actionMenu) {
    delete actionMenu;
    actionMenu = nullptr;
  }

  if (dirMenu) {
    delete dirMenu;
    dirMenu = nullptr;
  }

}


void Game::play() {

  printScenario();

  bool actionResult;
  int actionChoice;
  player = new Player;
  createMap();

  setStartingLocation();

  printMap();

  do {

    printStats();

    actionChoice = actionMenu->getIntFromPrompt(1, actionMenu->getMenuChoices(), true);

    cout << endl;

    switch (actionChoice)  {

      case 1 :  if ( currentSpace->wasSearched() ) {

                  cout << "You've already searched this area." << endl;
                  cout << "Try moving somewhere else if you'd like to search." << endl << endl;

                } else if ( !player->getBackpack()->hasRoom() ){

                  cout << "You have too much in your backpack to conduct a search." << endl;
                  cout << "Use or discard some items if you'd like to search here." << endl << endl;

                } else {
                  currentSpace->search();
                }

                break;

      case 2 :  if (player->hasEnergy()) {

                  actionResult = movePlayer(dirMenu->getIntFromPrompt(1, dirMenu->getMenuChoices(), true));

                  if (!actionResult) {

                    cout << "Going this direction will take you off the map." << endl;
                    cout << "Pick another direction if you'd like to keep exploring." << endl;

                  }

                } else {

                  cout << "You don't have enough energy to keep moving." << endl;
                  cout << "Use some items in your backpack to replenish your energy." << endl << endl;

                }

                break;

      case 3 :  printMap();
                break;

    }

  } while( !hikerRescued && (player->hasEnergy() || player->getBackpack()->hasItems()) );

  if (hikerRescued) {
    cout << "Congratulations! You saved the hiker!" << endl;
  } else {
    cout << "You ran out of energy and weren't able to save the hiker. Please try again." << endl;
  }

  endGame();

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
** Description: This method randomly selects a side of the map for to start the player on, then
** selects a random Space on that side of the map for that player to be placed to start.
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

  currentSpace = nullptr;

  if (player) {
    delete player;
    player = nullptr;
  }

}


/***********************************************************************************************
** Description: Takes a constant reference to an integer for the maximum random value to return,
** then generates and returns a random integer between 0 and 1 less than that value.
***********************************************************************************************/
int Game::generateNumber(const int &max) {
  return rand() % max;
}


/***********************************************************************************************
** Description: Takes a constant reference to a Direction, then checks if the player has enough
** energy to make a move. If the player's energy is above 0 and the direction the player wishes
** to move is a valid pointer, the current space is set to that space, then the player's energy
** is drained by the cost of moving to that new space. If the player was able to move, the
** original and current spaces are updated to reflect the player's updated location.
***********************************************************************************************/
bool Game::movePlayer(const int &wayToMove) {

  bool couldMove = false;

  if ( player->hasEnergy() ) {

    Space* originalSpace = currentSpace;

    switch (wayToMove - 1) {
      case North  : if ( currentSpace->getNorth() ) {
                      currentSpace = currentSpace->getNorth();
                    }
                    break;

      case East   : if ( currentSpace->getEast() ) {
                      currentSpace = currentSpace->getEast();
                    }
                    break;

      case South  : if ( currentSpace->getSouth() ) {
                      currentSpace = currentSpace->getSouth();
                    }
                    break;

      case West   : if ( currentSpace->getWest() ) {
                      currentSpace = currentSpace->getWest();
                    }

    }

    if (originalSpace != currentSpace) {

      originalSpace->setPlayerHere(false);
      currentSpace->setPlayerHere(true);
      player->drainEnergy( currentSpace->getEnergyCost() );
      couldMove = true;

    }

  }

  return couldMove;

}


/***********************************************************************************************
** Description: This method adds appropriate options to the menus for potential actions after
** an action is completed, and directions for the player to move if they choose the Move action.
***********************************************************************************************/
void Game::populateMenus() {

  actionMenu->addMenuItem("Search this area");
  actionMenu->addMenuItem("Move to a new area");
  actionMenu->addMenuItem("View the map");

  dirMenu->addMenuItem("North");
  dirMenu->addMenuItem("East");
  dirMenu->addMenuItem("South");
  dirMenu->addMenuItem("West");

}


/***********************************************************************************************
** Description: This method loops through the 2D array for the map, printing the icon at the
** for the space pointer's terrain type at that location, depending on whether that space has
** been marked as discovered, if the player or hiker is currently at that space, and the type
** of terrain.
***********************************************************************************************/
void Game::printMap() {
  for (int i = 0; i < maxRows; i++) {

    for (int j = 0; j < maxCols; j++) {
      cout << map[i][j]->getIcon() << " ";
    }
    cout << endl;
  }

  printMapKey();

}


/***********************************************************************************************
** Description: This method outputs the map's key, so the player is aware of what different
** icons mean on the map that was printed.
***********************************************************************************************/
void Game::printMapKey() {

  cout << "* - Your location" << endl;
  cout << "! - Hiker's location" << endl;
  cout << "? - Unexplored area" << endl;
  cout << "# - Brush" << endl;
  cout << "@ - Camp" << endl;
  cout << "_ - Clearing" << endl;
  cout << "^ - Peak" << endl << endl;

}


/***********************************************************************************************
** Description: This method outputs the game's information to the screen, so the player is
** aware of the objective and rules.
***********************************************************************************************/
void Game::printScenario() {

  string objective = "\nWelcome to Search & Rescue!\n\nYou're a wilderness survival expert \
searching for a trapped hiker.\nYour goal is to explore the terrain in search of the trapped \
hiker before you run out of energy.\nAs you explore, you can search your current location for \
sustenance and try to scout out your surroundings.\nYou can also try to explore the map \
without searching the area where you're located, but you may become too fatigued to find the \
missing hiker if you don't strategically choose which areas to explore.\n\nAreas:\n";

  string yourLocation = "* - Your Location\nFrom your location, you can search or move \
to another area on the map, including the areas you've already visited.\nYou can't search in \
the same area twice.\nSearching can unearth valuable goods to replenish your energy, which \
allows you to continue your search.\nSearching can also reveal surrounding areas you haven't \
explored yet and prepare you for the type of terrain you'll encounter, or even allow you to \
spot the lost hiker if he's close.\nIf your backpack is too heavy from the items you collect \
while searching, you'll have to use or discard some items if you wish to continue searching.\n\
Different types of terrain take more energy to traverse, so choose your path and the areas you \
want to search wisely.\n\n";

  string unexplored = "? - Unexplored Area\nThis area hasn't been revealed yet.\nYou reveal \
unexplored areas by moving to them, or by searching from your current location for a chance \
to reveal nearby areas.\nYour chances of revealing a nearby area vary depending on the type \
of terrain in your current location.\n\n";

  string brush = "# - Brush\nYou expend 2 energy points navigating through brush.\nThick \
brush is hard to see through, so searching only has a chance to reveal 1 unexplored \
adjacent space.\nYou may find some hidden items that help replenish your energy, though.\n\n";

  string camp = "@ - Camp\nYou don't expend any energy visiting a campsite.\nSearching a camp \
will randomly reveal 1 unexplored area to your north, south, east or west.\nCamps can usually \
provide some good loot if you're low on energy.\n\n";

  string clearing = "_ - Clearing\n You expend 1 energy point going through a clearing.\n\
Searching from a clearing has a chance to reveal 1 or 2 unexplored areas.\nClearings usually \
don't provide anything to replenish your energy.\n\n";

  string peak = "^ - Peak\nYou expend 3 energy points climbing a peak.\nA search from this \
height will reveal all unexplored areas to the north, south, east and west.\nAt these heights, \
you probably won't find much to replenish your energy.\n\n";

  cout << objective << yourLocation << unexplored << brush << camp << clearing << peak;

}


/***********************************************************************************************
** Description: This method outputs the player's energy, the terrain type at their current
** location, so the player can choose whether to search or move from this location for a better
** view and/or better chance of finding items.
***********************************************************************************************/
void Game::printStats() {

  cout << "Your Energy: " << player->getEnergy() << endl;
  cout << "Current Terrain: " << currentSpace->getType() << endl << endl;

}


/***********************************************************************************************
** Description: This method randomly selects a side of the map for to start the player on, then
** selects a random Space on that side of the map for that player to be placed to start from.
** Then, a random space on the map is selected as the location for the missing hiker, as long as
** that space is not the same row or column as the player's starting location.
***********************************************************************************************/
void Game::setStartingLocation() {
  int hikerRow = generateNumber(maxRows);
  int hikerCol = generateNumber(maxCols);
  int playerRow = generateNumber(maxRows);
  int playerCol = generateNumber(maxCols);

  switch ( generateNumber(4) ) {

    case North: currentSpace = map[0][playerCol];
                break;
    case East:  currentSpace = map[playerRow][maxCols - 1];
                break;
    case South: currentSpace = map[maxRows - 1][playerCol];
                break;
    case West:  currentSpace = map[playerRow][0];
                break;
  }

  currentSpace->setPlayerHere(true);

  while (playerRow == hikerRow || playerCol == hikerCol) {
    hikerRow = generateNumber(maxRows);
    hikerCol = generateNumber(maxCols);
  }

  map[hikerRow][hikerCol]->setHikerHere(true);

}


bool Game::getHikerRescued() {
  return hikerRescued;
}


void Game::setHikerRescued(const bool &hikerState) {
  hikerRescued = hikerState;
}
