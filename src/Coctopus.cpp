//
// Created by winkleri on 12.5.19.
//

#include "Coctopus.h"

std::shared_ptr<CMoveable> Coctopus::MoveableClone() const {
	return std::make_shared<Coctopus>(*this);
}

char Coctopus::getMoveableLetter() const {
	return letter;
}

void Coctopus::PossibleMoves(int x) {
	OldXPossible = Xoct;
	OldYPossible = Yoct;
	if (x == 0) {
		Xoct--;
	}
	if (x == 1) {
		Xoct++;
	}
	if (x == 2) {
		Yoct--;
	}
	if (x == 3) {
		Yoct++;
	}

}


void Coctopus::move(const std::vector<std::pair<int, int> > &Possibilities, int x, int y) {
	if (!Possibilities.empty()) {
		int num = 0;
		int Possiblecounter = 0;
		Possiblecounter = Possibilities.size();

		if (Random || Rage) { // Using when the Random movement is activeted
			random();
			num = (std::rand() % Possiblecounter);


			auto iter = Possibilities.begin();
			Possiblecounter = Possibilities.size();
			random();
			num = std::rand() % Possiblecounter;
			for (int i = 0; i < num; i++) {
				iter++;
			}
			OldX = Xoct;
			OldY = Yoct;
			Xoct = iter->first;
			Yoct = iter->second;

			if (Rage) {
				Ragecounter++;
				if (Ragecounter == 20) {
					SetRage(false);
					Ragecounter = 0;
				}
			}
			return;
		}

		if (Getmehome) { // need information from  bfs
			OldX = Xoct;
			OldY = Yoct;
			Xoct = x;
			Yoct = y;

		} else if (Chasing) {
			OldX = Xoct;
			OldY = Yoct;
			Xoct = x;
			Yoct = y;

		} else {
			random();
			num = (std::rand() % Possiblecounter);
			OldX = Xoct;
			OldY = Yoct;
			int counter = 0;
			for (auto i : Possibilities) {
				if (num == counter) {
					Xoct = i.first;
					Yoct = i.second;
				}
				counter++;
			}
		}
	} else{
		return;
	}
}
