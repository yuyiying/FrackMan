#include "StudentWorld.h"


using namespace std;


StudentWorld* StudentWorld::game;

GameWorld* createStudentWorld(string assetDir)
{
    return StudentWorld::game = new StudentWorld(assetDir);
}


// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp


StudentWorld::StudentWorld(std::string assetDir)
: GameWorld(assetDir)
{
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            dirt[i][j] = nullptr;
        }
    }
    frackman = nullptr;
    
}

bool StudentWorld::IsdirtVisble(int i, int j)
{
    
    if (i < 0 || j < 0 || i > 63 || j > 63)
        return false;
    
    return dirt[i][j]->isVisible();
}

Coord StudentWorld::getFrackManCoord()
{
    Coord c(frackman->getX(),frackman->getY(),0);
    return c;
}

int StudentWorld::getleftBarrel() const
{
    return numBarrel;
}

void StudentWorld::barreldeclinde()
{
    numBarrel--;
}

void StudentWorld::addNumgold()
{
    frackman->addgold();
}
void StudentWorld::addNumsquit()
{
    frackman->addsquirt();
}

void StudentWorld::addNumSonar()
{
    frackman->addsonar();
}



void StudentWorld::setDisplayText()
{
    int score = getScore();
    int level = getLevel();
    int lives = getLives();
    int health = frackman->gethitpoint(); // 得到数字
    int squirts = frackman->getsquirtnum();
    int gold = frackman->getgoldnum();
    int sonar = frackman->getsonarnum();
    int barrelsleft = getleftBarrel();
    
    int countdigit = 0;
    int sc = score;
    if(score == 0) countdigit = 1;
    while(sc != 0)
    {
        countdigit++;
        sc = sc/10;
    }
    string ss = "";
    while(countdigit != 6)
    {
        ss += '0';
        countdigit++;
    }
    ss += to_string(score);  //string score
    
    string le = "";
    if(level < 10)
        le = " "+ to_string(level);
    else
        le = to_string(level);   // string level
    
    string li = to_string(lives); //string lives
    
    string he = "";
    if(health == 100)
        he = "100%";
    else
        he = " "+to_string(health)+ "%";  //string health
    
    string sq = "";
    if(squirts < 10)
        sq = " "+to_string(squirts);  //squirts
    else
        sq = to_string(squirts);
    
    string go = "";
    if(gold < 10)
        go = " "+to_string(gold); // gold
    else
        go = to_string(gold);
    
    string so = "";
    if(sonar < 10)
        so = " "+to_string(sonar);
    else
        so = to_string(sonar); // sonar
    
    string bar = "";
    if(barrelsleft < 10)
        bar = " "+ to_string(barrelsleft);
    else
        bar = to_string(barrelsleft); //barrels
    
    string text = "Src: "+ss+"  Lvl: "+le+"  Lives: "+li+"  Hlth: "+he +"  Wtr: "+sq+"  Gld: "+go+"  Sonar: "+so + "  Oil Left: "+bar;
    setGameStatText(text);
    

}

void StudentWorld::cleanUp()
{
    for(int i = 0; i < 64; i++)
    {
        for(int j = 0; j < 64; j++)
        {
           if(dirt[i][j] != nullptr)
           {
                delete dirt[i][j];    // create  a 2-d dirt array
                dirt[i][j] = nullptr;
           }
        }
    }
    
    for(int i = 0; i < actor.size(); i++)
        delete actor[i];
    
    actor.clear();
    
    delete frackman;
    
}

void StudentWorld::addboulder()
{
    int numb = numBoulder;
    
    while(numb > 0)
    {
        int x = 0;
        int y = 0;
        do
        {
            x = rand()% 61;
            y = rand()% 37 + 20;
            int i = 0;
            for(i = 0; i < actor.size(); i++)
            {
                while((pow(x-actor[i]->getX(),2)+pow(y-actor[i]->getY(),2)) <= 36)
                {
                    x = rand()% 61;
                    y = rand()% 37 + 20;
                    i = 0;
                }
            }
        }while(x >= 27 && x < 34);
        
        Boulder* b = new Boulder(x,y);  // create a boulder
        actor.push_back(b);// store in the actor vector
        setdirtInVisble(x, y, false);
        numb--;
    }
}

