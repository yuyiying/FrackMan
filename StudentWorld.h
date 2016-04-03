#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "Actor.h"
#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include "GraphObject.h"
#include <cmath>
#include <algorithm>
#include <queue>



// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
struct Coord
{
    int x;
    int y;
    int z;
    Coord(int a, int b, int c):x(a),y(b),z(c){}
};

class StudentWorld : public GameWorld
{
public:
    static StudentWorld* game;
    
    StudentWorld(std::string assetDir);
    
    ~StudentWorld()
    {
        cleanUp();
    }
    
    virtual int init();
    
    virtual int move();
    
    virtual void cleanUp();
    
    void addboulder();
    
    void addnugget();
    
    void addBarrel();
    
    bool IsdirtVisble(int i, int j);
    
    void setdirtInVisble(int i, int j,bool visble);
    
    Coord getFrackManCoord();
    
    int getleftBarrel() const;
    
    void barreldeclinde();
    
    void addNumgold();
    
    void addNumsquit();
    
    void addNumSonar();
    
    bool isBoulder(int i, int j);
    
    bool hitBoulder(int i, int j);
    
    void setDisplayText();
    
    void illuminate(int i, int j);
        
    void insertSquirt(int i, int j, GraphObject::Direction dir);
    
    bool isSquaredirt(int i, int j);
    
    bool isSmaBouler(int i, int j);
    
    void addGold(int i, int j);
    
    bool goldbyProtester(int i, int j);
    
    bool hitProtester(int i, int j);
    
    bool stunProtester(int i, int j);
    
    bool withinshout(int i, int j);
    
    bool IsfacingFrackMan(int i, int j,GraphObject::Direction dir);
    
    bool annoyFrackMan();
    
    bool isInlineOfSight(int i, int j);
    
    GraphObject::Direction FaceFrackMan(int i, int j);
    
    bool movedir(int i, int j,GraphObject::Direction dir);
    
    GraphObject::Direction Turnto(int i, int j, GraphObject::Direction dir);
    
    void updateMap(int x, int y, GraphObject::Direction m[64][64], int r);
    
    GraphObject::Direction protesterback(int& x,int& y);
    
    bool clearDirtBoulder(int i, int j);
    
    void decrementNumProtester();
    
private:
    Dirt* dirt[64][64];  //2-d array contain pointer;
    std::vector<Actor*> actor; // all the rest actors;
    FrackMan* frackman;
    int numBoulder; // number of the Boulder in each level
    int numBarrel;
    int numGold;
    int addGoodie;
    int addprotester;
    int numprotester;
    int radius;
    GraphObject::Direction direct[64][64];
    GraphObject::Direction mapToFrack[64][64];
};


#endif // STUDENTWORLD_H_
