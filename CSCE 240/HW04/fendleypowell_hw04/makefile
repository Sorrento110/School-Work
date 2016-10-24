GPP = g++ -O3 -Wall

UTILS = ../../Utilities

A = Main.o
T = Traversal.o
N = Node.o
S = Scanner.o
SL = ScanLine.o
U = Utils.o

Aprog: $A $T $N $S $(SL) $U
	$(GPP) -o Aprog $A $T $N $S $(SL) $U

Main.o: Main.h Main.cpp
	$(GPP) -c Main.cpp

Traversal.o: Traversal.h Traversal.cpp
	$(GPP) -c -DEBUG Traversal.cpp

Node.o: Node.h Node.cpp
	$(GPP) -c Node.cpp

Scanner.o: $(UTILS)/Scanner.h $(UTILS)/Scanner.cpp
	$(GPP) -c $(UTILS)/Scanner.cpp

ScanLine.o: $(UTILS)/ScanLine.h $(UTILS)/ScanLine.cpp
	$(GPP) -c $(UTILS)/ScanLine.cpp

Utils.o: $(UTILS)/Utils.h $(UTILS)/Utils.cpp
	$(GPP) -c $(UTILS)/Utils.cpp
