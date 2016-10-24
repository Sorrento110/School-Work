GPP = g++ -O3 -Wall -std=c++11

UTILS = ../../Utilities

A = main.o
G = gcdtest.o
R = myrandom.o
S = scanner.o
SL = scanline.o
U = utils.o

Aprog: $(A) $(G) $(R) $(S) $(SL) $(U)
	$(GPP) -o Aprog $(A) $(G) $(R) $(S) $(SL) $(U)

main.o: main.h main.cc
	$(GPP) -c main.cc

gcdtest.o: gcdtest.h gcdtest.cc
	$(GPP) -c gcdtest.cc

myrandom.o: myrandom.h myrandom.cc
	$(GPP) -c myrandom.cc

scanner.o: $(UTILS)/scanner.h $(UTILS)/scanner.cc
	$(GPP) -c $(UTILS)/scanner.cc

scanline.o: $(UTILS)/scanline.h $(UTILS)/scanline.cc
	$(GPP) -c $(UTILS)/scanline.cc

utils.o: $(UTILS)/utils.h $(UTILS)/utils.cc
	$(GPP) -c $(UTILS)/utils.cc