void StudentWorld::addBarrel()
{
    int numbarrel = numBarrel;
    
    while(numbarrel > 0)
    {
        int x = 0;
        int y = 0;
        do
        {
            x = rand()% 61;
            y = rand()% 37 + 20;
            int i = 0;
            for(i = 0; i < actor.size(); i++)
            {
                while((pow(x-actor[i]->getX(),2)+pow(y-actor[i]->getY(),2)) <= 36)
                {
                    x = rand()% 61;
                    y = rand()% 37 + 20;
                    i = 0;
                }
            }
        }while(x >= 27 && x < 34);
        
        Barrel* ba = new Barrel(x,y);
        actor.push_back(ba);
        numbarrel--;
    }
}


void StudentWorld::addnugget()
{
    int numgold = numGold;
    
    while(numgold > 0)
    {
        int x = 0;
        int y = 0;
        do
        {
            x = rand()% 61;
            y = rand()% 37 + 20;
            int i = 0;
            for(i = 0; i < actor.size(); i++)
            {
                while((pow(x-actor[i]->getX(),2)+pow(y-actor[i]->getY(),2)) <= 36)
                {
                    x = rand()% 61;
                    y = rand()% 37 + 20;
                    i = 0;
                }
            }
        }while(x >= 27 && x < 34);
        
        Gold* go = new Gold(x,y);
        actor.push_back(go);
        numgold--;
    }

}

int StudentWorld::init()
{
    frackman = new FrackMan(); // create a frackman
    for(int i = 0; i < 64; i++)
    {
        for(int j = 0; j < 64; j++)
            dirt[i][j] = new Dirt(i,j);   // create  a 2-d dirt array  i- column, j - row;
    }
    
    for(int i = 0; i < 64; i++)
    {
        for(int j = 60; j < 64; j++)
            dirt[i][j]->setVisible(false);  // in case when judge the dirt, it will overlap
    }
    
    for(int i = 30; i < 34; i++)
    {
        for(int j = 4; j < 64; j++)  //create a single mineshaft
            dirt[i][j]->setVisible(false);
    }
    numBoulder = (getLevel())/2 +2 < 6 ? (getLevel())/2 +2 : 6;
    numBarrel = (2 + getLevel()) < 20 ? getLevel()+2 : 20;
    numGold = (5-getLevel()/2) > 2 ? 5-getLevel()/2 : 2;
    radius = 16 + getLevel()*2 ;
    
    srand(time(NULL));
    
    addboulder();
    
    addBarrel();
    
    addnugget();
    
    addGoodie = 0;
    
    addprotester = 25 > 200-getLevel() ? 25:200-getLevel();
    
    setDisplayText();
    
    
    return GWSTATUS_CONTINUE_GAME;
}


int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    
    
    //add goodie
    int tick = getLevel()*25 + 300;
    
    if(addGoodie == tick)
    {
        addGoodie = 0;
        int randNum = rand()%5 + 1;;
        if(randNum <= 1)
        {
            Sonarkit* sonar = new Sonarkit(0,60);
            actor.push_back(sonar);
            int time = 100 > (300-10*getLevel()) ? 100 : 300-10*getLevel(); // max  or min time
            sonar->setStaytime(time);
        }
        else
        {
            int x = 0;
            int y = 0;

            
            x = rand()% 64;
            y = rand()% 64;

            int i = 0, j = 0;
            
            for(i = 0; i < 4; i++)
            {
                for(j = 0; j < 4; j++)
                {
                    while(IsdirtVisble(x+i, y+j))
                    {
                        x = rand()% 64;
                        y = rand()% 64;
                        i = 0;
                        j = 0;
                    }
                }
            }
            
            Waterpool* water = new Waterpool(x,y);
            actor.push_back(water);
            int time = 100 > (300-10*getLevel()) ? 100 : 300-10*getLevel();  // max or min time
            water->setStaytime(time);
        }
    }
    else
        addGoodie++;
    
    
    //add protester
    int tickaddp = 25 > 200-getLevel() ? 25:200-getLevel();
    int nump = 15 < 2+getLevel()*1.5? 15:2+getLevel()*1.5;
    int waitnum = 0 > 3- (getLevel()/4) ? 0 : 3- (getLevel()/4);
    
    if(addprotester >= tickaddp)
    {
        if(numprotester < nump)
        {
            int prob = 90 < getLevel()*10 + 30? 90:getLevel()*10 + 30;
            if(rand()%100 < prob)
                actor.push_back(new HardcoreProtester(60,60,waitnum,16+2*getLevel()));
            else
                actor.push_back(new RegularProtester(60,60,waitnum));
            numprotester++;
            addprotester = 0;
        }
    }
    else
        addprotester++;
    
    updateMap(60, 60, direct, INT16_MAX);
    updateMap(frackman->getX(), frackman->getY(), mapToFrack, radius);
    
    int curLives = getLives();
    
    if(frackman->getAlive())
    {
        frackman->doSomething();
    }
    
    if(getLives() < curLives)
        return GWSTATUS_PLAYER_DIED;
    
    
    
    for(int i = 0; i < actor.size();i++)
    {
        if(actor[i]->getAlive())
        {
            actor[i]->doSomething();
        }
        
        if(getLives() < curLives)
            return GWSTATUS_PLAYER_DIED;
        
        else if(getleftBarrel() == 0)
        {
            advanceToNextLevel();
            setDisplayText();
            playSound(SOUND_FINISHED_LEVEL);
            return GWSTATUS_FINISHED_LEVEL;
        }
    }
    
    
    for(int i = 0; i < actor.size();)
    {
        if(actor[i]->getAlive())
            i++;
        else
            actor.erase(actor.begin()+i);
    }
    
    setDisplayText();

    return GWSTATUS_CONTINUE_GAME;
}


