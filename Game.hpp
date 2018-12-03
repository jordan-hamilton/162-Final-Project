/*********************************************************************
** Description: Specification file for the Game class.
*********************************************************************/

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>

#include "Brush.hpp"
#include "Camp.hpp"
#include "Clearing.hpp"
#include "Menu.hpp"
#include "Peak.hpp"
#include "Player.hpp"
#include "Space.hpp"

class Game {

  public:
    Game();
    ~Game();
    void play();

  private:
    int maxRows, maxCols;
    void createMap();
    void cleanMap();
    void endGame();
    void printMap();
    void setStartingLocation();
    int generateNumber(const int &max);
    Menu *actionMenu, *dirMenu;
    Player *player;
    Space*** map;

};

#endif
