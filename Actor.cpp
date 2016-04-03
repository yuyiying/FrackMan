#include "Actor.h"
#include "StudentWorld.h"


using namespace std;

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp


StudentWorld* Actor::getWorld()
{
    return StudentWorld::game;
}

Actor::Actor(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth, bool Isvisble, bool alive, int istate, std::string actname):GraphObject(imageID,startX,startY,dir,size,depth)
{
    setVisible(Isvisble);
    // setVisible(true); // for testing
    
    IsAlive = alive;
    state = istate;
    name = actname;
    imageId = imageID;

}

int Actor::getimageID() const
{
    return imageId;
}

void Actor::setAlive(bool Isalive)
{
    IsAlive = Isalive;
}

void Actor::setState(int s)
{
    state = s;
}

int Actor::getState() const
{
    return state;
}
bool Actor::getAlive() const
{
    return IsAlive;
}

std::string Actor::getname() const
{
    return name;
}

FrackMan::FrackMan(): Actor(IID_PLAYER,30,60,right,1.0,0,true,true,0,"frackman")
{
    hitpoint = 100;
    goldnum = 0;
    squirtnum = 5;
    sonarnum = 1;
}

bool FrackMan::declinehit() 
{
    hitpoint -= 20;
    if(hitpoint <= 0)
        return true;
    else
        return false;

}
void FrackMan::addgold()
{
    goldnum++;
}

void FrackMan::addsonar()
{
    sonarnum++;
}

void FrackMan::addsquirt()
{
    squirtnum += 5;
}

int FrackMan::gethitpoint()
{
    return hitpoint;
}

int FrackMan::getsquirtnum()
{
    return squirtnum;
}

int FrackMan::getsonarnum()
{
    return sonarnum;
}
int FrackMan::getgoldnum()
{
    return goldnum;
}


void FrackMan::Movedirt()
{
    bool sound = false;
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if (getWorld()->IsdirtVisble(getX()+i, getY()+j))
            {
                sound = true;
                break;
            }
        }
    }
    if(sound)
    {
        getWorld()->setdirtInVisble(getX(), getY(), false);
        getWorld()->playSound(SOUND_DIG);
    }
}

void FrackMan::doSomething()
{
    int val;
    if(getWorld()->getKey(val) == true)
    {
        switch(val)
        {
            case KEY_PRESS_LEFT:
                if(getDirection() != left)
                    setDirection(left);
                else
                {
                    if(getX()-1 >= 0)
                    {
                        if(getWorld()->isBoulder(getX()-1, getY())){}
                        else
                        {
                            moveTo(getX()-1, getY());
                            Movedirt();
                        }
                    }
                    else
                        moveTo(getX(), getY());
                }
                break;
            case KEY_PRESS_RIGHT:
                if(getDirection() != right)
                    setDirection(right);
                else
                {
                    if(getX()+1 <= 60)
                    {
                        if(getWorld()->isBoulder(getX()+1, getY())){}
                        else
                        {
                            moveTo(getX()+1, getY());
                            Movedirt();
                        }
                    }
                    else
                        moveTo(getX(), getY());
                }
                break;
            case KEY_PRESS_UP:
                if(getDirection() != up)
                    setDirection(up);
                else
                {
                    if(getY()+1 <= 60)
                    {
                        if(getWorld()->isBoulder(getX(), getY()+1)){}
                        else
                        {
                            moveTo(getX(), getY()+1);
                            Movedirt();
                        }
                    }
                    else
                        moveTo(getX(), getY());
                }
                break;
            case KEY_PRESS_DOWN:
                if(getDirection() != down)
                    setDirection(down);
                else
                {
                    if(getY()-1 >= 0)
                    {
                        if(getWorld()->isBoulder(getX(), getY()-1)){}
                        else
                        {
                            moveTo(getX(), getY()-1);
                            Movedirt();
                        }
                    }
                    else
                        moveTo(getX(), getY());
                }
                break;
            case KEY_PRESS_ESCAPE:
                getWorld()->decLives();
                break;
            case 'z':
            case 'Z':
                if(sonarnum > 0)
                {
                    sonarnum--;
                    getWorld()->playSound(SOUND_SONAR);
                    getWorld()->illuminate(getX(), getY());
                }
                break;
            case KEY_PRESS_SPACE:
                if(squirtnum > 0)
                {
                    squirtnum--;
                    getWorld()->playSound(SOUND_PLAYER_SQUIRT);
                    getWorld()->insertSquirt(getX(), getY(), getDirection());
                }
                break;
            case KEY_PRESS_TAB:
                if(goldnum > 0)
                {
                    goldnum--;
                    getWorld()->addGold(getX(), getY());
                }
                
                break;
                
        }
        
    }
}


