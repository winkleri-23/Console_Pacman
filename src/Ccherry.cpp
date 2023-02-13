//
// Created by winkleri on 11.5.19.
//

#include "Ccherry.h"

std::shared_ptr<Cobject> Ccherry::clone() const {
	return std::make_shared<Ccherry>(*this);
}

char  Ccherry::getLetter() const {
	return letter;
}