/***********************************************************************************************
** Program name: Final Project
** Author: Jordan Hamilton
** Date: 12/4/2018
** Description: This program seeds a random number generator, then creates new smart pointers
** to a Game object and a Menu object. The menu prompts the user to begin a game or exit. Once
** the game is started, the objective is displayed and the player randomly placed on an edge of
** the map, which is output to the screen. The player has the option to move to a different
** location on the map via pointers to adjacent spaces in each space object on the map. Moving
** to a new location marks the space as discovered, which allows the user to view the space
** on the map. The player can also search the current space for a chance to reveal adjacent
** spaces and search for items to add to their backpack. Items replenish energy, which is
** decreased as they move to adjacent spaces, with differing energy costs for different
** spaces. The player must search until finding the radio, while continuing to move around the
** map to reveal spaces, one of which has a trapped hiker in an unknown random location on the
** map. The player must conserve energy by selectively navigating to different spaces, searching
** to replenish energy, and then use the radio while in the same space as the hiker to win the
** game.
***********************************************************************************************/

#include <cstdlib>
#include <memory>

#include "Menu.hpp"
#include "Game.hpp"

using std::cout;
using std::endl;
using std::unique_ptr;

void populateMenu(unique_ptr<Menu> &menu);

/***********************************************************************************************
** Description: This program can be run via the finalproject executable generated by make.
***********************************************************************************************/
int main() {

  int choice;

  unsigned seed = time(0);
  srand(seed);

  unique_ptr<Game> wildernessGame( new Game() );

  unique_ptr<Menu> mainMenu( new Menu("Search & Rescue\nSelect an option to continue:") );
  populateMenu(mainMenu);

  do {

    choice = mainMenu->getIntFromPrompt(1, mainMenu->getMenuChoices(), true);

    cout << endl;

    switch (choice)  {

      case 1 : wildernessGame->play();

      default : {}

    }

    cout << endl;

  } while( choice != mainMenu->getMenuChoices() );

  return 0;

}


/***********************************************************************************************
** Description: This function takes a pointer to a Menu object, then calls the addMenuItem
** method to add the approprate menu options to the program's menu.
***********************************************************************************************/
void populateMenu(unique_ptr<Menu> &menu) {

  menu->addMenuItem("Begin a new game");
  menu->addMenuItem("Exit");

}
