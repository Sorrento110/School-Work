################################################################################
##
## Author/copyright: Duncan Buell
## Date: 6 February 2016
##
import sys
from collections import defaultdict
from nltk.util import ngrams

################################################################################
## Function to clean up the words to get rid of punctuation and to lowercase.
## And create a new list of the words after cleaning each one up.
def cleanTheWords(rawWords):
    cleanWords = []
    for rawWord in rawWords:
        word = rawWord.strip()
        word = word.lower()
        word = word.replace('.', '')
        word = word.replace(',', '')
        word = word.replace(';', '')
        word = word.replace(':', '')
        word = word.replace('!', '')
        word = word.replace('?', '')
        word = word.replace('"', '')
        word = word.replace("'", '')
        word = word.replace('(', '')
        word = word.replace(')', '')
        word = word.replace('_', '')
        cleanWords.append(word)

    return cleanWords

################################################################################
## Function create a dict of the freq of occurrence of each word
## and print that
def computeFreqs(words, stopwords):
    freqsGood = defaultdict(int)
    freqsStop = defaultdict(int)
    for word in words:
        if word in stopwords:
            freqsStop[word] += 1
        else:
            freqsGood[word] += 1

    return freqsGood, freqsStop

################################################################################
## Function to flip a freq dict and print in formatted fashion 
def printFlippedDict(label, freqDict, minimumFrequency):
    flippedlist = []
    for key, value in sorted(freqDict.items()):
        flippedlist.append([value, key])

#    print('THE %s FLIPPED LIST PRINTED IN RAW FORMAT IS' % (label))
#    print(flippedlist)
#    print()

    print('THE %s FLIPPED LIST PRINTED IN FORMATTED FASHION IS' % (label))
    print('(printing only those words and freqs that occur >= %d times' % \
               (minimumFrequency))
    for item in sorted(flippedlist):
        if item[0] >= minimumFrequency:
            print('%5d %-20s' % (item[0], item[1]))
    print()

################################################################################
## Function to read a file and split into words
def readFileAndSplit(filename):
    theFile = open(filename, encoding='utf-8')
    theText = theFile.read()
    rawWords = theText.split()
    theFile.close()
    return rawWords


################################################################################
################################################################################
################################################################################
## main code starts here
##

################################################################################
## Open the NLTK stopwords file, read that file, save it as a set of stopwords,
## and then close the file.
filename = 'dickens-tale.txt'
wordlist = readFileAndSplit(filename)
#print('THE WORD LIST IS')
#print(wordlist)
#print()

cleanWords = cleanTheWords(wordlist) 
#print(cleanWords)
#print(' '.join(cleanWords))
#for word in cleanWords:
#    print(word)
#print()
#sys.exit()

letterfreq = defaultdict(int)
fulltext = ' '.join(cleanWords)
fulltextsplit = list(fulltext)
for let in fulltextsplit:
   letterfreq[let] += 1

for let, freq in sorted(letterfreq.items()):
    print('%8d %s' % (freq, let))
#sys.exit()

thegrams = list(ngrams(cleanWords, 3))
#print(thegrams)
#print()

gramdict = defaultdict(int)
for gram in thegrams:
    gramconcat = " ".join(gram)
#    print(gramconcat)
    gramdict[gramconcat] += 1

#print(gramdict)
printFlippedDict('label', gramdict, 1)