void Boulder::doSomething()
{
    if(!getAlive())
        return;
    
    if(getState() == 0)
    {
        for(int i = 0; i < 4; i++)
        {
            if(getWorld()->IsdirtVisble(getX()+i, getY()-1)) return;
        }
        setState(1);
    }
    else if(getState() == 1)
    {
        if(waitingtime == 30)
        {
            waitingtime = 0;
            setState(2);
        }
        else
            waitingtime++;
    }
    else
    {
        
        if(getY()-1 == -1 || getWorld()->IsdirtVisble(getX(), getY()-1))
        {
            setVisible(false);
            setAlive(false);
            return;
        }
        else if(getWorld()->hitBoulder(getX(), getY()-1))
        {
            setAlive(false);
            return;
        }
        else
        {
            getWorld()->playSound(SOUND_FALLING_ROCK);
            if(pow(getX()-getWorld()->getFrackManCoord().x,2)+pow(getY()-1-getWorld()->getFrackManCoord().y,2) <= 9)
                getWorld()->decLives();
            else if(getWorld()->hitProtester(getX(), getY()-1)){}
            else
            {
                moveTo(getX(), getY()-1);
            }
        }
    }
}


void Barrel::doSomething()
{
    double distance = pow(getX()-getWorld()->getFrackManCoord().x,2)+(pow(getY()-getWorld()->getFrackManCoord().y, 2));
    if(!isVisible())
    {
        if(distance <= 16)
        {
            setVisible(true);
            return;
        }
    }
    else
    {
        if(distance > 9) return;
        else
        {
            setVisible(false);
            setAlive(false);
            getWorld()->barreldeclinde();
            getWorld()->increaseScore(1000);
            getWorld()->playSound(SOUND_FOUND_OIL);
            
        }
    }
}


void Goodies::setStaytime(int time)
{
    staytime = time;
}
int Goodies::getexistime() const
{
    return existime;
}
void Goodies::addexistime()
{
    existime++;
}
int Goodies::getStaytime() const
{
    return staytime;
}



void Gold::doSomething()
{
    if(!getAlive())
        return;
    
    if(getState() == 0) // picked up by frackman
    {
        double distance = pow(getX()-getWorld()->getFrackManCoord().x,2)+(pow(getY()-getWorld()->getFrackManCoord().y, 2));
        if(!isVisible())
        {
            if(distance <= 16)
            {
                setVisible(true);
                return;
            }
        }
        else
        {
            if(distance > 9) return;
            else
            {
                setVisible(false);
                setAlive(false);
                getWorld()->addNumgold();
                getWorld()->increaseScore(10);
                getWorld()->playSound(SOUND_GOT_GOODIE);
                
            }
        }
    }
    else if(getState() == 1)
    {
        if(getexistime() == getStaytime())
        {
            setVisible(false);
            setAlive(false);
        }
        else
        {
            addexistime();
            if(getWorld()->goldbyProtester(getX(), getY()))
            {
                setVisible(false);
                setAlive(false);                
            }
        }
    }
}

void  Sonarkit::doSomething()
{
    if(!getAlive())
        return;
    
    if(getexistime() == getStaytime())
    {
        setVisible(false);
        setAlive(false);
    }
    else
    {
        addexistime();
        double distance = pow(getX()-getWorld()->getFrackManCoord().x,2)+(pow(getY()-getWorld()->getFrackManCoord().y, 2));
        if(distance > 9) return;
        else
        {
            setVisible(false);
            setAlive(false);
            getWorld()->addNumSonar();
            getWorld()->increaseScore(75);
            getWorld()->playSound(SOUND_GOT_GOODIE);
            
        }

    }
}

void Waterpool::doSomething()
{
    if(!getAlive())
        return;
    
    if(getexistime() == getStaytime())
    {
        setVisible(false);
        setAlive(false);
    }
    else
    {
        addexistime();
        double distance = pow(getX()-getWorld()->getFrackManCoord().x,2)+(pow(getY()-getWorld()->getFrackManCoord().y, 2));
        if(distance > 9) return;
        else
        {
            setVisible(false);
            setAlive(false);
            getWorld()->addNumsquit();
            getWorld()->increaseScore(100);
            getWorld()->playSound(SOUND_GOT_GOODIE);
            
        }
        
    }
}



