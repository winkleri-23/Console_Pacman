#MAKEFILE
GG=g++ -std=c++11 -Wall -pedantic -g
OBJ=main.o Cmap.o Ccoin.o Ccherry.o CMoveable.o Coctopus.o CPacman.o Cwall.o Cmenu.o Cgame.o winkleri
DOC=doc

all: compile run doc

run: 
	./winkleri

compile: main.o Cmap.o Cwall.o Ccoin.o Ccherry.o CMoveable.o CPacman.o Coctopus.o Cmenu.o Cgame.o
	g++ -g -o winkleri Cmap.o main.o Cwall.o Ccoin.o Ccherry.o CMoveable.o CPacman.o Coctopus.o Cmenu.o Cgame.o

clean:
	rm -r $(OBJ)
	rm -rf $(DOC)

doc: src/main.cpp src/Ccherry.h src/Ccoin.h src/Cgame.h src/Ckiller.h src/Cmap.h src/Cmenu.h src/CMoveable.h src/Cnothing.h src/Coctopus.h src/CPacman.h src/Cwall.h 
	doxygen Doxyfile

Ccherry.o: src/Ccherry.cpp src/Ccherry.h src/Cobject.h
	$(GG) -c src/Ccherry.cpp

Cgame.o: src/Cgame.cpp src/Cgame.h src/Cmap.h src/Cobject.h src/Cwall.h src/Ccoin.h src/Ccherry.h src/CMoveable.h src/CPacman.h src/Coctopus.h src/Cnothing.h src/Cmenu.h src/Cteleport.h
	$(GG) -c src/Cgame.cpp


Ccoin.o: src/Ccoin.cpp src/Ccoin.h src/Cobject.h
	$(GG) -c src/Ccoin.cpp

Cmap.o: src/Cmap.cpp src/Cmap.h src/Cobject.h src/Cwall.h src/Ccoin.h src/Ccherry.h src/CMoveable.h src/CPacman.h src/Coctopus.h src/Cnothing.h src/Ckiller.h src/Cteleport.h
	$(GG) -c src/Cmap.cpp 

CMoveable.o: src/CMoveable.cpp src/CMoveable.h src/Cobject.h src/Ckiller.h
	$(GG) -c src/CMoveable.cpp

Coctopus.o: src/Coctopus.cpp src/Coctopus.h src/CMoveable.h src/Cobject.h
	$(GG) -c src/Coctopus.cpp

CPacman.o: src/CPacman.cpp src/CPacman.h src/CMoveable.h src/Cobject.h src/Ckiller.h
	$(GG) -c src/CPacman.cpp

Cwall.o: src/Cwall.cpp src/Cwall.h src/Cobject.h
	$(GG) -c src/Cwall.cpp

Cmenu.o: src/Cmenu.cpp src/Cmenu.h 
	$(GG) -c src/Cmenu.cpp

main.o: src/main.cpp src/Cmap.h src/Cobject.h src/Cmenu.h src/Cwall.h src/Ccoin.h src/Ccherry.h src/CPacman.h src/Coctopus.h src/Cnothing.h src/Cmenu.h src/Cgame.h src/Cteleport.h
	$(GG) -c  src/main.cpp 


