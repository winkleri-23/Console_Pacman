//
// Created by winkleri on 12.5.19.
//

#ifndef MYPAC_CMENU_H
#define MYPAC_CMENU_H
#define TOPTAB 4
#define TAB 3
#define ArayTab 2


#include <string>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstdio>
#include <sys/ioctl.h>
#include <chrono>
#include <thread>

/**
 * Class represents the menu, which is important part of every game.
 */

class Cmenu {
public:
	/**
	 * Constructor, just defines the arrays witch choices.
	 * Important but is not interesting.
	 */
	Cmenu() :mapchoice(0) , difficulty(0), mainMenuChoice(0) {


		Choices[0] = "Start Game";
		Choices[1] = "Choose map";
		Choices[2] = "Choose difficulty";
		Choices[3] = "Exit Game";


		MapChoices[0] = "Normal map";
		MapChoices[1] = "Alternative map";
		MapChoices[2] = "Crazy map";
		MapChoices[3] = "Your own map";

		DiffChoices[0] = "Easy";
		DiffChoices[1] = "Medium";
		DiffChoices[2] = "You gonna die and It´s gonna hurt";

		LostLiveMenu[0] = "You have lost your life!";
		LostLiveMenu[1] = "Press enter to continue";

	}

	/**
	 * Main menu of the game, you can choose here if you want to choose another map, or another difficulty atc..
	 * @param died If you died, the Main menu let you know that you died.
	 * @return
	 */

	bool MainMenu(bool died);
	/**
	 * Map menu.
	 * @return
	 */
	bool ChooseMapMenu();
	/**
	 * Difficulty menu.
	 * @return
	 */
	bool ChooseDiffMenu();


	/**
	 * Print Main menu.
	 * @param died
	 */
	void printMainMenu(bool died);
	/**
	 * Print map menu.
	 */
	void printMapMenu();
	/**
	 * Print difficulty menu.
	 */
	void printDiffMenu();
	void printLostMenu();
	void printWin(int score);


	int GetChar();
	int GetMap () const{return mapchoice;}
	int GetDiff() const{return difficulty;}

private:
	/**
	 * Represents which map was chosen.
	 */
	int mapchoice;
	/**
	 * Represents which difficulty was chosen.
	 */
	int difficulty;
	int mainMenuChoice;
	std::string Choices[4];
	std::string MapChoices[4];
	std::string DiffChoices[3];
	std::string LostLiveMenu[2];

};

#endif //MYPAC_CMENU_H
