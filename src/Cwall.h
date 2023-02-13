//
// Created by winkleri on 11.5.19.
//

#ifndef MYPAC_CWALL_H
#define MYPAC_CWALL_H

#include "Cobject.h"
/**
 * Class which represents Wall.
 */
class Cwall:public Cobject{
public:
	/**
	 * Constructor
	 * @param x Xposition
	 * @param y Yposition
	 */
	Cwall(int x, int y): letter('#'), Xwall(x), Ywall(y){}

	/**
	 * Return the right shared_ptr.
	 * @return
	 */
	virtual std::shared_ptr <Cobject> clone () const;

	virtual bool GetRage(){return false;}
	virtual int getX()const{return Xwall;}
	virtual int getY()const{return Ywall;}
	virtual char  getLetter() const;
	virtual int getOldX()const{return Xwall;};
	virtual int getOldY()const{return Ywall;};
	virtual int getStartX()const{return Xwall;}
	virtual int getStartY()const{return Ywall;}
	virtual bool GetRandom(){return false;}
	virtual int getLastObj() const{return 0;}
	virtual int getChaseCounter(){return 0;}
	virtual bool GetMeHome(){return false;}
	virtual bool getChase() {return false;}
	virtual bool getTeleported(){return false;}


	virtual void setLastObj(int x) {return;}
	virtual void SetXY(int x, int y){Xwall = x ; Ywall = y;}
	virtual void SetMeHome(bool Home){return;}
	virtual void SetRandom(bool random){return;}
	virtual void SetChasing(bool Chase){return;}
	virtual void SetRage(bool rage){return;}
	virtual void setTeleported(bool teleport){return;}


	/**
	 * Move function for the wall..haha..I know.
	 * @param Possibilities
	 * @param x
	 * @param y
	 */
	virtual void move(const std::vector <std::pair<int, int> > & Possibilities = std::vector <std::pair<int, int> > (),int x =0, int y=0 ){return;}
	virtual void moveBack(){return;}
	virtual void PossibleMoves(int x){return;}
	virtual void movePossibleBack(){return;}

	virtual bool isWall()const{return true;}
	virtual bool isCoin()const {return false;}
	virtual bool isOctopus()const {return false;}
	virtual bool isCherry() const{return false;}
	virtual bool isPacman()const {return false;}
	virtual bool isNothing()const {return false;}
	virtual bool isKiller()const{return false;}
	virtual bool isTeleport() const{return false;};


	virtual void getToStart (){return;}



private:
	char letter;
	int Xwall;
	int Ywall;
};



#endif //MYPAC_CWALL_H
