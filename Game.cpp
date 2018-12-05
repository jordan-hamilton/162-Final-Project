#include "Game.hpp"

using std::cout;
using std::endl;
using std::string;

/***********************************************************************************************
** Description: Default constructor that initializes data members and adds options to menus.
***********************************************************************************************/
Game::Game() {

  maxRows = 20;
  maxCols = 20;
  actionMenu = new Menu("What would you like to do in this area?");;
  dirMenu = new Menu("Select a direction to explore:");
  hikerRescued  = false;
  radioFound = false;
  populateMenus();
  player = nullptr;
  currentSpace = nullptr;
  map = nullptr;

}


/***********************************************************************************************
** Description: Destructor that calls delete on pointers to free dynamically allocated memory
** using the endGame function if this step has not been completed at the end of the play method.
** Memory for Menu objects is freed if the menus are valid pointers.
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


/***********************************************************************************************
** Description: This method runs the game by first displaying the rules and objective of the
** game, then defining a boolean to store results of player actions and an integer to store
** the selected choice from game menus. A new player object is allocated and assigned to the
** player data member, and a dynamically allocated 2D array of random space objects is created
** to set the player and hiker at random spaces in the array. The itemStore vector is filled
** with random item names that the player can collect during the game. The map is displayed to
** the user, then a do-while loop prompts the user to move to a different space, search in the
** current space, use an item in the backpack, or view the map again. If the player attempts to
** move out of bounds, an error message is displayed. Otherwise, the movePlayer function is
** passed an integer corresponding to a direction to set the player's current space to the
** pointer associated with that direction, as long as the player's energy hasn't fallen below 0.
** If the player tries to search in a location already set as searched, an error message is
** displayed, otherwise, the search function is called on the currentSpace pointer. If the
** player has no energy remaining but has found the radio, the game verifies if they have
** any other items besides the radio and if they would still need to move to reach the hiker.
** If so, the item is removed and the game ends.
***********************************************************************************************/
void Game::play() {

  printScenario();

  bool actionResult;

  int actionChoice;

  player = new Player;

  createMap();

  populateItemStore();

  setStartingLocation();

  printMap();

  do {

    printStats();

    actionChoice = actionMenu->getIntFromPrompt(1, actionMenu->getMenuChoices(), true);

    cout << endl;

    switch (actionChoice)  {

      case 1 :  if ( currentSpace->wasSearched() ) {

                  cout << "You've already searched this area." << endl;
                  cout << "Try moving somewhere else if you'd like to search again." << endl << endl;

                } else if ( !player->getBackpack()->hasRoom() ){

                  cout << "You have too much in your backpack to search here." << endl;
                  cout << "Use some items before searching here." << endl << endl;

                } else {

                  currentSpace->search();

                  if ( currentSpace->wasItemScavenged() ) {
                    addItemToBackpack();
                  }

                }

                break;

      case 2 :  if (player->hasEnergy()) {

                  actionResult = movePlayer(dirMenu->getIntFromPrompt(1, dirMenu->getMenuChoices(), true));

                  if (!actionResult) {

                    cout << "Going this direction will take you off the map." << endl;
                    cout << "Pick another direction if you'd like to keep exploring." << endl << endl;

                  }

                } else {

                  cout << "You don't have enough energy to keep moving." << endl;
                  cout << "Use some items in your backpack to replenish your energy." << endl << endl;

                }

                break;

      case 3 :  if ( player->getBackpack()->hasItems() ) {
                  useItem();
                } else {
                  cout << "You don't have any items in your backpack." << endl;
                  cout << "Start searching areas to scavenge more items." << endl << endl;
                }

                break;

      case 4 :  printMap();
                break;

    }

    if (!player->hasEnergy() && radioFound) {

      if ( player->getBackpack()->getItemCount() == 1 && !currentSpace->isHikerHere() ) {
        player->getBackpack()->removeItem(0);
      }

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
** Description: This method is called if an area's search successfully returned an item to add
** to the player's backpack. A random item at an index in the itemStore is added to the player's
** backpack with a random value, which is used to restore energy when used by the player.
** If the random item is the radio, that item is added with a value of 0 to distinguish it from
** consumables and it is removed from the itemStore so it can't be added to the backpack twice.
** Otherwise, the item is added to the backpack using the addItem function to add an item with
** a random value between 1 and 5.
***********************************************************************************************/
void Game::addItemToBackpack() {

  int itemNumber = generateNumber( itemStore.size() );

  string itemToAdd = itemStore.at(itemNumber);

  if (itemToAdd == "Radio") {

    player->getBackpack()->addItem( itemToAdd, 0 );

    itemStore.erase(itemStore.begin() + itemNumber);

    radioFound = true;

  } else {

    player->getBackpack()->addItem( itemToAdd, generateNumber(5) + 1 );

  }

  cout << "You found: " << itemToAdd << endl;

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
** Description: This method creates the map by creating a 2D array of space objects, randomly
** choosing the type of inherited class for each element in the array using a switch statement.
** If the space is not in the first row it is linked the the space above it using setNorth and
** setSouth methods in the adjacent spaces. Similarly, spaces in adjacent columns after the
** first column are linked using setEast and setWest methods.
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
** played. The currentSpace is set to null and the itemStore is cleared so the radio can be
** readded by playing again. Variables for whether the hiker was rescued and whether the radio
** was found are reset as well, so their states aren't carried over if the player begins a new
** game.
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

  itemStore.clear();

  hikerRescued = false;
  radioFound = false;

}


/***********************************************************************************************
** Description: Takes a constant reference to an integer for the number of possible random
** values that could be returned (between 0 and one less than the passed integer), then
** generates and returns a random integer between 0 and 1 less than that value.
***********************************************************************************************/
int Game::generateNumber(const int &possibilities) {
  return rand() % possibilities;
}


/***********************************************************************************************
** Description: Takes a constant reference to an integer, then checks if the player has enough
** energy to make a move. If the player's energy is above 0 and the direction the player wishes
** to move is a valid pointer, the current space is set to that space, then the player's energy
** is drained by the cost of moving to that new space. If the player was able to move, the
** original and current spaces are updated to reflect the player's updated location. If the
** hiker is at the updated location, the hikerRescued boolean is set to true.
***********************************************************************************************/
bool Game::movePlayer(const int &wayToMove) {

  bool couldMove = false;

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

    if ( currentSpace->isHikerHere() ) {

      cout << "You found the hiker!" << endl;
      cout << "Use your radio from this location to call for help and win the game." << endl;
      cout << "If you haven't found your radio yet, keep searching and return here to use it \
once you're ready." << endl;

    }

  }

  return couldMove;

}


/***********************************************************************************************
** Description: This method adds names for potential items that can be found while searching
** an area into the itemStore vector, so a successful search for an item allows an item with
** that name to be added to the player's backpack.
***********************************************************************************************/
void Game::populateItemStore() {

  itemStore.push_back("Ants");
  itemStore.push_back("Berries");
  itemStore.push_back("Cattails");
  itemStore.push_back("Fish");
  itemStore.push_back("Rabbit");
  itemStore.push_back("Radio");
  itemStore.push_back("Squirrel");
  itemStore.push_back("Slugs");
  itemStore.push_back("Water");
  itemStore.push_back("Worms");

}


/***********************************************************************************************
** Description: This method adds appropriate options to the menus for potential actions after
** an action is completed, and directions for the player to move if they choose the Move action.
***********************************************************************************************/
void Game::populateMenus() {

  actionMenu->addMenuItem("Search this area");
  actionMenu->addMenuItem("Move to a new area");
  actionMenu->addMenuItem("Use an item in your backpack");
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
without searching the area where you're located,\nbut you need to search until you find your \
radio so you can call for help once you find the hiker. You may also become too fatigued to find \
the missing hiker if you don't strategically choose which areas to explore.\n\nAreas:\n";

  string yourLocation = "* - Your Location\nFrom your location, you can search or move \
to another area on the map, including the areas you've already visited.\nYou can't search in \
the same area twice.\nSearching can unearth valuable goods to replenish your energy, which \
allows you to continue your search.\nSearching can also reveal the radio you need to have in \
your backpack so you can call for help once you've located the hiker.\nSurrounding areas you \
haven't explored yet can also be revealed by searching, which can prepare you for the type of \
terrain you'll encounter,\nor even allow you to spot the lost hiker if he's close.\nIf your \
backpack is too heavy from the items you collect while searching, you'll have to use some of \
your items if you wish to continue searching.\nDifferent types of terrain take more energy to \
traverse, so choose your path and the areas you want to search wisely.\n\n";

  string unexplored = "? - Unexplored Area\nThis area hasn't been revealed yet.\nYou reveal \
unexplored areas by moving to them, or by searching from your current location for a chance \
to reveal nearby areas.\nYour chances of revealing a nearby area vary depending on the type \
of terrain in your current location.\n\n";

  string brush = "# - Brush\nYou expend 2 energy points navigating through brush.\nThick \
brush is hard to see through, so searching only has a chance to reveal 1 unexplored \
adjacent space.\nYou have a 1 in 2 chance of finding hidden items to add to your backpack \
that help replenish your energy, though.\nYou might even find the radio you lost, which you \
need so you can call for help and win the game.\n\n";

  string camp = "@ - Camp\nYou don't expend any energy visiting a campsite.\nSearching a camp \
will randomly reveal 1 unexplored area to your north, south, east or west.\nCamps have a 3 \
in 4 chance of providing some item to store in your backpack.\n\n";

  string clearing = "_ - Clearing\n You expend 1 energy point going through a clearing.\n\
Searching from a clearing has a chance to reveal 1 or 2 unexplored areas.\nClearings have \
roughly a 1 in 3 chance of providing something to add to your backpack.\n\n";

  string peak = "^ - Peak\nYou expend 3 energy points climbing a peak.\nA search from this \
height will reveal all unexplored areas to the north, south, east and west.\nAt these heights, \
you'll only have a 1 in 5 chance of finding something to add to your backpack.\n\n";

  cout << objective << yourLocation << unexplored << brush << camp << clearing << peak;

}


/***********************************************************************************************
** Description: This method outputs the player's energy, the terrain type at their current
** location, so the player can choose whether to search or move from this location for a better
** view and/or better chance of finding items.
***********************************************************************************************/
void Game::printStats() {

  cout << "Your Energy: " << player->getEnergy() << endl;
  cout << "Current Terrain: " << currentSpace->getType() << endl;
  cout << "Items: " << player->getBackpack()->getItemCount() << "/" << player->getBackpack()->getItemLimit() << endl << endl;

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


/***********************************************************************************************
** Description: This method prompts the user to select an item from the backpack to use to
** restore energy. The player's energy is restored by the item's value. If the item selected is
** the radio and the player is not in the same area as the hiker, an error message is displayed.
** Otherwise, the hikerRescued variable is set to true.
***********************************************************************************************/
void Game::useItem() {

  int choice;

  player->getBackpack()->printItems();

  choice = actionMenu->getIntFromPrompt("Which item would you like to use?", 1, player->getBackpack()->getItemCount(), false);

  if ( player->getBackpack()->getItemValue(choice - 1) != 0) {

    cout << "You added " << player->getBackpack()->getItemValue(choice - 1) << " points to your energy." << endl;
    player->restoreEnergy( player->getBackpack()->getItemValue(choice - 1) );
    player->getBackpack()->removeItem(choice - 1);

  } else if ( !currentSpace->isHikerHere() ) {

    cout << "You must be in the same area as the hiker to use your radio." << endl;

  } else {

    hikerRescued = true;

  }

}


bool Game::getHikerRescued() {
  return hikerRescued;
}


void Game::setHikerRescued(const bool &hikerState) {
  hikerRescued = hikerState;
}
