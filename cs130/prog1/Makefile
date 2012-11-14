prog1.exe: prog.o HashKey.o HashTable.o main.o Quash.o
	g++ prog.o HashKey.o HashTable.o main.o Quash.o -o prog1.exe

prog.o: prog.cpp
	g++ -c prog.cpp

HashKey.o: HashKey.cpp
	g++ -c HashKey.cpp

HashTable.o: HashTable.cpp
	g++ -c HashTable.cpp

main.o: main.cpp
	g++ -c main.cpp

Quash.o: Quash.cpp
	g++ -c Quash.cpp

