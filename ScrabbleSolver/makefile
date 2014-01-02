all: scrabble clean

scrabble: ScrabbleMain.o PrefixTree.o MaxHeap.o ScrabbleLookup.o
	g++ ScrabbleMain.o PrefixTree.o MaxHeap.o ScrabbleLookup.o -o scrabble

ScrabbleMain.o: ScrabbleMain.cpp
	g++ -c ScrabbleMain.cpp

PrefixTree.o: PrefixTree.cpp
	g++ -c PrefixTree.cpp

MaxHeap.o: MaxHeap.cpp
	g++ -c MaxHeap.cpp

ScrabbleLookup.o: ScrabbleLookup.cpp
	g++ -c ScrabbleLookup.cpp

clean:
	rm -rf *.o *.cpp~ *.h~ makefile~ 