bool StudentWorld::isBoulder(int i, int j)  //determine whether a FrackMan stands within 3 radius away center
{
    for(int k = 0; k < actor.size(); k++)
    {
        if(actor[k]->getname() == "boulder")
        {
            double distance = pow(i-actor[k]->getX(), 2) + pow(j-actor[k]->getY(),2);
            if( distance <= 9)
                return true;
        }
    }
    return false;
}



void StudentWorld::setdirtInVisble(int i, int j,bool visble)
{
    for(int k = 0; k < 4; k++)
        for(int q = 0; q < 4; q++)
            dirt[i+k][j+q]->setVisible(false);
}



bool StudentWorld::hitBoulder(int i, int j)
{
    for(int k = 0; k < actor.size(); k++)
    {
        if(actor[k]->getname() == "boulder")
        {
            for(int d = 0; d < 4; d++)
            {
                if(i == actor[k]->getX()+d && j == actor[k]->getY())
                    return  true;
            }
        }
    }
    return false;
}

void StudentWorld::illuminate(int i, int j)
{
    for(int k = 0; k < actor.size(); k++)
    {
        if(actor[k]->getname() == "gold" || actor[k]->getname() == "barrel")
        {
            double distance = pow(i-actor[k]->getX(),2)+pow(j-actor[k]->getY(),2);
            if(distance <= 144)
                actor[k]->setVisible(true);
        }
    }
}


bool StudentWorld::isSquaredirt(int i, int j)
{
    if (i < 0 || j < 0 || i > 60 || j > 60)
        return false;
    
    for(int k = 0; k < 4; k++)
    {
        for(int q = 0; q < 4; q++)
        {
            if(IsdirtVisble(i+k, j+q))
                return true;
        }
    
    }
    return false;
}

bool StudentWorld::isSmaBouler(int i, int j)
{
    for(int k = 0; k < actor.size(); k++)
    {
        if(actor[k]->getname() == "boulder")
        {
            for (int x = i - 3; x < i + 4; x++)
            {
                for (int y = j - 3; y < j + 4; y++)
                {
                    if(x == actor[k]->getX() && y == actor[k]->getY())
                        return true;
                }
            }
        }
    }
    return false;
}


void StudentWorld::insertSquirt(int i, int j, GraphObject::Direction dir)
{
    if(dir == GraphObject::right && i + 3 <= 60 && isSquaredirt(i+3, j) == false)
        actor.push_back(new Squirt(i+3,j,dir));
    
    else if(dir == GraphObject::left && i - 3 >= 0 && isSquaredirt(i-3, j)== false)
        actor.push_back(new Squirt(i-3,j,dir));
    
    else if(dir == GraphObject::up && j + 3 <= 60 && isSquaredirt(i, j+3)== false)
        actor.push_back(new Squirt(i,j+3,dir));
    
    else if(dir == GraphObject::down && j-3 >= 0 && isSquaredirt(i, j-3) == false)
        actor.push_back(new Squirt(i,j-3,dir));
}


void StudentWorld::addGold(int i, int j)
{
    Gold* gold = new Gold(i,j,true);
    gold->setState(1);
    gold->setStaytime(100);
    actor.push_back(gold);
}

