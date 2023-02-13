//
// Created by winkleri on 11.5.19.
//

#ifndef MYPAC_CMOVEABLE_H
#define MYPAC_CMOVEABLE_H

#include "Cobject.h"


/**
 * Represents moveable objects.
 */
class CMoveable:public Cobject{
public:
	virtual std::shared_ptr <Cobject> clone () const ;
	virtual char  getLetter() const;


	virtual std::shared_ptr<CMoveable> MoveableClone() const = 0;
	virtual char getMoveableLetter() const = 0;

	//virtual void move() = 0;
	//virtual void Collision (const Cobject  & a) = 0;

};


#endif //MYPAC_CMOVEABLE_H
