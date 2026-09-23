#include "markov.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {

    std::string testWords[] = {"the", "cat", "sat", "down"};
    std::cout << joinWords(testWords, 0, 2) << std::endl;
    std::cout << joinWords(testWords, 1, 3) << std::endl;

    std::string words[1000];
    int count = readWordsFromFile("test.txt", words, 1000);
    std::cout << "Read " << count << " words" << std::endl;
    
    for (int i = 0; i < 10 && i < count; i++) {
        std::cout << words[i] << std::endl;
    }


    return 0;
}