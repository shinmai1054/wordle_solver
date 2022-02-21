// solve.cpp
#include "solve.hpp"

void searchOptimalSolution() {
    std::vector<std::string> Ma, MO;
    std::vector<std::string> input_words;
    std::vector<std::string> candidates;
    bool used_char[26] = {};

    read_file(Ma, MO);

    for(int n = 0; n < 4; ++n) {
        std::cout << "----------------------------------------" << std::endl;

        for(auto dw: input_words) {
            for(auto c: dw) {
                if(c - 'a' >= 26) std::exit(2);
                used_char[c - 'a'] = true;
            }
        }

        std::string iw_min = search(Ma, MO, used_char, input_words);

        if(iw_min == "") {
            std::cout << "n=" << n << ", " << "not found" << std::endl;
            break;
        }
        std::cout << std::endl;
        std::cout << "n=" << n << " word=" << iw_min << std::endl;
        input_words.push_back(iw_min);
    }
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "result: ";
    for (auto word : input_words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
}



void solve(std::string default_word) {
    std::vector<std::string> input_words = {default_word};

    std::vector<std::string> Ma, MO;
    read_file(Ma, MO);

    std::vector<std::string> candidates(Ma);
    bool used_char[26] = {};

    for(int i = 0; i < 6; ++i) {
        char green[5], orange[5];
        std::vector<char> gray;

        std::string word = input_words.back();
        for(auto c: word) {
            if(c - 'a' >= 26) std::exit(2);
            used_char[c - 'a'] = true;
        }

        std::cout << "----------------------------------------" << std::endl;
        std::cout << "try '" << word << "'" << std::endl;
        std::cout << " green=1, orange=2, gray=3" << std::endl << ">> ";
        colorInput(word, green, orange, gray);

        //dist(word, "caulk", green, orange, gray); for(auto b: gray) blacklist[b-'a'] = true;
        cand(green, orange, gray, candidates);
        std::cout << std::endl << "candidates: " << candidates.size() << std::endl;
        if(candidates.size() <= 1) break;

        std::string iw_min = search(candidates, MO, used_char);

        if(iw_min == "") iw_min = candidates[0];
        input_words.push_back(iw_min);
    }
    std::cout << "----------------------------------------" << std::endl;
    switch(candidates.size()) {
        case 0:
            std::cout << "ans: not found" << std::endl;
            break;
        case 1:
            std::cout << "ans: " << candidates[0] << std::endl;
            break;
        default:
            std::cout << "failed solving" << std::endl;
            for(auto w: candidates) std::cout << w << std::endl;
            break;
    }
}
