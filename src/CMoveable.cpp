//
// Created by winkleri on 11.5.19.
//

#include "CMoveable.h"

std::shared_ptr <Cobject> CMoveable::clone () const{
	return (*this).MoveableClone();
}

char  CMoveable::getLetter() const{
	return (*this).getMoveableLetter();
}



