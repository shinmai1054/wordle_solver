// main.cpp
#include "search.hpp"
#include "solve.hpp"


int main() {
    //solve();
    searchOptimalSolution();
    return 0;
}


int main2() {
    std::vector<std::string> Ma, MO;
    read_file(Ma, MO);
    char green[5], orange[5];
    std::vector<char> gray;
    std::string s;
    while (true) {
        std::cin >> s;
        dist(s, "array", green, orange, gray);
        for(int i = 0; i < 5; ++i) std::cout << green[i] << std::endl;
        std::cout << std::endl;
        for(int i = 0; i < 5; ++i) std::cout << orange[i] << std::endl;
        std::cout << std::endl;
        for(auto b: gray) std::cout << b << std::endl;
        std::cout << std::endl;
    }
    return 0;
}
