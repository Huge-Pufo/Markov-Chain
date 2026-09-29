#include "markov.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>

int main() {

    srand(time(0));
    int const MAX_WORDS  = 5000;

    std::string words[MAX_WORDS];
    std::string prefixes[MAX_WORDS];
    std::string suffixes[MAX_WORDS];
    
    std::string fileName;
    int count;
    while (true) {
        std::cout << "Enter the file name: ";
        std::getline(std::cin, fileName);
        count = readWordsFromFile(fileName, words, MAX_WORDS);

        if (count != -1) {
            break;
        }
        else {
            std::cout << "Unable to open file\n";
            std::cout << "Double check file name or extension.\n";
        }
    }


    int maxNumOfWords;
    while (true) {
        std::cout << "Enter maximum number of words: ";
        //claude helped me here
        if (std::cin >> maxNumOfWords) {
            if (std::cin.peek() == '\n') {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            else {
                std::cout << "Please enter only integers.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        else {
            std::cout << "Please enter only integers.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    int order;
    while (true) {
        std::cout << "Enter the order (1, 2 or 3): ";
        if (std::cin >> order) {
            if (std::cin.peek() == '\n') {
                if (order < 1 || order > 3) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Enter a number between 1 and 3\n";
                }
                else if (order > maxNumOfWords) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "order must not exceed the maximum number of words\n";
                }
                else if (order >= count) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "At least order + 1 training words are needed\n";
                } 
                else {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
            }
            else {
                std::cout << "Please enter only integers.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        else {
            std::cout << "Please enter only integers.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    int chainSize = buildMarkovChain(words, maxNumOfWords, order, prefixes, suffixes, MAX_WORDS);
    if (count == 5000) {
        std::cout << "at most " << MAX_WORDS << " input words were used and additional words, if any, were ignored.\n";
    }

    std::string resultString = generateText(prefixes, suffixes, chainSize, order, maxNumOfWords);

    std::cout << resultString;

    /* INITIAL TESTING

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

    */


    return 0;

}