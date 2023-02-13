//
// Created by winkleri on 12.5.19.
//
#define Easy 0
#define Medium 1
#define Hard 2
#define Dead 0
#define noCoin 0
#define Hardchasing 70
#define Easychasing 50
#define Easycherry  30
#define Medcherry   50
#define Hardcherry  70
#define Maxdistance 120
#define Coin 1
#define Nothing 0
#define Cherry 2
#define Killer	 3



#include "Cgame.h"

bool Cgame::PacmanCOllision() {
	bool wall = false;
	bool died = false;
	bool skip = false;
	bool firstRun = true;
	bool Teleport = false;
	int cherryCounter = 0;
	FindTheNearest();
	while (true) {
		died = false;
		system("clear");
		if (!firstRun) { if (OctopusMoving()) { return true; }} // Octopus moving using their algorithm
		NewCherry(GameMap.GetDifficulty(), cherryCounter, skip); // Should be generate next  cherry?
		firstRun = false;
		GameMap.printArray();
		auto Pacman = GameMap.GetObject(GameMap.getXPac(), GameMap.getYPac());
		(*Pacman).move();
		if (GameMap.GetObject((*Pacman).getX(), (*Pacman).getY())->isWall()) { // You cant go there if there is a wall
			(*Pacman).moveBack();
		} else if (GameMap.GetObject((*Pacman).getX(), (*Pacman).getY())->isCoin()) {
			if (!PacmanToCoin(Pacman, wall, died, Teleport)) {return false;	}
		} else if (GameMap.GetObject((*Pacman).getX(), (*Pacman).getY())->isOctopus()) {
			if (PacmanToOct(Pacman, wall, died, Teleport)) {return true;}
		} else if (GameMap.GetObject((*Pacman).getX(), (*Pacman).getY())->isCherry()) {
			PacmanToCherry(Pacman, wall, died, Teleport);
		} else if (GameMap.GetObject((*Pacman).getX(), (*Pacman).getY())->isKiller()) {
			PacmanToKiller(Pacman, wall, died, Teleport);
		} else if (GameMap.GetObject((*Pacman).getX(), (*Pacman).getY())->isTeleport()) {
			PacmanToTel(Pacman, wall, died, Teleport);
		} else {
			GameMap.setObject((*Pacman).getX(), (*Pacman).getY(), (*Pacman));
			wall = true;
		}
		if (!died) {
			if (wall) {
				if (GameMap.getXPac() != (*Pacman).getX() || GameMap.getYPac() !=
															 (*Pacman).getY()) { // if the position changed, evaluate which object should be placet on the old place
					if (Teleport) {
						Cteleport c(GameMap.getXPac(), GameMap.getYPac());
						GameMap.setObject(GameMap.getXPac(), GameMap.getYPac(), c);
						(*Pacman).setTeleported(false);
					} else {
						Cnothing c(GameMap.getXPac(), GameMap.getYPac());
						GameMap.setObject(GameMap.getXPac(), GameMap.getYPac(), c);
					}
					Teleport = (*Pacman).getTeleported();
				}
			}
			if (wall) {
				GameMap.setXPac((*Pacman).getX()); // Set information about where the Pacman is.
				GameMap.setYPac((*Pacman).getY());
				wall = false;
			}
		}
	}
}

void Cgame::PacmanToCherry(std::shared_ptr <Cobject> & Pacman, bool & wall, bool & died, bool &Teleport){
	GameMap.setObject((*Pacman).getX(), (*Pacman).getY(), (*Pacman));
	wall = true;
	GameMap.takeCherry(); // give me score
}

void Cgame::PacmanToKiller(std::shared_ptr <Cobject> & Pacman, bool & wall, bool & died, bool &Teleport){
	GameMap.setObject((*Pacman).getX(), (*Pacman).getY(), (*Pacman));
	for (auto &i : GameMap.GetVector()) { // active rage mode --> all octopuses can be eaten
		i->SetRage(true);
		i->SetRandom(true);
	}
	wall = true;
}

