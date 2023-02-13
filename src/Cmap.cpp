#include "Cmap.h"
#define Wall '#'
#define coin '.'
#define cherry 'c'
#define pacman 'P'
#define octopus 'X'
#define killer 'K'
#define nothing ' '
#define teleport 'T'



Cmap::Cmap(int map, int difficulty) : lives(3), score(0), Coincounter(0), difficulty(difficulty), cherryCounter(0)	, Octopuscounter(0) {
	int NumberofLines = 0;
	int lenghtofLine = 0;
	std::string PathToMap;
	Valid = true;
	if (!ValidMap(map, PathToMap)) {
		Valid = false;
	}
	if (Valid) {
		std::string Line;
		FindNumberOfLines(NumberofLines, lenghtofLine, map, PathToMap);
		CharMap = new char *[NumberofLines];
		for (int i = 0; i < NumberofLines; ++i) {
			CharMap[i] = new char[lenghtofLine];
		}
		std::ifstream MyMap;
		switch (map) {
			case 0 :
				MyMap.open("examples/EasyMap");
				break;
			case 1 :
				MyMap.open("examples/AlternativeMap");
				break;
			case 2:
				MyMap.open("examples/CrazyMap");
				break;
			case 3:
				MyMap.open(PathToMap);
				break;
		}
		length = lenghtofLine;
		lines = NumberofLines;
		SetTheCharArr(MyMap);
		MyMap.close();
		ObjectMap = new std::shared_ptr<Cobject> *[NumberofLines];
		for (int i = 0; i < NumberofLines; ++i) {
			ObjectMap[i] = new std::shared_ptr<Cobject>[lenghtofLine];
		}
		SetCobjectMap();
	}
}

void Cmap::printArray() const {
	system("clear");
	for (int i = 0; i < TOPTAB; i++) {
		std::cout << std::endl;
	}
	for (int i = 0; i < lines; i++) {
		for (int a = 0; a < TAB ; a++) {
			std::cout << "\t";
		}
		for (int a = 0; a < length; a++) {
			std::cout << ObjectMap[i][a]->getLetter();
			if (a == length - 1) {
				std::cout << std::endl;
			}
		}
	}

	for (int a = 0; a < TAB ; a++) {
		std::cout << "\t";
	}
	std::cout << "lives: "<< lives << " ";
	for(int i = 0 ; i < TAB; i++){
		std::cout << "|" ;
	}
	std::cout << " Score " << score << " ||| coins: " << Coincounter <<std::endl;
}

Cmap::~Cmap() {
	if(Valid) {
		for (int i = 0; i < lines; i++) {
			delete[] CharMap[i];
		}
		delete[] CharMap;

		for (int i = 0; i < lines; i++) {
			delete[] ObjectMap[i];
		}
		delete[] ObjectMap;
	}
}



void Cmap::FindNumberOfLines(int &NumberofLines, int &lenghtofLine, int map, std::string & PathToMap) {


	std::ifstream Lines;
	switch (map) {
		case 0 :
			Lines.open("examples/EasyMap");
			break;
		case 1 :
			Lines.open("examples/AlternativeMap");
			break;
		case 2:
			Lines.open("examples/CrazyMap");
			break;
		case 3:
			Lines.open(PathToMap);
	}


	std::string Line;
	if (Lines.fail()) {
		std::cout << "wtf" << std::endl;
	}

	while (getline(Lines, Line)) {
		NumberofLines++;
		if (NumberofLines == 1) {
			lenghtofLine = Line.length();
		}
	}
	Lines.close();
}


void Cmap::SetTheCharArr(std::ifstream &MyMap) {
	char tmp;
	int counterChar = 0;
	int counterLines = 0;
	while (MyMap.get(tmp)) {
		if (tmp != '\n') {
			CharMap[counterLines][counterChar] = tmp;
			counterChar++;
		} else {
			counterChar = 0;
			counterLines++;
		}
	}
}

