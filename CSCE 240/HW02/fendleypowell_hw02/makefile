GPP = g++ -O3 -Wall

UTILS = ../../Utilities

A = Main.o
T = TrapezoidMethod.o
F = Function.o
S = Scanner.o
SL = ScanLine.o
U = Utils.o

Aprog: $A $T $F $S $(SL) $U
	$(GPP) -o Aprog $A $T $F $S $(SL) $U

Main.o: Main.h Main.cpp
	$(GPP) -c Main.cpp

TrapezoidMethod.o: TrapezoidMethod.h TrapezoidMethod.cpp
	$(GPP) -c TrapezoidMethod.cpp

Function.o: Function.h Function.cpp
	$(GPP) -c Function.cpp

Scanner.o: $(UTILS)/Scanner.h $(UTILS)/Scanner.cpp
	$(GPP) -c $(UTILS)/Scanner.cpp

ScanLine.o: $(UTILS)/ScanLine.h $(UTILS)/ScanLine.cpp
	$(GPP) -c $(UTILS)/ScanLine.cpp

Utils.o: $(UTILS)/Utils.h $(UTILS)/Utils.cpp
	$(GPP) -c $(UTILS)/Utils.cpp