bool Cgame::PacmanToCoin(std::shared_ptr<Cobject> &Pacman, bool &wall, bool &died, bool &Teleport) {
	GameMap.setObject((*Pacman).getX(), (*Pacman).getY(), (*Pacman));
	wall = true;
	GameMap.takeCoin();
	if (GameMap.getCoins() == noCoin) {
		Cmenu a;
		a.printWin(GameMap.getScore());
		return false;
	}
	return true;
}


bool Cgame::OctopusCollision() {
	int WannaX = 0;
	int WannaY = 0;
	bool skip = false;
	std::vector<std::pair<int, int>> Possibilities;
	for (auto &i : GameMap.GetVector()) {
		if (FindPossibleMoves(Possibilities, i, skip)) { return true; }
		if (skip) {
			skip = false;
			continue;
		}
		if (i->getChase()) { // Is the octopus chasing Pacman?
			int howLong;
			if (GameMap.GetDifficulty() == Medium) { // Difficult determine how long the octopus will chase Pacman.
				howLong = Hardchasing;
			} else {
				howLong = Easychasing;
			}
			if (i->getChaseCounter() > howLong) {
				FindTheNearest();
				i->SetMeHome(true);
			}
		}
		if (i->getX() == i->getStartX() && i->getY() == i->getStartY()) {
			i->SetMeHome(false);
		}
		if (i->GetMeHome()) {
			if (!Hunter(i, WannaX, WannaY, i->getStartX(), i->getStartY())) {
				i->SetRandom(true);
			}
		} else if (i->getChase()) {
			if (!Hunter(i, WannaX, WannaY, GameMap.getXPac(), GameMap.getYPac())) {
				i->SetRandom(true);
			}
		}
		i->move(Possibilities, WannaX, WannaY); // Set the new position of Octopus acording bfs or other alg.
		i->SetRandom(false);
		if (NextObj(i, Possibilities)) {
			return true;
		}
	}
	return false;
}

bool
Cgame::FindPossibleMoves(std::vector<std::pair<int, int>> &Possibilities, std::shared_ptr<Cobject> &i, bool &skip) {
	int counter = 0;
	while (true) {
		i->PossibleMoves(counter);

		if (GameMap.GetObject(i->getX(), i->getY())->isWall() ||
			GameMap.GetObject(i->getX(), i->getY())->isOctopus() ||
			GameMap.GetObject(i->getX(), i->getY())->isTeleport()) { //if the object is one of them, you shouldnt go there
			i->movePossibleBack();
		} else if (GameMap.GetObject(i->getX(), i->getY())->isPacman()) { // easy, if its Pacman, hunt him!
			i->movePossibleBack();
			if (!i->GetRage()) { // check if the Rage mode is activated or not
				return true;
			} else {
				std::shared_ptr<Cobject> tmpOct = (GameMap.GetObject(i->getX(), i->getY()));
				for (auto &i : GameMap.GetVector()) {
					if (i->getX() == tmpOct->getX() && i->getY() == tmpOct->getY()) {
						GameMap.Swap(i->getX(), i->getY(), i->getStartX(), i->getStartY());
						i->getToStart();
						i->SetRage(false);
					}
				}
				skip = true;
			}
		} else if (GameMap.GetObject(i->getX(), i->getY())->isCoin()) { // you can go throughout the coin
			Possibilities.emplace_back(std::make_pair(i->getX(), i->getY()));
			i->movePossibleBack();
		} else if (GameMap.GetObject(i->getX(), i->getY())->isNothing()) {
			Possibilities.emplace_back(std::make_pair(i->getX(), i->getY()));
			i->movePossibleBack();
		} else if (GameMap.GetObject(i->getX(), i->getY())->isCherry()) {
			Possibilities.emplace_back(std::make_pair(i->getX(), i->getY()));
			i->movePossibleBack();
		} else if (GameMap.GetObject(i->getX(), i->getY())->isKiller()) {
			Possibilities.emplace_back(std::make_pair(i->getX(), i->getY()));
			i->movePossibleBack();
		} else {
			break;
		}
		counter++;
		if (counter == 4) {
			break;
		}
	}
	return false;
}

