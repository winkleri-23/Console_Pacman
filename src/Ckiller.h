//
// Created by winkleri on 15.5.19.
//

#ifndef MYPAC_CKILLER_H
#define MYPAC_CKILLER_H

#endif //MYPAC_CKILLER_H

#include "Cobject.h"

/**
 * Represents objects which allows Pacman to eat Octopuses.
 */
class Ckiller:public Cobject{
public:
	/**
	 * Constructor
	 * @param x
	 * @param y
	 */
	Ckiller(int x, int y): letter('K'), Xkill(x), Ykill(y){}
	virtual std::shared_ptr <Cobject> clone () const{return std::make_shared<Ckiller>(*this);}


	virtual char  getLetter() const{return letter;}
	virtual bool GetRage(){return false;}
	virtual int getOldX()const{return Xkill;};
	virtual int getOldY()const{return Ykill;};
	virtual int getStartX()const{return Xkill;}
	virtual int getStartY()const{return Ykill;}
	virtual int getX()const{return Xkill;}
	virtual int getY()const{return Ykill;}
	virtual int getLastObj() const{return 0;}
	virtual int getChaseCounter(){return 0;}
	virtual bool getChase() {return false;}
	virtual bool GetRandom(){return false;}
	virtual bool getTeleported(){return false;}


	virtual void setLastObj(int x) {return;}
	virtual void SetXY(int x, int y){Xkill = x ; Ykill = y;}
	virtual void SetChasing(bool Chase){return;}
	virtual void SetRage(bool rage){return;}
	virtual void SetRandom(bool random){return;}
	virtual void SetMeHome(bool Home){return;}
	virtual void setTeleported(bool teleport){return;}


	virtual void move(const std::vector <std::pair<int, int> > & Possibilities = std::vector <std::pair<int, int> > (),int x =0, int y=0 ){return;}
	virtual void moveBack(){return;}
	virtual void PossibleMoves(int x){return;}
	virtual void movePossibleBack(){return;}
	virtual bool isWall()const{return false;}
	virtual bool isCoin() const{return false;}
	virtual bool isOctopus()const {return false;}
	virtual bool isCherry() const{return false;}
	virtual bool isPacman() const{return false;}
	virtual bool isNothing() const{return false;}
	virtual bool isKiller()const{return true;}
	virtual bool isTeleport() const{return false;}

	virtual void getToStart (){return;}
	virtual bool GetMeHome(){return false;}




private:
	char letter;
	int Xkill;
	int Ykill;
};