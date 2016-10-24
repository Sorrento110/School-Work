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
    for line in thefile:
#        print('ONE %s' % (line))
        linesplit = line.split()
#        print('TWO %s' % (linesplit))
        for item in linesplit:
#            print('THR %s' % (item))
            print('%s' % (item))

################################################################################
## main code starts here
##
main(sys.argv[1])