bool Cgame::NextObj(std::shared_ptr<Cobject> &i, std::vector<std::pair<int, int>> &Possibilities) {
	int tmp = 0;
	if (GameMap.GetObject(i->getX(), i->getY())->isPacman()) {
		i->moveBack();
		return true;
	} else if (GameMap.GetObject(i->getX(), i->getY())->isCoin()) {
		tmp = i->getLastObj();
		i->setLastObj(Coin);
	} else if (GameMap.GetObject(i->getX(), i->getY())->isNothing()) {
		tmp = i->getLastObj();
		i->setLastObj(Nothing);
	} else if (GameMap.GetObject(i->getX(), i->getY())->isCherry()) {
		tmp = i->getLastObj();
		i->setLastObj(Cherry);
	} else if (GameMap.GetObject(i->getX(), i->getY())->isKiller()) {
		tmp = i->getLastObj();
		i->setLastObj(Killer);
	}
	GameMap.setObject(i->getX(), i->getY(), *i);
	GameMap.ReplacingObject(i->getOldX(), i->getOldY(), tmp);
	Possibilities.clear();
	return false;
}


bool Cgame::Play() {
	return PacmanCOllision();
}

void Cgame::FindTheNearest() { // Find the nearest octopus
	int tmpDistance = Maxdistance;
	int HowManyOct = GameMap.GetVector().size();
	int howManyHounting = 0;
	for (auto &i : GameMap.GetVector()) {
		if (i->getChase()) {
			howManyHounting++;
		}
	}

	if (howManyHounting == HowManyOct) {
		random();
		int num = std::rand() % HowManyOct;
		int counter = 0;
		for (auto &i : GameMap.GetVector()) {
			i->SetChasing(false);
		}
		for (auto &i : GameMap.GetVector()) {
			if (counter == num) {
				i->SetChasing(true);
			}
			counter++;
		}
	} else {
		std::shared_ptr<Cobject> tmp;
		std::shared_ptr<Cobject> tmp2;
		for (auto &i : GameMap.GetVector()) {
			if ((abs(i->getX() - GameMap.getXPac()) + abs(GameMap.getYPac() - i->getY())) < tmpDistance &&
				!i->getChase()) {
				tmpDistance = abs(i->getX() - GameMap.getXPac()) + abs(GameMap.getYPac() - i->getY());
				tmp = i;
			}
		}


		for (auto &i : GameMap.GetVector()) {
			i->SetChasing(false);
		}

		tmp->SetChasing(true);
		if (GameMap.GetDifficulty() == Hard && GameMap.GetOctopuscount() >= 2 ) {
			tmpDistance = 90;
			for (auto &i : GameMap.GetVector()) {
				int Xoct = i->getX();
				int XPac = GameMap.getXPac();
				int Yoct = i->getY();
				int YPac = GameMap.getYPac();
				if ((abs(Xoct - XPac) + abs(YPac - Yoct)) < tmpDistance && !i->getChase()) {
					tmpDistance = abs(Xoct - XPac) + abs(YPac - Yoct);
					tmp2 = i;
				}
			}
			tmp2->SetChasing(true);
		}
	}

}


bool Cgame::Hunter(std::shared_ptr<Cobject> &Octopus, int &x, int &y, int XDest, int YDest) { // HUNTER MODE --> BFS
	std::vector<std::pair<int, int> > Result;
	int StartXBFS = Octopus->getX();
	int StartYBFS = Octopus->getY();
	std::pair<int, int> Home = std::make_pair(XDest, YDest);
	bool exist = false;
	std::map<std::pair<int, int>, std::pair<int, int>> MapVisited;
	std::queue<std::pair<std::pair<int, int>, std::pair<int, int>  >> que;
	que.push(std::make_pair(std::make_pair(Octopus->getX(), Octopus->getY()),
							std::make_pair(Octopus->getX(), Octopus->getY())));
	std::vector<std::pair<int, int>> Possibilities;
	std::set<std::pair<int, int >> SetVisited;
	while (!que.empty()) {
		std::pair<int, int> tmp = que.front().first;
		std::pair<int, int> from = que.front().second;
		if (tmp.first == Home.first && tmp.second == Home.second) {
			exist = true;
			MapVisited.insert(std::make_pair(tmp, from));
			auto iter = MapVisited.find(Home);
			bool firstRun = true;
			while (true) {
				if (iter->first.first == StartXBFS && iter->first.second == StartYBFS) {
					break;
				}
				if (firstRun) {
					Result.emplace_back(std::make_pair(iter->first.first, iter->first.second));
					firstRun = false;
				}
				Result.emplace_back(iter->second.first, iter->second.second);
				iter = MapVisited.find(std::make_pair(iter->second.first, iter->second.second));
			}
			break;
		}
		que.pop();
		if (SetVisited.find(tmp) != SetVisited.end()) {
			continue;
		}
		SetVisited.insert(tmp);
		MapVisited.insert(std::make_pair(tmp, from));
		from = tmp;
		FindPossibleMovesBFS(Possibilities, tmp); // Find all possible moves from possition
		auto Startiter = Possibilities.begin();
		for (auto iter = Startiter; iter != Possibilities.end(); iter++) {
			que.push(std::make_pair(std::make_pair(iter->first, iter->second), from));
		}
		Possibilities.clear();
	}
	if (exist) {
		if (!Result.empty()) {
			auto iter = Result.end();
			iter--;
			iter--;
			x = iter->first;
			y = iter->second;
		}
		return true;
	} else {
		return false;
	}

}

