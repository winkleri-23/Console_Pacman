//
// Created by winkleri on 12.5.19.
//

#ifndef MYPAC_COCTOPUS_H
#define MYPAC_COCTOPUS_H



#include "CMoveable.h"

/**
 * Represents octopuses(ghosts).
 */
class Coctopus: public CMoveable{
public:



	Coctopus(int x, int y,int Obj) :letter('X'), Xoct(x), Yoct(y), OldX(x), OldY(y),
	StartX(x), StartY(y),LastObj(Obj), OldXPossible(x), OldYPossible(y),Chasing(false),Getmehome(false),
	Chasingcounter(0),Random{false}, Rage(false), Ragecounter(0) {}
	virtual std::shared_ptr<CMoveable> MoveableClone() const;
	virtual char getMoveableLetter() const;
	virtual void move(const std::vector <std::pair<int, int> > & Possibilities = std::vector <std::pair<int, int> > (),int x =0, int y=0 );
	virtual void moveBack(){Xoct = OldX; Yoct =OldY;}
	virtual void movePossibleBack(){Xoct = OldXPossible; Yoct = OldYPossible;};
	virtual void PossibleMoves(int x);
	virtual int getX()const{return Xoct;}
	virtual int getY()const{return Yoct;}
	virtual int getLastObj() const{return LastObj;}
	virtual void setLastObj(int x) {LastObj = x;}

	virtual int getOldX()const{return OldX;};
	virtual int getOldY()const{return OldY;};
	virtual void getToStart (){Xoct = StartX; Yoct = StartY; Ragecounter = 0; }
	virtual int getStartX()const{return StartX;}
	virtual int getStartY()const{return StartY;}
	virtual int getChaseCounter(){Chasingcounter++; return Chasingcounter;}
	virtual bool getChase() {return Chasing;}
	virtual bool GetMeHome(){if(StartX == Xoct && StartY == Yoct){Getmehome = false;}return Getmehome;}
	virtual bool GetRandom(){return Random;}
	virtual bool GetRage(){return Rage;}
	virtual bool getTeleported(){return false;}


/**
 * Function that determine if the octopus should chase Pacman or not.
 * @param Chase
 */
	virtual void SetChasing(bool Chase){Chasing= Chase; Chasingcounter =0; Getmehome = false;}
	/**
	 * Function that set boolean if the octopus is coming home or not.
	 * @param Home
	 */
	virtual void SetMeHome(bool Home){Getmehome = Home;}
	virtual void SetXY(int x, int y){Xoct = x ; Yoct = y;}
	virtual void setTeleported(bool teleport){return;}
	/**
	 * Set boolean, which determine if the octopus is moving random or not.
	 * @param random
	 */
	virtual void SetRandom(bool random){ Random = random;}
	/**
	 * Set Rage factor --> Octopuses can be eaten.
	 * @param rage
	 */
	virtual void SetRage(bool rage){if(rage){letter = 'M';} if(!rage){letter = 'X';if(Rage == true){Getmehome = true;}} Rage = rage; }

	virtual bool isWall()const{return false;}
	virtual bool isCoin() const{return false;}
	virtual bool isOctopus() const{return true;}
	virtual bool isCherry()const {return false;}
	virtual bool isPacman() const{return false;}
	virtual bool isNothing()const {return false;}
	virtual bool isKiller()const{return false;}
	virtual bool isTeleport() const{return false;};



private :
	/**
	 * char, which represents the object when it is printed
	 */
	char letter;
	/**
	 * X coordinate
	 */
	int Xoct;
	/**
	 * Y coordinate
	 */
	int Yoct;
	/**
	 * X coordinate before last move
	 */
	int OldX;
	/**
	 * Y coordinate before last move
	 */
	int OldY;
	/**
	 * X coordinate where the Octopus started
	 */
	int StartX;
	/**
	 * Y coordinate where the Octopus started.
	 */
	int StartY;
	/**
	 * Information about, which object was replaced by Octopus
	 */
	int LastObj;
	/**
	 * Temporary --> used when you need possible moves.
	 */
	int OldXPossible;
	/**
	 * Temporary --> used when you need possible moves.
	 */
	int OldYPossible;
	/**
	 * Boolean, which represents if the Octopus chasing Pacman right now or not.
	 */
	bool Chasing;
	/**
	 * Boolean, which represents if the Octopus going home right now or not.
	 */
	bool Getmehome;
	/**
	 * Represents how many moves the Pacman is chased by this Octopus.
	 */
	int Chasingcounter;
	/**
	 * Boolean, which represents if the octopus act Random or not.
	 */
	bool Random;
	/**
	 * Boolean, which represents if the rage mode is activated and the Octopus can be eaten.
	 */
	bool Rage;
	/**
	 * Represents how many moves the Octopus is in rage mode.
	 */
	int Ragecounter;

};


#endif //MYPAC_COCTOPUS_H
