P1.out : Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o
	g++ -g -o P1.out Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o

Project1.o : Project1.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ -g -c Project1.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -g -c SetLimits.cpp

LexicalAnalyzer.o : LexicalAnalyzer.cpp LexicalAnalyzer.h
	g++ -g -c LexicalAnalyzer.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h
	g++ -g -c SyntacticalAnalyzer.cpp

clean : 
	rm *.o P1.out *.gch

submit : Project1.cpp LexicalAnalyzer.h LexicalAnalyzer.cpp SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp makefile README.txt
	rm -rf submissionIDP1
	mkdir submissionIDP1
	cp Project1.cpp submissionIDP1
	cp LexicalAnalyzer.h submissionIDP1
	cp LexicalAnalyzer.cpp submissionIDP1
	cp SyntacticalAnalyzer.h submissionIDP1
	cp SyntacticalAnalyzer.cpp submissionIDP1
	cp makefile submissionIDP1
	cp README.txt submissionIDP1
	tar cfvz submissionIDP1.tgz submissionIDP1
	cp submissionIDP1.tgz ~tiawatts/cs460drop
