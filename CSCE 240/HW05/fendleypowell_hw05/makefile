GPP = g++ -O3 -Wall

UTILS = ../../Utilities

A = Main.o
I = Index.o
D = Dictionary.o
ST = Stoplist.o
SET = SetOfWords.o
O = Operators.o
S = Scanner.o
SL = ScanLine.o
U = Utils.o

Aprog: $A $I $D $(ST) $(SET) $S $(SL) $U
	$(GPP) -o Aprog $A $I $D $(ST) $(SET) $S $(SL) $U

Main.o: Main.h Main.cpp
	$(GPP) -c Main.cpp

Index.o: Index.h Index.cpp
	$(GPP) -c Index.cpp

Dictionary.o: Dictionary.h Dictionary.cpp
	$(GPP) -c Dictionary.cpp

Stoplist.o: Stoplist.h Stoplist.cpp
	$(GPP) -c Stoplist.cpp

SetOfWords.o: SetOfWords.h SetOfWords.cpp
	$(GPP) -c SetOfWords.cpp

Operators.o: Operators.h Operators.cpp
	$(GPP) -c Operators.cpp

Scanner.o: $(UTILS)/Scanner.h $(UTILS)/Scanner.cpp
	$(GPP) -c $(UTILS)/Scanner.cpp

ScanLine.o: $(UTILS)/ScanLine.h $(UTILS)/ScanLine.cpp
	$(GPP) -c $(UTILS)/ScanLine.cpp

Utils.o: $(UTILS)/Utils.h $(UTILS)/Utils.cpp
	$(GPP) -c $(UTILS)/Utils.cpp
