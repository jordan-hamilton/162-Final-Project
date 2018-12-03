#include "Player.hpp"

/***********************************************************************************************
** Description: Default constructor that initializes data members.
***********************************************************************************************/
Player::Player() {
  backpack = nullptr;
  energy = 100;
  row = 0, col = 0;
}


Player::~Player() {

  if (backpack) {
    delete backpack;
    backpack = nullptr;
  }

}


/***********************************************************************************************
** Description: Method that returns a boolean to indicate if the player still has energy to
** continue moving through the wilderness.
***********************************************************************************************/
bool Player::hasEnergy() {

  if (energy > 0) {
    return true;
  } else {
    return false;
  }

}


int Player::getEnergy() {
  return energy;
}


int Player::getRow() {
  return row;
}


int Player::getCol() {
  return col;
}


void Player::setEnergy(int energyLeft) {
  energy = energyLeft;
}


void Player::setRow(int rowIn) {
  row = rowIn;
}


void Player::setCol(int colIn) {
  col = colIn;
}
