//
// Created by winkleri on 11.5.19.
//

#ifndef MYPAC_CMAP_H
#define MYPAC_CMAP_H
#define TOPTAB 4
#define TAB 3
#define ArayTab 2


#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <vector>

#include "Cobject.h"
#include "Cwall.h"
#include "Ccoin.h"
#include "Ccherry.h"
#include "CMoveable.h"
#include "CPacman.h"
#include "Coctopus.h"
#include "Cnothing.h"
#include "Ckiller.h"
#include "Cteleport.h"


#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstdio>
#include <sys/ioctl.h>


/**
 * Class which represents the map
 */



class Cmap {
public:

/**
 * Constructor which receiving which map and difficulty were chosen by the user.
 *
 * @param[in] map
 * @param[in] difficulty
 */
Cmap(int map, int difficulty);
~Cmap();


//getters
/**
 * Returns X coordinates of Pacman.
 * @return
 */
int getXPac()const{return XPacman;}
/**
 * Returns Y coordinates of Pacman.
 * @return
 */
int getYPac()const{return YPacman;}
/**
 * Returns how many lives are left.
 * @return
 */
int getLives()const{ return lives;}
/**
 * Returns coin counter.
 * @return
 */
int getCoins()const{return Coincounter;}
/**
 * Returns the difficulty of the game.
 * @return
 */
int GetDifficulty() const{return difficulty;}
/**
 * Returns X coordinate where the Pacman started.
 * @return
 */
int getPacmanStartX()const{return XPacmanStart;}
/**
 * Returns Y coordinate where the Pacman started.
 * @return
 */
int getPacmanStartY()const{return YPacmanStart;}
/**
 * Returns boolean if the game map is valid.
 * @return
 */
bool getValid () const {return Valid;}

	int getScore() const { return score;}
	int getLines() const {return lines;}
	int getLength () const {return length;}
	int getCherrycount() const { return cherryCounter;}
	int GetOctopuscount()const {return Octopuscounter;}
/**
 * Returns vector of shared_ptr on all active Octopuses.
 * @return
 */

std::vector <std::shared_ptr<Cobject>> & GetVector(){ return Octopusses;}
/**
 * Return vector of all active teleports.
 * @return
 */
std::vector <std::shared_ptr<Cobject>> & GetTeleports(){return teleports;}
std::shared_ptr<Cobject> GetObject (int x, int y){return ObjectMap[x][y];}
//setters
void setXPac(int x){ XPacman = x;}
void setYPac (int y ){YPacman = y;}
void setObject(int x, int y, const Cobject & newObj){ObjectMap[x][y] = newObj.clone();}
void SetCobjectMap();
void SetTheCharArr(std::ifstream & MyMap);

/**
 * Function that put the right object on the right place after Octopus leave
 * @param Xobj
 * @param Yobj
 * @param Obj
 */
void ReplacingObject(int Xobj, int Yobj, int Obj);

/**
 * Give the player score points.
 */
void takeCoin(){score+=100;Coincounter--;}
void takeCherry(){score+=200; cherryCounter--;}
void takeDemage(){lives--;}
void addCherry(){cherryCounter++;}

/**
 * Boolean function which determine if the map from the file is valid or if there is some kind of problem.
 * @param map
 * @param PathToMap
 * @return
 */
bool ValidMap(int map,std::string & PathToMap);
/**
 * This function is used to determine the size of the map.
 * @param NumberofLines
 * @param lenghtofLine
 * @param map
 * @param PathToMap
 */
void FindNumberOfLines(int & NumberofLines , int & lenghtofLine, int map,std::string & PathToMap);
void printArray()const;
/**
 * Swap to object in map. Little bit risky but it works. :)
 * @param Xfirst
 * @param Yfisrt
 * @param Xsecond
 * @param Ysecond
 */
void Swap(int Xfirst, int Yfisrt,  int Xsecond, int Ysecond){std::swap(ObjectMap[Xfirst][Yfisrt], ObjectMap[Xsecond][Ysecond]);}


private:
	/**2D dynamic Array of Objects, which is used as a map during the game.*/
	std::shared_ptr <Cobject> ** ObjectMap;
	/**Vector of active Ghosts --> because sometimes I dont know where they are*/
	std::vector <std::shared_ptr<Cobject>>  Octopusses;
	/**
	 * Vector, where are all active teleports.
	 */
	std::vector <std::shared_ptr<Cobject>> teleports;
	/**2D char Array used only because I needed to store the information from the file somewhere*/
	char ** CharMap;
	/** X coordinate of Pacman*/
	int XPacman;
	/** Y coordinate of Pacman*/
	int YPacman;
	int XPacmanStart;
	int YPacmanStart;
	/**How long are rows in the map */
	int length;
	/**How many lines have the map*/
	int lines;
	int lives;
	int score;
	/** Number of coins --> if it is equal to 0 --> you win!*/
	int Coincounter;
	/** How difficult the game will be */
	int difficulty;
	/**Is your map valid? */
	bool Valid;
	/**
	 * Represents how many cherries is on the map right now.
	 */
	int cherryCounter;
	int Octopuscounter;




};

#endif //MYPAC_CMAP_H