bool StudentWorld::goldbyProtester(int i, int j)
{
    for(int k = 0 ; k < actor.size(); k++)
    {
        if(actor[k]->getname() == "regularprotester" && actor[k]->getState() == 0)
        {
            double distance =  pow(i - actor[k]->getX(),2)+pow(j-actor[k]->getY(),2);
            if(distance <= 9)
            {
                playSound(SOUND_PROTESTER_FOUND_GOLD);
                actor[k]->setState(1);
                Protester* p = dynamic_cast<Protester*>(actor[k]);
                p->setresting(0);
                increaseScore(25);
                return true;
            }
        }
        else if(actor[k]->getname() == "hardcoreprotester" && actor[k]->getState() == 0)
        {
            double distance =  pow(i - actor[k]->getX(),2)+pow(j-actor[k]->getY(),2);
            if(distance <= 9)
            {
                playSound(SOUND_PROTESTER_FOUND_GOLD);
                int resttime = 50 > 100-getLevel()*10 ? 50 : 100-getLevel()*10;
                dynamic_cast<HardcoreProtester*>(actor[k])->setresting(resttime);
                increaseScore(50);
                return true;
            }
        }
    
    }
    return false;
}

bool StudentWorld::hitProtester(int i, int j)  // i, j boulder next step position
{
    for(int k = 0; k < actor.size(); k++)
    {
        if((actor[k]->getname() == "regularprotester" || actor[k]->getname() == "hardcoreprotester") && actor[k]->getState() == 0)
        {
            double distance =  pow(i - actor[k]->getX(),2)+pow(j-actor[k]->getY(),2);
            if(distance <= 9)
            {
                playSound(SOUND_PROTESTER_GIVE_UP);
                if(actor[k]->getname() == "regularprotester")
                    increaseScore(100);
                else if(actor[k]->getname() == "hardcoreprotester")
                    increaseScore(250);
                actor[k]->setState(1);
                Protester* p = dynamic_cast<Protester*>(actor[k]);
                p->setresting(0);
                increaseScore(500);
                return true;
            }
        }
    
    }
    return  false;
}

bool StudentWorld::stunProtester(int i, int j)
{
    bool stun = false;
    for(int k = 0; k < actor.size(); k++)
    {
        if((actor[k]->getname() == "regularprotester" || actor[k]->getname() == "hardcoreprotester") && actor[k]->getState() == 0)
        {
            double distance =  pow(i - actor[k]->getX(),2)+pow(j-actor[k]->getY(),2);
            if(distance <= 9)
            {
                Protester* p = dynamic_cast<Protester*>(actor[k]);
                if(p->declinheal(2)) // protester died
                {
                    playSound(SOUND_PROTESTER_GIVE_UP);
                    if(actor[k]->getname() == "regularprotester")
                        increaseScore(100);
                    else if(actor[k]->getname() == "hardcoreprotester")
                        increaseScore(250);
                    actor[k]->setState(1);
                    p->setresting(0);
                }
                else
                {
                    playSound(SOUND_PROTESTER_ANNOYED);
                    int restime = 50 > 100-getLevel()*10 ? 50 : 100-getLevel()*10;
                    p->setresting(restime);
            
                }
                stun = true;
            }
        }
    }
    return stun;
}

bool StudentWorld::withinshout(int i, int j)
{
    double distance = pow(i-frackman->getX(),2)+pow(j-frackman->getY(), 2);
    if(distance <= 16)
        return true;
    else
        return false;
}

bool StudentWorld::IsfacingFrackMan(int i, int j, GraphObject::Direction dir)
{
    int fx = frackman->getX();
    int fy = frackman->getY();
    
    if(i < fx && dir == GraphObject::right)
        return true;
    else if(i > fx && dir == GraphObject::left)
        return true;
    else if(j < fy && dir == GraphObject::up)
        return true;
    else if(j > fy && dir == GraphObject::down)
        return true;
    return false;
}

GraphObject::Direction StudentWorld::FaceFrackMan(int i, int j)
{
    int fx = frackman->getX();
    int fy = frackman->getY();
    
    if(i < fx)
        return GraphObject::right;
    else if(i > fx)
        return GraphObject::left;
    else if(j < fy)
        return GraphObject::up;
    else if(j > fy)
        return GraphObject::down;
    else
        return GraphObject::up;
}

bool StudentWorld::annoyFrackMan()
{
    return frackman->declinehit();
}