void Cgame::FindPossibleMovesBFS(std::vector<std::pair<int, int>> &Possibilities, std::pair<int, int> &tmp) { // Find possible moves for my bfs algorithm
	int counter = 0;
	while (true) {  // Possible moves for every position

		if (counter == 0) {
			tmp.first++;
		}
		if (counter == 1) {
			tmp.first--;
		}
		if (counter == 2) {
			tmp.second++;
		}
		if (counter == 3) {
			tmp.second--;
		}

		if (GameMap.GetObject(tmp.first, tmp.second)->isWall() ||
			GameMap.GetObject(tmp.first, tmp.second)->isOctopus() ||
			GameMap.GetObject(tmp.first, tmp.second)->isTeleport()) {
		} else if (GameMap.GetObject(tmp.first, tmp.second)->isPacman()) {
			Possibilities.emplace_back(std::make_pair(tmp.first, tmp.second));
		} else if (GameMap.GetObject(tmp.first, tmp.second)->isCoin()) {
			Possibilities.emplace_back(std::make_pair(tmp.first, tmp.second));
		} else if (GameMap.GetObject(tmp.first, tmp.second)->isNothing()) {
			Possibilities.emplace_back(std::make_pair(tmp.first, tmp.second));
		} else if (GameMap.GetObject(tmp.first, tmp.second)->isCherry()) {
			Possibilities.emplace_back(tmp.first, tmp.second);
		} else if (GameMap.GetObject(tmp.first, tmp.second)->isKiller()) {
			Possibilities.emplace_back(tmp.first, tmp.second);
		} else {
			break;
		}

		if (counter == 0) {
			tmp.first--;
		}
		if (counter == 1) {
			tmp.first++;
		}
		if (counter == 2) {
			tmp.second--;
		}
		if (counter == 3) {
			tmp.second++;
		}

		counter++;
		if (counter == 4) {
			break;
		}

	}
}


bool Cgame::OctopusMoving() {
	if (OctopusCollision()) {
		GameMap.takeDemage();
		if (GameMap.getLives() == Dead) {
			return true;
		}
		Cmenu A;
		A.printLostMenu();
		auto FindPacman = GameMap.GetObject(GameMap.getXPac(), GameMap.getYPac());
		for (auto &i : GameMap.GetVector()) {
			GameMap.Swap(i->getX(), i->getY(), i->getStartX(), i->getStartY());
			i->getToStart();
		}

		GameMap.Swap((*FindPacman).getX(), (*FindPacman).getY(), GameMap.getPacmanStartX(),
					 GameMap.getPacmanStartY());
		(*FindPacman).getToStart();
		GameMap.setXPac(GameMap.getPacmanStartX());
		GameMap.setYPac(GameMap.getPacmanStartY());
	}
	return false;
}


