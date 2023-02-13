//
// Created by winkleri on 11.5.19.
//

#ifndef MYPAC_CCOIN_H
#define MYPAC_CCOIN_H
#include "Cobject.h"

/**
 * Represents coin.
 */
class Ccoin:public Cobject{
public:
/**
 * Constructor
 * @param x
 * @param y
 */
	Ccoin(int x, int y): letter('.'), Xcoin(x), Ycoin(y){}
	/**
	 * Return shared_ptr on this object.
	 * @param x
	 * @param y
	 */

	virtual std::shared_ptr <Cobject> clone () const;

	virtual void moveBack(){return;}
	virtual void move(const std::vector <std::pair<int, int> > & Possibilities = std::vector <std::pair<int, int> > (),int x =0, int y=0 ){return;}
	virtual int getX()const{return Xcoin;}
	virtual int getY()const{return Ycoin;}
	virtual void setLastObj(int x) {return;}
	virtual void setTeleported(bool teleport){return;}
	virtual bool getTeleported(){return false;}


	virtual bool isWall()const{return false;}
	virtual bool isCoin() const{return true;}
	virtual bool isOctopus() const{return false;}
	virtual bool isCherry()const {return false;}
	virtual bool isPacman()const {return false;}
	virtual bool isNothing()const {return false;}
	virtual bool isKiller()const{return false;}
	virtual bool isTeleport() const{return false;};





	virtual bool GetRage(){return false;}
	virtual char  getLetter() const;
	virtual int getOldX()const{return Xcoin;}
	virtual int getOldY()const{return Ycoin;}
	virtual int getStartX()const{return Xcoin;}
	virtual int getStartY()const{return Ycoin;}
	virtual int getLastObj() const{return 1;}



	virtual void getToStart (){return;}
	void PossibleMoves(int x){return;}
	virtual void movePossibleBack(){return;};
	virtual void SetChasing(bool Chase){return;}
	virtual int getChaseCounter(){return 0;}
	virtual bool getChase() {return false;}
	virtual bool GetMeHome(){return false;}
	virtual void SetXY(int x, int y){Xcoin= x ; Ycoin = y;}
	virtual void SetMeHome(bool Home){return;}
	virtual void SetRandom(bool random){return;}
	virtual bool GetRandom(){return false;}
	virtual void SetRage(bool rage){return;}


private:
	char letter;
	int Xcoin;
	int Ycoin;
};




#endif //MYPAC_CCOIN_H
