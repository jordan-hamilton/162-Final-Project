#include "Player.hpp"

/***********************************************************************************************
** Description: Default constructor that initializes data members.
***********************************************************************************************/
Player::Player() {
  backpack = new Pack;
  energy = 100;
}


/***********************************************************************************************
** Description: Destructor that deletes dynamically allocated memory for the backpack if the
** backpack is a valid pointer.
***********************************************************************************************/
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


/***********************************************************************************************
** Description: This method takes an integer representing the energy cost of a space the player
** just moved to, then decreases the player's energy by that amount.
***********************************************************************************************/
void Player::drainEnergy(const int &energyDrained) {
  energy -= energyDrained;
}


/***********************************************************************************************
** Description: This method takes an integer representing the value of an item the player
** has in the backpack, then increases the player's energy by the value of that item.
***********************************************************************************************/
void Player::restoreEnergy(const int &energyRestored) {
  energy += energyRestored;
}


/***********************************************************************************************
** Description: Returns a pointer to a pack object so the game can view the content's of the
** player's backpack, allowing items in the pack to be used during gameplay.
***********************************************************************************************/
Pack* Player::getBackpack() {
  return backpack;
}


int Player::getEnergy() {
  return energy;
}


void Player::setEnergy(const int &energyLeft) {
  energy = energyLeft;
}
