//
// Created by winkleri on 12.5.19.
//

#ifndef MYPAC_CGAME_H
#define MYPAC_CGAME_H

#include "Cmap.h"
#include "Cmenu.h"
#include <map>
#include <queue>
#include <set>
#include <vector>

/**
 * Represents the game itself - everything happen here. It connects the map and the menu.
 */

class Cgame{
public:

	/**
	 * Constructor - receiving which map is going to be played and how difficult it is going to be.
	 * Also create the map and check if it is valid.
	 * @param maps
	 * @param Diff
	 */
	Cgame(int maps, int Diff) : GameMap(maps,Diff){validMap = GameMap.getValid();}

	/**
	 * Is everything OK?
	 * @return
	 */
	bool getValidGame() const {return validMap;}

	/**
	 * Evaluate the Pacman moves and his collision with other objects.
	 * @return
	 */
	bool PacmanCOllision();

	/**
	 * Evaluate the Octopus moves and their collisions with other objects.
	 * @return
	 */
	bool OctopusCollision();

	/**
	 * Start the game.
	 * @return
	 */
	bool Play ();
	/**
	 * Find the nearest Ghost to Pacman. Usually using when you need to start hunting him.
	 */
	void FindTheNearest();

	/**
	 * This function find the nearest path to some point using bfs. Useful for Octopuses.
	 * This is the function, which make me proud.
	 * @param Octopus
	 * @param x Xcordinates where you Start
	 * @param y	Ycordinates where you Start
	 * @param Xdest
	 * @param Ydest
	 * @return
	 */
	bool Hunter(std::shared_ptr<Cobject> &Octopus, int &x, int &y, int Xdest, int Ydest);

	bool NextObj(std::shared_ptr<Cobject> & Octopus,std::vector<std::pair<int, int>> & Possibilities);
	/**
	 * Find the possible moves for Octopus. It means, tries every possible direction and check which object is there.
	 * Every possible move is pushed to a vector.
	 * @param Possibilities Vector of possibilities.
	 * @param i iterator on the object.
	 * @param skip Just boolean which is used after in the function in some cases.
	 * @return
	 */
	bool FindPossibleMoves(std::vector<std::pair<int, int>> &Possibilities, std::shared_ptr <Cobject> & i, bool & skip );

	/**
	 * Really similar to previous function, but adjusted for bfs algorithm.
	 * @param Possibilities
	 * @param tmp
	 */
	void FindPossibleMovesBFS(	std::vector<std::pair<int, int>> & Possibilities,std::pair<int, int> & tmp);

	/**
	 * Call the AI algorithm a evaluete its results.
	 * @return
	 */
	bool OctopusMoving();
	//bool OctopusAndPacman(std::vector <std::shared_ptr <Cobject>>::iterator iter ,bool &wall, bool &died);
	/**
	 * Put Random cherry on the random place. Depends on the difficulty of the game.
	 * @param Diff
	 * @param cherryCounter
	 * @param skip
	 */
	void NewCherry(int Diff, int &  cherryCounter, bool & skip );

	/**
	 * Evaluate what happens when Pacman touch octopus.
	 * @param Pacman
	 * @return
	 */
	bool PacmanToOct(std::shared_ptr <Cobject> & Pacman, bool & wall, bool & died, bool &Teleport);
	/**
	 * Evaluate collision between Pacman and teleport.
	 * @param Pacman
	 * @param wall
	 * @param died
	 * @param Teleport
	 */
	void PacmanToTel(std::shared_ptr <Cobject> & Pacman, bool & wall, bool & died, bool &Teleport);
	/**
	 * Evaluate collision between Pacman and coin.
	 * @param Pacman
	 * @param wall
	 * @param died
	 * @param Teleport
	 * @return
	 */
	bool PacmanToCoin(std::shared_ptr <Cobject> & Pacman, bool & wall, bool & died, bool &Teleport);
	/**
	 * Evaluate collision between Pacman and Ragestarter.
	 * @param Pacman
	 * @param wall
	 * @param died
	 * @param Teleport
	 * @return
	 */
	void PacmanToKiller(std::shared_ptr <Cobject> & Pacman, bool & wall, bool & died, bool &Teleport);
	/**
	 * Evaluate collision between Pacman and cherry.
	 * @param Pacman
	 * @param wall
	 * @param died
	 * @param Teleport
	 */
	void PacmanToCherry(std::shared_ptr <Cobject> & Pacman, bool & wall, bool & died, bool &Teleport);

private:
	/**
	 * Game map.
	 */
	Cmap GameMap;
	/**
	 * Represents if the map is valid or not.
	 */
	bool validMap;
};


#endif //MYPAC_CGAME_H
