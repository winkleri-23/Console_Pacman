//
// Created by winkleri on 11.5.19.
//

#include "Cwall.h"


std::shared_ptr<Cobject> Cwall::clone() const {
	return std::make_shared<Cwall>(*this);
}

char  Cwall::getLetter() const {
	return letter;
}