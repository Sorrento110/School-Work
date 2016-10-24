################################################################################
##
## Author/copyright: Duncan Buell
## Date: 21 August 2016
##
import sys
from collections import defaultdict

################################################################################
## compute and print the frequences of the letters
def main(filename):
    thefile = open(filename)
    freqdict = defaultdict(int)
    for line in thefile:
        print('ONE %s' % (line))
        linesplit = line.split()
        print('TWO %s' % (linesplit))
        linelist = list(linesplit)
        print('THR %s' % (linelist))
        for item in linelist:
            itemlist = list(item)
            print('FOU %s' % (itemlist))
            for itemitem in itemlist:
                freqdict[itemitem] += 1

    for key,value in sorted(freqdict.items()):
        print('%15s %6d' % (key, value))

################################################################################
## main code starts here
##
main(sys.argv[1])
