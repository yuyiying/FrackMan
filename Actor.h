#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <algorithm>
#include <string>

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;


class Actor: public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0, bool Isvisble = false, bool alive = true, int istate = 0, std::string actname = "");
    
    virtual ~Actor(){}
    void setAlive(bool Isalive);
    
    void setState(int s);
    
    int getState() const;
    
    bool getAlive() const;
    
    int getimageID() const;
    
    virtual void doSomething()= 0;
    
    StudentWorld* getWorld();
    
    std::string getname() const;
private:
    bool IsAlive; // check whether the object is alive.(every object has a state)
    int state; // Boulder 0- stable, 1-waiting, 2-falling down
            //gold 0-frackman, 1-protester
            //sonar kit && water pool 0-temporary state
            //protester 0-normal, 1-level
    int imageId;
    std::string name;
    
    
};

class Dirt: public Actor
{
public:
    Dirt(int x = 0, int y = 0) : Actor(IID_DIRT,x,y,right,0.25,3,true,false,0,"dirt"){}
    virtual ~Dirt(){}
    virtual void doSomething(){}
};

class FrackMan : public Actor
{
public:
    FrackMan();
    virtual ~FrackMan(){}
    virtual void doSomething();
    void Movedirt();
    void addgold();
    void addsonar();
    void addsquirt();
    int gethitpoint();
    int getsquirtnum();
    int getsonarnum();
    int getgoldnum();
    bool declinehit();  // return true, when died
private:
    int hitpoint;  //每次杀伤力减20
    int goldnum;
    int squirtnum;
    int sonarnum;
    
};

class Boulder : public Actor
{
public:
    Boulder(int x = 0, int y = 0): Actor(IID_BOULDER,x,y,down,1.0,1,true,true,0,"boulder"),waitingtime(0){}
    
    virtual ~Boulder(){}
    virtual void doSomething();

private:
    int waitingtime;

};

class Barrel: public Actor
{
public:
    Barrel(int x = 0, int y = 0): Actor(IID_BARREL,x,y,right,1.0,2,false,true,0,"barrel"){}
    virtual ~Barrel(){}
    virtual void doSomething();
};


class Squirt:public Actor
{
public:
    Squirt(int x = 0, int y = 0,Direction dir = left):Actor(IID_WATER_SPURT,x,y,dir,1.0,1,true,true,0,"squirt"),travdistance(0){}
    virtual ~Squirt(){}
    virtual void doSomething();

private:
    int travdistance;
    
};


class Protester: public Actor
{
public:
    Protester(int imageID,int x = 0, int y = 0,std::string name = "", int wait = 0,int heal = 0):Actor(imageID,x,y,left,1.0,0,true,true,0,name),waitingticks(wait),health(heal),numStepsinDir(rand()%53 + 8),stepsSinperp(0),ticks(wait),hasShouted(false),canturn(false){}
    virtual ~Protester(){}
    virtual void doSomething();
    void setresting(int t);
    bool declinheal(int h);  // return true when died
    void moveStep(Direction d);
    Direction getRandir(Direction);
    void sethealth();
    
private:
    int waitingticks;
    int ticks;
    bool hasShouted;
    int health;
    int numStepsinDir;
    int stepsSinperp;
    bool canturn;
};


class RegularProtester : public Protester
{
public:
    RegularProtester(int x =0, int y = 0, int wait = 0):Protester(IID_PROTESTER,x,y,"regularprotester",wait,5){}
    virtual ~RegularProtester(){}
};


class HardcoreProtester: public Protester
{
public:
    HardcoreProtester(int x = 0,int y = 0, int wait = 0, int dis = 0):Protester(IID_HARD_CORE_PROTESTER,x,y,"hardcoreprotester",wait,20),chasedis(dis){}
    virtual ~HardcoreProtester(){}

    
private:
    int chasedis;

};

//class DeadProtester: public Protester
//{
//public:
//    DeadProtester(int imageID,int x = 0, int y = 0):Protester(imageID,x,y,"deadprotester",0,-1){}
//    ~DeadProtester(){}
//    virtual void doSomething(){}
//private:
//    virtual bool chasingFrackman(){return false;}
//    
//};



class Goodies: public Actor
{
public:
    Goodies(int imageID, int x = 0, int y = 0, bool isvisble = true, std::string gname = ""):Actor(imageID,x,y,right,1.0,2,isvisble,true,0,gname),existime(0),staytime(0){}
    
    virtual ~Goodies(){}
    virtual void doSomething() = 0;
    void setStaytime(int time);
    int getexistime() const;
    void addexistime();
    int getStaytime() const;
    
private:
    int existime;
    int staytime;


};


class Gold: public Goodies
{
public:
    Gold(int x = 0, int y = 0,bool gvisble = false): Goodies(IID_GOLD,x,y,gvisble,"gold")
    {
       // setVisible(true);  // testing
    }
    virtual ~Gold(){}
    virtual void doSomething();

};

class Sonarkit: public Goodies
{
public:
    Sonarkit(int x = 0, int y = 0): Goodies(IID_SONAR,x,y,true,"sonar"){}
    virtual ~Sonarkit(){}
    virtual void doSomething();
};

class Waterpool: public Goodies
{
public:
    Waterpool(int x = 0, int y = 0): Goodies(IID_WATER_POOL,x,y,true,"water"){}
    virtual ~Waterpool(){}
    virtual void doSomething();
    
};





#endif // ACTOR_H_
