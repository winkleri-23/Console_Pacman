//
// Created by winkleri on 11.5.19.
//
#include <iostream>
#include "CPacman.h"

std::shared_ptr<CMoveable> CPacman::MoveableClone() const {
	return std::make_shared<CPacman>(*this);
}

char CPacman::getMoveableLetter() const {
	return letter;
}

void CPacman::move(const std::vector <std::pair<int, int> > & Possibilities,int x , int y) {
	int key;
	key = GetChar();
	OldX = XPacman;
	OldY = YPacman;

	switch (key) {
		case 119:
			XPacman--;
			break;                                                            //W
		case 115 :
			XPacman++;                                                        //S
			break;
		case 97 :
			YPacman--;
			break;                                                            //A
		case 100:
			YPacman++;
			break;//D
		default:
			break;
	}


}

void CPacman::moveBack(){
	XPacman = OldX;
	YPacman = OldY;
}






int CPacman::GetChar() { //StackOverflow
	int ch;
	struct termios oldt;
	struct termios newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	return ch;
}