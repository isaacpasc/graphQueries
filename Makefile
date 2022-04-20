gp: AdjacencyList.o Utilities.o HashTable.o DFS.o FloydWarshall.o main.o
	g++ AdjacencyList.o Utilities.o HashTable.o DFS.o FloydWarshall.o main.o -o gp

AdjacencyList.o: AdjacencyList.cpp AdjacencyList.h Utilities.cpp Utilities.h HashTable.cpp HashTable.h defns.h
	g++ -c AdjacencyList.cpp AdjacencyList.h Utilities.cpp Utilities.h HashTable.cpp HashTable.h defns.h

Utilities.o: Utilities.cpp Utilities.h defns.h
	g++ -c Utilities.cpp Utilities.h defns.h

HashTable.o: HashTable.cpp HashTable.h Utilities.cpp Utilities.h defns.h
	g++ -c HashTable.cpp HashTable.h Utilities.cpp Utilities.h defns.h defns.h

DFS.o: DFS.cpp DFS.h AdjacencyList.cpp AdjacencyList.h Utilities.cpp Utilities.h defns.h
	g++ -c DFS.cpp DFS.h AdjacencyList.cpp AdjacencyList.h Utilities.cpp Utilities.h defns.h

FloydWarshall.o: FloydWarshall.cpp FloydWarshall.h defns.h
	g++ -c FloydWarshall.cpp FloydWarshall.h defns.h

main.o: main.cpp defns.h Utilities.cpp Utilities.h AdjacencyList.cpp AdjacencyList.h DFS.cpp DFS.h HashTable.cpp HashTable.h FloydWarshall.cpp FloydWarshall.h
	g++ -c main.cpp defns.h Utilities.cpp Utilities.h AdjacencyList.cpp AdjacencyList.h DFS.cpp DFS.h HashTable.cpp HashTable.h FloydWarshall.cpp FloydWarshall.h
