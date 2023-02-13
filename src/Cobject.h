//
// Created by winkleri on 11.5.19.
//

#ifndef MYPAC_COBJECT_CPP
#define MYPAC_COBJECT_CPP

/**
 * The most importan  object. From this object inherit all the others.
 */
#include <memory>
#include<iostream>
#include<stdlib.h>
#include <vector>
class Cobject{
public:
	/**
	 * Virtual method which create shared_ptr on the object.
	 * @return
	 */
	virtual std::shared_ptr <Cobject> clone () const =0;

	/**
	 * Returns object letter.
	 * @return
	 */
	virtual char getLetter() const = 0;
	/**
	 * Returns X coordinate.
	 * @return
	 */
	virtual int getX() const= 0;
	/**
	 * Returns  Y coordinate.
	 * @return
	 */
	virtual int getY() const= 0;

	/**
	 * Returns X coordinate before last move.
	 * @return
	 */
	virtual int getOldX() const =0;

	/**
	 * Returns Y coordinate before last move.
	 * @return
	 */
	virtual int getOldY() const=0;

	/**
	 * Returns X coordinate where the object started.
	 * @return
	 */
	virtual int getStartX() const=0 ;

	/**
	 * Returns Y coordinate where the object started.
	 * @return
	 */
	virtual int getStartY() const=0 ;

	/**
	 * Returns which object was on place before Octopus came.
	 * @return
	 */
	virtual int getLastObj() const = 0;

    /**
     * Returns if the Octopus move random right now or not.
     * @return
     */
	virtual bool GetRandom()=0;
	virtual void SetXY(int x, int y) = 0;

/**
 * Returns if the Octopus is chasing Pacman or not.
 * @return
 */
	virtual bool getChase() = 0;

	/**
	 * Returns if Pacman is in rage mode and can eat Octopuses.
	 * @return
	 */
	virtual bool GetRage() = 0;
	virtual bool getTeleported()=0;
	/**
	 * Retuns how many moves Octopus chasing Pacman.
	 * @return
	 */
	virtual int getChaseCounter()=0;

	/**
	 * Returns if Octopus going home right now or not.
	 * @return
	 */

	virtual bool GetMeHome()=0;

	/**
	 * Call function, I am going home.
	 */
	virtual void getToStart () = 0;

	/**
	 * Set if Octopus chasing Pacman right now or not.
	 * @param Chase
	 */
	virtual void SetChasing(bool Chase)=0;

	/**
	 * Set if Octopus should come back home.
	 * @param Home
	 */
	virtual void SetMeHome(bool Home)=0;
	/**
	 * Set if the Octopus should move Random or using algorithm.
	 */
	virtual void SetRandom(bool random)=0;
	/**
	 * Set if the Octopus can be eaten.
	 * @param rage
	 */
	virtual void SetRage(bool rage) =0;

/**
 * Set which object was on the place, which was captured by Octopus.
 * @param x
 */
	virtual void setLastObj(int x) =0;

	/**
	 * Virtual method which allows some objects to move. Pacman is controlled by the user and the Octopuses are
	 * controlled by the AI.
	 * @param Possibilities vector of possible moves - useful in some cases.
	 * @param x
	 * @param y
	 */

	virtual void move(const std::vector <std::pair<int, int> > & Possibilities = std::vector <std::pair<int, int> > (), int x =0, int y=0 ) = 0;

	/**
	 * Find out the possible moves for object.
	 * @param x
	 */
	virtual void PossibleMoves(int x) =0;
	/**
	 * Function that return the object to last position. This function is needed when we are trying to find possible moves.
	 */
	virtual void movePossibleBack() =0;

	/**
	 * Return to last position. No meter what, just last position.
	 */
	virtual void moveBack() = 0;



/**
 * Boolean function, which answer the question "Are you a wall?"
 * @return
 */
	virtual bool isWall() const=0;
/**
 * Boolean function, which answer the question "Are you a coin?"
 * @return
 */
	virtual bool isCoin() const=0;

/**
 * Boolean function, which answer the question "Are you an Octopus?"
 * @return
 */
	virtual bool isOctopus() const=0;

/**
 * Boolean function, which answer the question "Are you a cherry?"
 * @return
 */
	virtual bool isCherry() const=0;

/**
 * Boolean function, which answer the question "Are you a Pacman?"
 * @return
 */
	virtual bool isPacman() const= 0;

/**
 * Boolean function, which answer the question "Are you nothing?"
 * @return
 */
	virtual bool isNothing() const=0;

/**
 * Boolean function, which answer the question "Are you a killer?"
 * @return
 */
	virtual bool isKiller() const=0;
/**
 * Boolean function, which answer the question "Are you a teleport?"
 * @return
 */
	virtual bool isTeleport()const=0;
	/**
	 * Set Pacman boolean if it was teleported or not.
	 */
	virtual void setTeleported(bool teleport) =0;
};

#endif //MYPAC_COBJECT_CPP
