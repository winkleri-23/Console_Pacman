//
// Created by winkleri on 11.5.19.
//

#include "Ccoin.h"

std::shared_ptr<Cobject> Ccoin::clone() const {
	return std::make_shared<Ccoin>(*this);
}

char  Ccoin::getLetter() const {
	return letter;
}