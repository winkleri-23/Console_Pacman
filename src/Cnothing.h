//
// Created by winkleri on 12.5.19.
//

#ifndef MYPAC_CNOTHING_H
#define MYPAC_CNOTHING_H


#include "Cobject.h"

/**
 * Represents "nothing". I know it sounds stupid, but its important to represent free space.
 */

class Cnothing:public Cobject{
public:

	/**
	 * Constructor
	 * @param x
	 * @param y
	 */
	Cnothing(int x, int y): letter(' '), Xnoth(x), Ynoth(y){}

	/**
	 * Return shared_ptr on this object.
	 * @return
	 */
	std::shared_ptr<Cobject> clone() const {return std::make_shared<Cnothing>(*this);}



	virtual void move (const std::vector <std::pair<int, int> > & Possibilities = std::vector <std::pair<int, int> > (),int x =0, int y=0 ){return;}
	virtual char getLetter() const {return letter;}
	virtual void moveBack(){return;}
	virtual void PossibleMoves(int x){return;}
	virtual void movePossibleBack(){return;}


	virtual int getX()const{ return Xnoth;}
	virtual int getY()const{return Ynoth;}
	virtual int getLastObj() const{return 0;}
	virtual int getOldX()const{return Xnoth;};
	virtual int getOldY()const{return Ynoth;};
	virtual int getStartX()const{return Xnoth;}
	virtual int getStartY()const{return Ynoth;}
	virtual bool GetRandom(){return false;}
	virtual void SetRage(bool rage){return;}
	virtual bool GetRage(){return false;}
	virtual void getToStart (){return;}
	virtual bool getChase() {return false;}
	virtual bool GetMeHome(){return false;}
	virtual bool getTeleported(){return false;}



	virtual bool isWall()const{return false;}
	virtual bool isCoin()const {return false;}
	virtual bool isOctopus()const {return false;}
	virtual bool isPacman()const {return false;}
	virtual bool isCherry()const {return false;}
	virtual bool isNothing()const {return true;}
	virtual bool isKiller()const{return false;}
	virtual bool isTeleport() const{return false;};
	virtual void SetChasing(bool Chase){return;}



	virtual int getChaseCounter(){return 0;}
	virtual void SetXY(int x, int y){Xnoth = x ; Ynoth = y;}
	virtual void setTeleported(bool teleport){return;}


	virtual void setLastObj(int x) {return; }
	virtual void SetMeHome(bool Home){return;}
	virtual void SetRandom(bool random){return;}

private:
	char letter;
	int Xnoth;
	int Ynoth;
};
#endif //MYPAC_CNOTHING_H