void Cmap::SetCobjectMap() {

	for (int i = 0; i < lines; i++) {
		for (int a = 0; a < length; a++) {
			if (CharMap[i][a] == Wall) {
				Cwall s(i,a);
				ObjectMap[i][a] = s.clone();
			}
			if (CharMap[i][a] == coin) {
				Coincounter++;
				Ccoin s(i,a);
				ObjectMap[i][a] = s.clone();
			}

			if (CharMap[i][a] == cherry) {
				cherryCounter++;
				Ccherry s(i, a);
				ObjectMap[i][a] = s.clone();
			}

			if (CharMap[i][a] == nothing) {
				Cnothing s(i, a);
				ObjectMap[i][a] = s.clone();
			}

			if(CharMap[i][a] == killer){
				Ckiller s(i,a);
				ObjectMap[i][a]= s.clone();
			}

			if (CharMap[i][a] == pacman) {
				CPacman Pacman(i,a, 3);
				XPacman = i;
				YPacman = a;
				XPacmanStart = i;
				YPacmanStart = a;
				ObjectMap[i][a] = Pacman.clone();
			}

			if (CharMap[i][a] == octopus) {
				Octopuscounter++;
				Coctopus s(i,a,0);
				ObjectMap[i][a] = s.clone();
				Ccoin C(i,a);
				Octopusses.emplace_back(ObjectMap[i][a]->clone());
			}

			if(CharMap[i][a] == teleport){
				Cteleport s(i,a);
				ObjectMap[i][a] = s.clone();
				teleports.emplace_back(ObjectMap[i][a]->clone());
			}
		}
	}
	bool found = false;
	if(difficulty == 1){
		for(int i = 0; i < lines; i++){
			for(int j = 0; j < length;j++ ){
				if(ObjectMap[i][j]->isCoin()){
					Coctopus newOct(i,j,0);
					setObject(i,j, newOct );
					Coincounter--;
					Octopusses.emplace_back(ObjectMap[i][j]->clone());
					found = true;
					break;
				}
			}
			if(found){break;}
		}
	}
}

void Cmap::ReplacingObject(int Xobj, int Yobj, int Obj){
	if(Obj == 0){
		Cnothing c (Xobj, Yobj);
		ObjectMap[Xobj][Yobj] = c.clone();
	}
	if(Obj == 1){
		Ccoin c(Xobj, Yobj);
		ObjectMap[Xobj][Yobj] = c.clone();
	}
	if(Obj == 2){
		Ccherry c (Xobj, Yobj);
		ObjectMap[Xobj][Yobj] = c.clone();
	}
	if(Obj == 3){
		Ckiller c(Xobj, Yobj);
		ObjectMap[Xobj][Yobj] = c.clone();
	}

}

bool Cmap::ValidMap(int map, std::string & PathToMap) {
	std::ifstream Lines;

	int NumberofLines=0;
	unsigned int lenghtofLine =0;
	switch (map) {
		case 0 :
			Lines.open("examples/EasyMap");
			break;
		case 1 :
			Lines.open("examples/AlternativeMap");
			break;
		case 2:
			Lines.open("examples/CrazyMap");
			break;
		case 3:
			std::cout << "Zadejte cestu ke svoji mape:" << std::endl;
			std::cin >> PathToMap;
			getchar();
			Lines.open(PathToMap);
	}
	if(!Lines.is_open()){
		return false;
	}

	if (Lines.fail()) {
		return false;
	}
	std::string Line;
	while (getline(Lines, Line)) {
		NumberofLines++;
		if (NumberofLines == 1) {
			lenghtofLine = Line.length();
		}else{
			if(lenghtofLine != Line.length()){
				return false;
			}
		}
	}
	Lines.clear();
	Lines.seekg(0, std::ios::beg);
	int Pacman = 0;
	bool Octopus = false;
	bool Coin = false;
	char tmp;
	int teleports = 0;
	int lines = 1;
	size_t charCounter = 0;
	if(NumberofLines < 2 || lenghtofLine < 2){
		return false;
	}
	while (Lines.get(tmp)) {
		if(lines == 1){
			if(tmp != Wall && tmp != '\n'){
				return false;
			}
		}

		if(lines == NumberofLines){
			if(tmp != Wall && tmp != '\n'){
				return false;
			}
		}

		if(charCounter == 0){
			if(tmp != Wall){
				return false;
			}
		}

		if(charCounter == lenghtofLine - 1 ){
			if(tmp != Wall){
				return false;
			}
		}

		if(tmp == teleport){
			teleports++;
		}
		if(tmp == Wall){
			Octopus = true;
		}
		if(tmp == pacman){
			Pacman++;
		}
		if(tmp == coin){
			Coin = true;
		}

		if(tmp != Wall && tmp != cherry && tmp != coin && tmp != pacman && tmp != octopus && tmp != nothing && tmp != '\n' && tmp != killer && tmp != teleport){
			Lines.close();
			return false;
		}
		charCounter++;
		if(tmp == '\n'){
			charCounter = 0;
			lines++;
		}
	}
	if(teleports != 0 && teleports != 2){
		return false;
	}

	if(!Octopus || Pacman != 1 || !Coin){
		return false;
	}
	Lines.close();
	return true;
}
