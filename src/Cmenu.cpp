//
// Created by winkleri on 12.5.19.
//

#include "Cmenu.h"


int Cmenu::GetChar() { //StackOverflow
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

bool Cmenu::MainMenu(bool died) {

	int key;
	bool breakCycle = false;
	mainMenuChoice = 0;
	while(true) {
		system("clear");
		printMainMenu(died);
		died =false;
		key = GetChar();

		switch(key){
			case  119 : mainMenuChoice--;
			if(mainMenuChoice == -1){
				mainMenuChoice = 3;
			}
			break;
			case 115 : mainMenuChoice++;
			if(mainMenuChoice == 4){
				mainMenuChoice = 0;
			}
			break;
			case 10 : breakCycle = true;
				break;
			default:
				break;
		}
		if(breakCycle){
			break;
		}

	}

	switch (mainMenuChoice){
		case 0 : return false;
		case 1 : return ChooseMapMenu();
		case 2 : return ChooseDiffMenu();
		case 3: return true;
	}
	return false;
}

bool Cmenu::ChooseMapMenu() {
	int key;
	bool breakCycle = false;
	while(true) {
		system("clear");
		printMapMenu();
		key = GetChar();

		switch(key){
			case  119 : mapchoice--;
				if(mapchoice == -1){
					mapchoice = 3;
				}
				break;
			case 115 : mapchoice++;
				if(mapchoice == 4){
					mapchoice = 0;
				}
				break;
			case 10 : breakCycle = true;
				break;
			default:
				break;
		}
		if(breakCycle){
			break;
		}

	}

	return MainMenu(false);
}


bool Cmenu::ChooseDiffMenu() {
	int key;
	bool breakCycle = false;
	while(true) {
		system("clear");
		printDiffMenu();
		key = GetChar();

		switch(key){
			case  119 : difficulty--;
				if(difficulty == -1){
					difficulty= 2;
				}
				break;
			case 115 : difficulty++;
				if(difficulty == 3){
					difficulty = 0;
				}
				break;
			case 10 : breakCycle = true;
				break;
			default:
				break;
		}
		if(breakCycle){
			break;
		}

	}

	return MainMenu(false);
}



void Cmenu::printMapMenu()  {
	for(int i = 0; i < 4 ; i++){
		std::cout << std::endl;
	}
	int counter = 0;
	for(const auto & i: MapChoices){

		if(counter == mapchoice){
			for(int a = 0; a < ArayTab; a++){
				std::cout << "\t";
			}
			std::cout << "    --> ";
		}else{
			for(int a = 0; a < TAB; a++){
				std::cout << "\t";
			}
		}
		std::cout << i << std::endl;
		counter++;
		if(counter == 4){
			counter = 0 ;
		}
	}

}

void Cmenu::printMainMenu(bool died) {
	for(int i = 0; i < TOPTAB ; i++){
		std::cout << std::endl;
	}
	if(died){
		for(int a = 0; a < TAB; a++){
			std::cout << "\t";
		}
		std::cout << "You have died!!" << std::endl;
		using namespace std::this_thread;
		using namespace std::chrono;
		sleep_for(nanoseconds(100000));
		sleep_until(system_clock::now() + seconds(1));

	}

	system("clear");
	for(int i = 0; i < TOPTAB ; i++){
		std::cout << std::endl;
	}
	int counter = 0;
	for(const auto & i: Choices){

		if(counter == mainMenuChoice){
			for(int a = 0; a < ArayTab; a++){
				std::cout << "\t";
			}
			std::cout << "    --> ";
		}else{
			for(int a = 0; a < TAB; a++){
				std::cout << "\t";
			}
		}
		std::cout << i << std::endl;
		counter++;
		if(counter == 4){
			counter = 0 ;
		}
	}
}

void Cmenu::printDiffMenu() {
	for(int i = 0; i < TOPTAB ; i++){
		std::cout << std::endl;
	}
	int counter = 0;
	for(const auto & i: DiffChoices){

		if(counter == difficulty){
			for(int a = 0; a < ArayTab; a++){
				std::cout << "\t";
			}
			std::cout << "    --> ";
		}else{
			for(int a = 0; a < TAB; a++){
				std::cout << "\t";
			}
		}
		std::cout << i << std::endl;
		counter++;
		if(counter == 3){
			counter = 0 ;
		}
	}


}

void Cmenu::printLostMenu(){
	system("clear");
	for(int i = 0; i < TOPTAB ; i++){
		std::cout << std::endl;
	}
	int counter = 0;
	for(const auto & i: LostLiveMenu){

		if(counter == 1){
			for(int a = 0; a < TAB; a++){
				std::cout << "\t";
			}
		}else{
			for(int a = 0; a < TAB; a++){
				std::cout << "\t";
			}
		}
		std::cout << i << std::endl;
		counter++;
		if(counter == 2){
			counter = 0 ;
		}
	}
	int key =0;
	while(key !=10){key = GetChar();}


}

void Cmenu::printWin(int score) {
	system("clear");
	for(int i = 0; i < TOPTAB; i++){
		std::cout << std::endl;
	}

		for(int a = 0; a < TAB; a++){
			std::cout << "\t";
		}
		std::cout << "--->  WIN!  <----" << std::endl;
		for(int a = 0; a < TAB; a++){
			std::cout << "\t";
		}
		std::cout << "Your score: " << score <<std::endl;


		using namespace std::this_thread;
		using namespace std::chrono;
		sleep_for(nanoseconds(100000));
		sleep_until(system_clock::now() + seconds(1));

}





