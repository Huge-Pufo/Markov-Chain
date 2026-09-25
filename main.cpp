#include "markov.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {

    srand(time(0));
    int const MAX_WORDS  = 5000;

    std::string fileName;
    std::cout << "Enter input filename: ";
    std::getline(std::cin, fileName);

    int order;
    std::cout << "Enter order (1,2, or 3): ";
    std::cin >> order;

    int maxNumOfWords;
    std::cout << "Enter maximum number of words: ";
    std::cin >> maxNumOfWords;

    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Maximum number of words only accepts an integer as input.\n";
        std::cout << "Enter maximum number of words: ";
        std::cin >> maxNumOfWords;
    }
    while (maxNumOfWords < order) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Maximum number of words must be greater than or equal to 'order'.\n";
        std::cout << "Enter maximum number of words: ";
        std::cin >> maxNumOfWords;
    }


    std::string testWords[] = {"the", "cat", "sat", "down"};
    std::cout << joinWords(testWords, 0, 2) << std::endl;
    std::cout << joinWords(testWords, 1, 3) << std::endl;

    std::string words[1000];
    int count = readWordsFromFile("test.txt", words, 1000);
    std::cout << "Read " << count << " words" << std::endl;

    for (int i = 0; i < 10 && i < count; i++) {
        std::cout << words[i] << std::endl;
    }

    std::string prefixes[1000], suffixes[1000];
    int chainSize = buildMarkovChain(words, count, 1, prefixes, suffixes, 1000);

    for (int i = 0; i < 20 && i < chainSize; i++) {
        std::cout << "[" << prefixes[i] << "] -> [" << suffixes[i] << "]" << std::endl;
    }

    for (int i = 0; i < 10; i++) {
        std::cout << getRandomSuffix(prefixes, suffixes, chainSize, "the") << std::endl;
    }

    std::string output = generateText(prefixes, suffixes, chainSize, 1, 20);
    std::cout << output << std::endl;


    return 0;
}