//
// Created by winkleri on 11.5.19.
//

#ifndef MYPAC_CPACMAN_H
#define MYPAC_CPACMAN_H

#include <unistd.h>
#include <stdlib.h>
#include <cstdio>
#include <sys/ioctl.h>
#include <termios.h>
#include <chrono>


#include "CMoveable.h"


/**
 * This class represents the main character of this game. PACMAN.
 */
class CPacman: public CMoveable{
public:
	/**
	 * Constructor
	 * @param x Start coordinate of Pacman.
	 * @param y tart coordinate of Pacman
	 * @param lives
	 */
	CPacman(int x, int y, int lives) :letter('P'), XPacman(x), YPacman(y),
	lives(lives) , OldX(x), OldY(y), Xstart(x), Ystart(y), teleported(false){}

/**
 * Return shared_ptr on this object.
 * @return
 */
	virtual std::shared_ptr<CMoveable> MoveableClone() const;
	virtual char getMoveableLetter() const;
	virtual void move(const std::vector <std::pair<int, int> > & Possibilities = std::vector <std::pair<int, int> > (),int x =0, int y=0);
	virtual void moveBack();
	virtual void PossibleMoves(int x){return;}
	virtual void movePossibleBack(){return;}


	int getX()const{return XPacman;}
	int getY()const{return YPacman;}
	int getOldX()const{return OldX;}
	int getOldY()const{return OldY;}
	virtual int getLastObj() const{return 0;}
	virtual bool GetRage(){return false ;}
	virtual int getStartX()const{return Xstart;}
	virtual int getStartY()const{return Ystart;}
	virtual bool getTeleported(){return teleported;}



	virtual void setLastObj(int x) {return;}
	int GetChar();
	virtual void Collision (std::shared_ptr <Cobject>  & a) {return;};


	virtual bool isWall() const{return false;};
	virtual bool isCoin() const{return false;};
	virtual bool isOctopus() const{return false;};
	virtual bool isCherry() const{return false;};
	virtual bool isPacman() const{return true;}
	virtual bool isNothing() const{return false;}
	virtual bool isKiller() const{return false;}
	virtual bool isTeleport() const{return false;};


	virtual void getToStart (){XPacman = Xstart; YPacman = Ystart;}
	virtual void SetChasing(bool Chase){return;}
	virtual void increaseChase(){return;}
	virtual int getChaseCounter(){return 0;}
	virtual bool getChase() {return false;}
	virtual bool GetMeHome(){return false;}
	virtual void SetXY(int x, int y){XPacman = x ; YPacman = y;}
	virtual void SetMeHome(bool Home){return;}
	virtual void SetRandom(bool random){return;}
	virtual bool GetRandom(){return false;}
	virtual void SetRage(bool rage){return;}
	virtual void setTeleported(bool teleport){teleported = teleport;}



private :
	char letter;
	int XPacman;
	int YPacman;
	int lives;
	int OldX;
	int OldY;
	int Xstart;
	int Ystart;
	bool teleported;
};

#endif //MYPAC_CPACMAN_H
