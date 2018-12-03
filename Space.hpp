/*********************************************************************
** Description: Specification file for the Space class.
*********************************************************************/

#ifndef SPACE_HPP
#define SPACE_HPP

#include <string>

enum Direction {North, East, South, West};

class Space {

  public:
    Space();
    virtual ~Space();
    void search();
    bool isHikerHere();
    bool isPlayerHere();
    bool wasDiscovered();
    bool wasSearched();
    char getIcon();
    int getEnergyCost();
    std::string getType();
    Space* getNorth();
    Space* getEast();
    Space* getSouth();
    Space* getWest();
    void setHikerHere(bool presenceStatus);
    void setPlayerHere(bool presenceStatus);
    void setNorth(Space* northIn);
    void setEast(Space* eastIn);
    void setSouth(Space* southIn);
    void setWest(Space* westIn);

  protected:
    virtual void scavenge() = 0;
    virtual void scout() = 0;
    bool revealSpace(Space* spaceToReveal);
    int getDiscoverableSpaces();
    int generateNumber(const int &max);
    void setDiscovered(bool discoveryStatus);
    void setSearched(bool searchStatus);
    void setIcon(char iconIn);
    void setEnergyCost(int cost);
    void setType(std::string terrainType);
    bool hikerHere, playerHere, discovered, foundItem, searched;
    char icon;
    int energyCost;
    std::string type;
    Space *north, *south, *east, *west;

};

#endif