void Squirt::doSomething()
{
    /* 
     If a Squirt is within a radius of 3.0 of one or more Protesters (up to and including a distance of 3.0 squares away), it will cause 2 points of annoyance to these Protester(s), and then immediately set its state to dead, so it can be removed from the oil field at the end of the tick.
    */
    if(!getAlive())
        return;
    
    if(travdistance < 4)
    {
        if(getDirection()==right && getX()+1 <= 60 && getWorld()->IsdirtVisble(getX()+4, getY())==false &&  getWorld()->isSmaBouler(getX()+1, getY())== false)
        {
            moveTo(getX()+1, getY());
            if(getWorld()->stunProtester(getX(), getY()))
            {
                travdistance = 4;
                return;
            }
            else
                travdistance++;
        }
        else if(getDirection() == left && getX()-1 >= 0 && getWorld()->IsdirtVisble(getX()-1, getY())==false && getWorld()->isSmaBouler(getX()-1, getY())== false)
        {
            moveTo(getX()-1, getY());
            if(getWorld()->stunProtester(getX(), getY()))
            {
                travdistance = 4;
                return;
            }
            else
                travdistance++;
        }
        else if(getDirection() == up && getY()+1 <= 60 && getWorld()->IsdirtVisble(getX(),getY()+4)==false
            && getWorld()->isSmaBouler(getX(), getY()+1)== false)
        {
            moveTo(getX(), getY()+1);
            if(getWorld()->stunProtester(getX(), getY()))
            {
                travdistance = 4;
                return;
            }
            else
                travdistance++;
        }
        else if(getDirection() == down && getY()-1 >= 0 && getWorld()->IsdirtVisble(getX(), getY()-1)==false
                && getWorld()->isSmaBouler(getX(), getY()-1)== false)
        {
            moveTo(getX(), getY()-1);
            if(getWorld()->stunProtester(getX(), getY()))
            {
                travdistance = 4;
                return;
            }
            else
                travdistance++;
        }
        else
        {
            setAlive(false);
            setVisible(false);
        }
        
    }
    else if(travdistance == 4)
    {
        setAlive(false);
        setVisible(false);
    }    

}

void Protester::setresting(int t)
{
    ticks = t;

}


bool Protester::declinheal(int h)
{
    health -= h;
    if(health <= 0)
        return true;
    else
        return  false;
    
}

void Protester::sethealth()
{
    health = -1;
}

void Protester::moveStep(Direction d)
{
    if(d == right)
        moveTo(getX()+1, getY());
    else if(d == left)
        moveTo(getX()-1, getY());
    else if(d == up)
        moveTo(getX(), getY()+1);
    else
        moveTo(getX(), getY()-1);
}


Actor::Direction Protester::getRandir(Actor::Direction dir)
{
    int num = rand()%4 +1;
    
    if (num == 1)
        return Actor::up;
    else if (num == 2)
        return Actor::down;
    else if (num == 3)
        return Actor::left;
    else
        return Actor::right;
}


void Protester::doSomething()
{
    if(!getAlive())
        return;
    
    if(ticks <= 0)
    {
        if(stepsSinperp > 0)
            stepsSinperp--;
        else if(canturn == false)
            canturn = true;
    }
    if(hasShouted == true)
        hasShouted = false;
    
    if(ticks > 0)
    {
        ticks--;
        return;
    }
    else if(getState() == 1)
    {
        if(getX() == 60 && getY() == 60)
        {
            setAlive(false);
            setVisible(false);
            getWorld()->decrementNumProtester();
            return;
        }
        Direction dir = none;
        int tempx = getX();
        int tempy = getY();
        
        dir = getWorld()->protesterback(tempx,tempy);
        if(dir != none)
        {
            setDirection(dir);
            moveTo(tempx, tempy);
        }
        ticks = waitingticks;
        return;
    }
    
    else if (getWorld()->withinshout(getX(), getY()) && getWorld()->IsfacingFrackMan(getX(),getY(),getDirection()) && hasShouted == false)
    {
        getWorld()->playSound(SOUND_PROTESTER_YELL);
        if(getWorld()->annoyFrackMan())
        {
            getWorld()->decLives();
            return;
        }
        hasShouted = true;
        ticks = 15* waitingticks;
        return;
    }
    
    else if(getWorld()->isInlineOfSight(getX(), getY()))
    {
       if(!getWorld()->withinshout(getX(), getY()))
       {
           setDirection(getWorld()->FaceFrackMan(getX(), getY()));
           moveStep(getDirection());
       }
       else
       {
           setDirection(getWorld()->FaceFrackMan(getX(), getY()));
       }
        numStepsinDir = 0;
        ticks = waitingticks;
        return;
    }
    else
    {
        numStepsinDir--;
        if(numStepsinDir <= 0)
        {
            Direction dir;
            dir = getRandir(getDirection());
            
            while(!getWorld()->movedir(getX(), getY(),dir))
            {
                dir = getRandir(getDirection());
            }
            setDirection(dir);
            numStepsinDir = rand() % 53 + 8;
        }
        else
        {
            Direction dir = getWorld()->Turnto(getX(), getY(), getDirection());
            if(dir != none)
            {
                if(canturn == true)
                {
                    setDirection(dir);
                    numStepsinDir = rand()% 53 + 8;
                   
                    stepsSinperp = 200;
                    canturn = false;
                }
            }
            
            if(getWorld()->movedir(getX(), getY(), getDirection()))
                moveStep(getDirection());
            else
                numStepsinDir = 0;
            ticks = waitingticks;
            return;
        }
    }
    
    
}
