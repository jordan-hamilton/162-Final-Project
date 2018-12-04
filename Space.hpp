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
    bool wasItemScavenged();
    bool wasSearched();
    char getIcon();
    int getEnergyCost();
    std::string getType();
    Space* getNorth();
    Space* getEast();
    Space* getSouth();
    Space* getWest();
    void setHikerHere(const bool &presenceStatus);
    void setPlayerHere(const bool &presenceStatus);
    void setNorth(Space* northIn);
    void setEast(Space* eastIn);
    void setSouth(Space* southIn);
    void setWest(Space* westIn);

  protected:
    virtual void scavenge() = 0;
    virtual void scout() = 0;
    bool revealSpace(Space* spaceToReveal);
    int getDiscoverableSpaces();
    int generateNumber(const int &possibilities);
    void setDiscovered(const bool &discoveryStatus);
    void setItemScavenged(const bool &itemStatus);
    void setSearched(const bool &searchStatus);
    void setIcon(const char &iconIn);
    void setEnergyCost(const int &cost);
    void setType(const std::string &terrainType);
    bool hikerHere, playerHere, discovered, itemScavenged, searched;
    char icon;
    int energyCost;
    std::string type;
    Space *north, *south, *east, *west;

};

#endif
