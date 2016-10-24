GPP = g++ -O3 -Wall -std=c++0x

UTILS = ../../Utilities

A = Main.o
Q = Queue.o
O = OneVoter.o
R = MyRandom.o
S = Scanner.o
SL = ScanLine.o
U = Utils.o

Aprog: $A $Q $O $R $S $(SL) $U
	$(GPP) -o Aprog $A $Q $R $O $S $(SL) $U

Main.o: Main.h Main.cpp
	$(GPP) -c Main.cpp

Queue.o: Queue.h Queue.cpp
	$(GPP) -c Queue.cpp

OneVoter.o: OneVoter.h OneVoter.cpp
	$(GPP) -c OneVoter.cpp

MyRandom.o: MyRandom.h MyRandom.cpp
	$(GPP) -c MyRandom.cpp

Scanner.o: $(UTILS)/Scanner.h $(UTILS)/Scanner.cpp
	$(GPP) -c $(UTILS)/Scanner.cpp

ScanLine.o: $(UTILS)/ScanLine.h $(UTILS)/ScanLine.cpp
	$(GPP) -c $(UTILS)/ScanLine.cpp

Utils.o: $(UTILS)/Utils.h $(UTILS)/Utils.cpp
	$(GPP) -c $(UTILS)/Utils.cpp
