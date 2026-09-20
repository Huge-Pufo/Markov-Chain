#include <string>

#ifndef MARKOV_H
#define MARKOV_H

std::string joinWords(const std::string words[], int startIndex, int count);

int readWordsFromFile(std::string filename, std::string words[], int maxWords);

int buildMarkovChain(const std::string words[], int numWords, int order,
                     std::string prefixes[], std::string suffixes[],
                     int maxChainSize);

std::string getRandomSuffix(const std::string prefixes[], const std::string suffixes[],
                            int chainSize, std::string currentPrefix);

std::string getRandomPrefix(const std::string prefixes[], int chainSize);

std::string generateText(const std::string prefixes[], const std::string suffixes[],
                         int chainSize, int order, int numWords);


#endif