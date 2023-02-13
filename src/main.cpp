#include "Cgame.h"


int main() {
	Cmenu GameMenu;
	bool died =false ;
	while(true) {
		if (GameMenu.MainMenu(died)) {
			return 0;
		}
		Cgame Game(GameMenu.GetMap(), GameMenu.GetDiff());
		if(!Game.getValidGame()){
			std::cout << "Wrong map, try it again..Press any key to continue" << std::endl;
			getchar();
			died = false;
			continue;
		}
		died = Game.Play();
		}
}
