#include <iostream>
#include <fstream>
#include <markov.h>

using namespace std;
string joinWords(const std::string words[], int startIndex, int count) {

    string result = "";
    for (int i = 0; i <= count - 1; i++) {

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
    fstream file(filename);

    if (file.is_open()) {

        int counter = 0;
        while (counter < maxWords && file >> words[counter]) {
            counter += 1;
        }

        file.close();
        return counter;

    } else {
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
    while ((i < numWords - order) && (i < maxChainSize)) {
        string prefix = joinWords(words, i, order);
        prefixes[count] = prefix;

        string suffix = words[i + order];
        suffixes[count] = suffix;

        count += 1;
        i += 1;
    }

};

