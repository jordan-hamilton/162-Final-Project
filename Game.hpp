/*********************************************************************
** Description: Specification file for the Game class.
*********************************************************************/

#ifndef GAME_HPP
#define GAME_HPP

#include "Brush.hpp"
#include "Camp.hpp"
#include "Clearing.hpp"
#include "Peak.hpp"
#include "Player.hpp"
#include "Space.hpp"

class Game {

  public:
    Game();
    ~Game();

  private:
    int maxRows, maxCols;
    void createMap();
    void setStartingLocation();
    int generateNumber(const int &max);
    Space*** map;

};

#endif
