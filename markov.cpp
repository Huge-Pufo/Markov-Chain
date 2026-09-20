#include <iostream>
#include <fstream>
#include <markov.h>

std::string joinWords(const std::string words[], int startIndex, int count) {

    std::string result = "";
    for (int i = 0; i < count; i++) {

        //add words to result
        result += words[startIndex + i];
        
        //if not last word add space
        if (i < count - 1) {
            result += " ";
        }
    }

    return result;
};

int readWordsFromFile(std::string filename, std::string words[], int maxWords) {
    std::ifstream file(filename);

    if (file.is_open()) {

        int counter = 0;
        while (counter < maxWords && file >> words[counter]) {
            counter += 1;
        }

        file.close();
        return counter;

    } 
    else {
        return -1;
    }
};

int buildMarkovChain(const std::string words[], int numWords, int order,
                    std::string prefixes[], std::string suffixes[],
                    int maxChainSize) {

    if ((order < 1 || order > 3) || (numWords <= order) || (maxChainSize <= 0)) {
        return 0;
    }

    int i = 0;
    int count = 0;
    while ((i < numWords - order) && (count < maxChainSize)) {
        std::string prefix = joinWords(words, i, order);
        prefixes[count] = prefix;

        std::string suffix = words[i + order];
        suffixes[count] = suffix;

        count += 1;
        i += 1;
    }

    return count;
};

std::string getRandomSuffix(const std::string prefixes[], const std::string suffixes[],
                            int chainSize, std::string currentPrefix) {
    
    int matchCount = 0;
    for (int i = 0; i < chainSize; i++) {
        if (prefixes[i] == currentPrefix) {
            matchCount += 1;
        }
    }
    
    if (matchCount == 0) {
        return "";
    }

    int pick = rand() % matchCount;

    int counterForMatches = 0;

    for (int i = 0; i < chainSize; i++) {
        if (prefixes[i] == currentPrefix) {
           counterForMatches += 1;
        }

        //Might be wrong check later
        if (counterForMatches - 1 == pick) {
            return suffixes[i];
        }
    }

    return "";
};


std::string getRandomPrefix(const std::string prefixes[], int chainSize) {
    if (chainSize <= 0) {
        return "";
    }

    int index = rand() % chainSize;
    return prefixes[index];

};


std::string generateText(const std::string prefixes[], const std::string suffixes[],
                         int chainSize, int order, int numWords) {

    if ((chainSize <= 0) || (numWords < order)) {
        return "";
    } 
    else if (order < 1 || order > 3) {
        return "";
    }

    std::string currentPrefix = getRandomPrefix(prefixes, chainSize);
    std::string resultString = currentPrefix;
    
    std::string currentWords[3]; // supports the validated orders 1, 2, and 3
    int wordIndex = 0;                                                                                                                                                                 
    std::string temp = "";
    //splits prefix into words in currentWords
    for (int i = 0; i < currentPrefix.length(); i++) {                                                                                                                                 
        if (currentPrefix[i] == ' ') {                                                                                                                                                 
            currentWords[wordIndex] = temp;                                                                                                                                            
            wordIndex++;                                                                                                                                                               
            temp = "";                 
        } else {                                                                                                                                                                       
            temp += currentPrefix[i];  
        }
    }

    currentWords[wordIndex] = temp; // don't forget the last word

    //picks random
    std::string newWord;
    for (int i = 0; i < numWords - order; i++) {
        newWord = getRandomSuffix(prefixes, suffixes, chainSize, currentPrefix);

        if (newWord == "") {
            break;
        }

        resultString += " " + newWord;
        
        //updates currentwordss to the new prefixes
        if (order == 1) {
            currentWords[0] = newWord;
        }
        else if (order == 2) {
            currentWords[0] = currentWords[1];
            currentWords[1] = newWord;
        }
        else {
            currentWords[0] = currentWords[1];
            currentWords[1] = currentWords[2];
            currentWords[2] = newWord;
        }

        currentPrefix = joinWords(currentWords, 0, order);
    }

    return resultString;
    
};

