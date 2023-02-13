//
// Created by winkleri on 11.5.19.
//

#ifndef MYPAC_CCHERRY_H
#define MYPAC_CCHERRY_H

#include "Cobject.h"

/**
 * Represents cherry.
 */


class Ccherry:public Cobject{
public:
	/**
	 * constructor
	 * @param x coordinates
	 * @param y coordinates
	 */
	Ccherry(int x, int y): letter('c'), Xcher(x), Ycher(y){}
/**
 * Return shared_ptr on this object.
 * @return
 */
	virtual std::shared_ptr <Cobject> clone () const;
	/**
	 * Getter
	 * @return
	 */
	virtual char  getLetter() const;
	virtual void getToStart (){return;}
	virtual int getOldX()const{return Xcher;};
	virtual int getOldY()const{return Ycher;};
	virtual int getStartX()const{return Xcher;}
	virtual int getStartY()const{return Ycher;}
	virtual int getX()const{return Xcher;}
	virtual int getY()const{return Ycher;}
	virtual int getLastObj() const{return 2;}
	virtual bool GetRage(){return false;}
	virtual bool getChase() {return false;}
	virtual int getChaseCounter(){return 0;}
	virtual bool getTeleported(){return false;}


	/**
	 * Yes, I know. Cherry does not move.
	 * @param Possibilities
	 * @param x
	 * @param y
	 */
	virtual void move(const std::vector <std::pair<int, int> > & Possibilities = std::vector <std::pair<int, int> > (),int x =0, int y=0){return;}
	virtual void moveBack(){return;}
	virtual void PossibleMoves(int x){return;}
	virtual void movePossibleBack(){return;}

	virtual void setLastObj(int x) {return;}
	virtual void SetChasing(bool Chase){return;}
	virtual bool GetMeHome(){return false;}
	virtual void SetXY(int x, int y){Xcher = x ; Ycher= y;}
	virtual void SetMeHome(bool Home){return;}
	virtual void SetRandom(bool random){return;}
	virtual bool GetRandom(){return false;}
	virtual void SetRage(bool rage){return;}
	virtual void setTeleported(bool teleport){return;}

	virtual bool isWall()const{return false;}
	virtual bool isCoin() const{return false;}
	virtual bool isOctopus()const {return false;}
	virtual bool isCherry()const {return true;};
	virtual bool isPacman()const {return false;}
	virtual bool isNothing()const {return false;}
	virtual bool isKiller()const{return false;}
	virtual bool isTeleport() const{return false;};


private:
	char letter;
	int Xcher;
	int Ycher;
};

#endif //MYPAC_CCHERRY_H
