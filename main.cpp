#include "markov.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
int main() {

    string testWords[] = {"the", "cat", "sat", "down"};
    std::cout << joinWords(testWords, 0, 2) << std::endl;
    std::cout << joinWords(testWords, 1, 3) << std::endl;


    return 0;
}