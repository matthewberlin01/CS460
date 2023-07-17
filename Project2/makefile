P2.out : Project2.o dataArrays.o LexicalAnalyzer.o SyntacticalAnalyzer.o
	g++ -g -o P2.out Project2.o dataArrays.o LexicalAnalyzer.o SyntacticalAnalyzer.o

Project2.o : Project2.cpp SyntacticalAnalyzer.h
	g++ -g -c Project2.cpp

dataArrays.o : dataArrays.cpp
	g++ -g -c dataArrays.cpp

LexicalAnalyzer.o : LexicalAnalyzer.cpp LexicalAnalyzer.h
	g++ -g -c LexicalAnalyzer.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h
	g++ -g -c SyntacticalAnalyzer.cpp

clean : 
	rm *.o P2.out *.gch

submit : Project2.cpp dataArrays.cpp LexicalAnalyzer.h LexicalAnalyzer.cpp SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp makefile README.txt
	rm -rf berlinMP2
	mkdir berlinMP2
	cp Project2.cpp berlinMP2
	cp dataArrays.cpp berlinMP2
	cp LexicalAnalyzer.h berlinMP2
	cp LexicalAnalyzer.cpp berlinMP2
	cp SyntacticalAnalyzer.h berlinMP2
	cp SyntacticalAnalyzer.cpp berlinMP2
	cp makefile berlinMP2
	cp README.txt berlinMP2
	tar cfvz berlinMP2.tgz berlinMP2
	cp berlinMP2.tgz ~tiawatts/cs460drop