void Cgame::NewCherry(int Diff, int &cherryCounter, bool &skip) {
	bool notThis = false;
	if (GameMap.getCherrycount() < 3) {
		if ( (GameMap.GetDifficulty() == Easy && cherryCounter == Easycherry) ||
				(GameMap.GetDifficulty() == Medium && cherryCounter == Medcherry) ||
				(GameMap.GetDifficulty() == Hard && cherryCounter == Hardcherry)) {
				for (int i = 0; i < GameMap.getLines(); i++) {
					for (int j = 0; j < GameMap.getLength(); j++) {
						if (GameMap.GetObject(i, j)->isNothing()) {
							for (auto &f : GameMap.GetVector()) {
								if (f->getStartX() == i && f->getStartY() == j) {
									notThis = true;
								}
							}
							if (notThis) {
								notThis = false;
								continue;
							}
							Ccherry c(i, j);
							GameMap.setObject(i, j, c);
							skip = true;
							GameMap.addCherry();
							break;
						}
					}
					if (skip) {
						skip = false;
						break;
					}
				}
			cherryCounter = 0;
		}


	if (GameMap.GetDifficulty() == Easy && cherryCounter > Easycherry) {
		cherryCounter = 0;
	}
	if (GameMap.GetDifficulty() == Medium && cherryCounter > Medcherry) {
		cherryCounter = 0;
	}
	if (GameMap.GetDifficulty() == Hard && cherryCounter > Hardcherry) {
		cherryCounter = 0;
	}}
	cherryCounter++;
}

bool Cgame::PacmanToOct(std::shared_ptr<Cobject> &Pacman, bool &wall, bool &died, bool &Teleport) {

	if ((GameMap.GetObject((*Pacman).getX(),
						   (*Pacman).getY())->GetRage())) { // Control if the Octopus is in the rage mode or not
		wall = true;
		died = true;
		std::shared_ptr<Cobject> tmp = (GameMap.GetObject((*Pacman).getX(), (*Pacman).getY()));
		for (auto &i : GameMap.GetVector()) { // Set eaten octopus on the start position
			if (i->getX() == tmp->getX() && i->getY() == tmp->getY()) {

					GameMap.Swap(i->getX(), i->getY(), i->getStartX(), i->getStartY());
					i->getToStart();
					i->SetRage(false);

			}
		}
		GameMap.setObject((*Pacman).getX(), (*Pacman).getY(), *Pacman); // set Pacman where he started
		Cnothing c(GameMap.getXPac(), GameMap.getYPac());
		GameMap.setObject(GameMap.getXPac(), GameMap.getYPac(), c);
		GameMap.setXPac((*Pacman).getX());
		GameMap.setYPac((*Pacman).getY());

	} else {
		wall = true;
		GameMap.takeDemage();
		died = true;

		if (GameMap.getLives() == Dead) {
			return true;
		} else {
			Teleport = false;
			(*Pacman).setTeleported(false);
			Cmenu A;
			A.printLostMenu();
			for (auto &i : GameMap.GetVector()) { // Set all octopuses on the start position
				GameMap.Swap(i->getX(), i->getY(), i->getStartX(), i->getStartY());
				i->getToStart();
			}
			(*Pacman).moveBack();
			/*GameMap.Swap((*Pacman).getX(), (*Pacman).getY(), GameMap.getPacmanStartX(),
						 GameMap.getPacmanStartY());*/
			Cnothing C((*Pacman).getX(), (*Pacman).getY());
			GameMap.setObject((*Pacman).getX(), (*Pacman).getY(), C);
			(*Pacman).getToStart();
			GameMap.setXPac(GameMap.getPacmanStartX());
			GameMap.setYPac(GameMap.getPacmanStartY());
			GameMap.setObject(GameMap.getPacmanStartX(),GameMap.getPacmanStartY(), (*Pacman) );

		}
	}
	return false;
}

void Cgame::PacmanToTel(std::shared_ptr<Cobject> &Pacman, bool &wall, bool &died, bool &Teleport) {
	std::shared_ptr<Cobject> tmpTeleport;
	for (auto &i : GameMap.GetTeleports()) {
		if (i->getX() != (*Pacman).getX() || i->getY() != (*Pacman).getY()) { // find the other teleport
			tmpTeleport = i;
		}
	}
	(*Pacman).SetXY(tmpTeleport->getX(), tmpTeleport->getY());
	GameMap.setObject((*Pacman).getX(), (*Pacman).getY(), (*Pacman));
	(*Pacman).setTeleported(true);
	wall = true;
}