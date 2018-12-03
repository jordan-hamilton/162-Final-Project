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

enum Direction {North, East, South, West};
enum SpaceType {brushSpace, campSpace, clearingSpace, peakSpace};

class Game {

  public:
    Game();
    ~Game();
    void play();

  private:
    int maxRows, maxCols;
    void cleanMap();
    void createMap();
    void displayStats();
    void endGame();
    bool movePlayer(const int &wayToMove);
    void populateMenus();
    void printMap();
    void setStartingLocation();
    int generateNumber(const int &max);
    bool getHikerRescued();
    void setHikerRescued(const bool &hikerState);
    bool hikerRescued;
    Menu *actionMenu, *dirMenu;
    Player *player;
    Space *currentSpace;
    Space*** map;

};

#endif