bool StudentWorld::isInlineOfSight(int i, int j)
{
    int fx = frackman->getX();
    int fy = frackman->getY();
    
    int lowy;
    int highy;
    int lowx;
    int highx;
    
    if(i == fx)
    {
        if(j < fy)
        {
            lowy = j;
            highy = fy -1 ;
        }
        else
        {
            lowy = fy + 4;
            highy = j;
        }
        for(int k = lowy; k < highy; k++)
        {
            if(isSquaredirt(i, k) || isSmaBouler(i, k))
                return false;
        }
    }
    else if(j == fy)
    {
        if(i < fx)
        {
            lowx = i;
            highx = fx-1;
        }
        else
        {
            highx = i;
            lowx = fx + 4;
        }
        for(int q = lowx; q < highx; q++)
        {
            if(isSquaredirt(q, j) || isSmaBouler(q, j))
                return false;
        }
    }
    return true;
}

bool StudentWorld::clearDirtBoulder(int i, int j)
{
    if(i > 60 || i < 0)
        return  false;
    if(j > 60 || j < 0)
        return false;
    if(isSquaredirt(i, j))
        return false;
    if(isBoulder(i, j))
        return false;
    return true;
}


bool StudentWorld::movedir(int i, int j,GraphObject::Direction dir)
{
    if (dir == GraphObject::right)
    {
        if (!clearDirtBoulder(i+1, j))
            return false;
    }
    else if (dir == GraphObject::left)
    {
        if (!clearDirtBoulder(i-1, j))
            return false;
    }
    else if (dir == GraphObject::up)
    {
        if (!clearDirtBoulder(i, j+1))
            return false;
    }
    else if (dir == GraphObject::down)
    {
        if (!clearDirtBoulder(i, j-1))
            return false;
    }
    return true;
}

GraphObject::Direction StudentWorld::Turnto(int i, int j, GraphObject::Direction dir)
{
    if (dir == GraphObject::up || dir == GraphObject::down)
    {
        if (movedir(i, j, GraphObject::left) && movedir(i, j, GraphObject::right))
        {
            int num = rand()% 2;
            if (num == 0)
                return GraphObject::left;
            else
                return GraphObject::right;
        }
        else if (movedir(i, j, GraphObject::left))
            return GraphObject::left;
        else if (movedir(i, j, GraphObject::right))
            return Actor::right;
        else
            return GraphObject::none;
    }
    else
    {
        if (movedir(i, j, GraphObject::up) && movedir(i, j, GraphObject::down))
        {
            int num = rand()%2;
            if (num == 0)
                return GraphObject::up;
            else
                return GraphObject::down;
        }
        else if (movedir(i, j, GraphObject::up))
            return GraphObject::up;
        else if (movedir(i, j, GraphObject::down))
            return GraphObject::down;
        else
            return GraphObject::none;
    }
}

GraphObject::Direction StudentWorld::protesterback(int &x, int &y)
{
    if (direct[x][y] == Actor::up)
    {
        y++;
        return Actor::up; // up
    }
    else if (direct[x][y] == Actor::right)
    {
        x++;
        return Actor::right; // right
    }
    else if (direct[x][y] == Actor::down)
    {
        y--;
        return Actor::down; // down
    }
    else if (direct[x][y] == Actor::left)
    {
        x--;
        return Actor::left; // left
    }
    else
        return Actor::none;
}

void StudentWorld::updateMap(int x, int y, Actor::Direction m[64][64], int r)
{
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            m[i][j] = Actor::none;
        }
    }
    
    queue<Coord> cstack;
    cstack.push(Coord(x, y, r));
    while (!cstack.empty()) {
        Coord a = cstack.front();
        cstack.pop();
        if (m[a.x - 1][a.y] == 0 && clearDirtBoulder(a.x - 1, a.y) && a.z > 0) {
            cstack.push(Coord(a.x - 1, a.y, a.z - 1));
            m[a.x - 1][a.y] = Actor::right;
        }
        if (m[a.x][a.y - 1] == 0 && clearDirtBoulder(a.x, a.y - 1) && a.z > 0) {
            cstack.push(Coord(a.x, a.y - 1, a.z - 1));
            m[a.x][a.y - 1] = Actor::up;
        }
        if (m[a.x + 1][a.y] == 0 && clearDirtBoulder(a.x + 1, a.y) && a.z > 0) {
            cstack.push(Coord(a.x + 1, a.y, a.z - 1));
            m[a.x + 1][a.y] = Actor::left;
        }
        if (m[a.x][a.y + 1] == 0 && clearDirtBoulder(a.x, a.y + 1) && a.z > 0) {
            cstack.push(Coord(a.x, a.y + 1, a.z - 1));
            m[a.x][a.y + 1] = Actor::down;
        }
    }
}

void StudentWorld::decrementNumProtester()
{
    numprotester--;
}
