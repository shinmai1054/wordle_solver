// solve.cpp
#include "solve.hpp"

void searchOptimalSolution() {
    std::vector<std::string> Ma, MO;
    std::vector<std::string> default_words;
    std::vector<std::string> candidates;

    #ifdef _OPENMP
    std::cout << "OpenMP : Enabled (Max # of threads = " << omp_get_max_threads() << ")" << std::endl;
    #else
    std::cout << "OpenMP : Disabled" << std::endl;
    #endif

    read_file(Ma, MO);

    for(int n = 0; n < 4; ++n) {
        std::cout << "----------------------------------------" << std::endl;

        std::string iw_min = "";
        int cand_min = INT_MAX;
        int count = 0;

        bool used_char[26] = {};
        for(auto dw: default_words) {
            for(auto c: dw) {
                if(c - 'a' >= 26) std::exit(2);
                used_char[c - 'a'] = true;
            }
        }
        #ifdef _OPENMP
        #pragma omp parallel for
        #endif
        for (auto word: MO) {
            bool not_used = true;
            for(char c : word) {
                if(c - 'a' >= 26) std::exit(2);
                if(used_char[c - 'a']) {
                    not_used = false;
                    break;
                }
            }
            if(!not_used) continue;

            int cand_sum = 0;
            char green[5], orange[5];
            std::vector<char> gray;
            std::vector<std::string> candidates;
            std::vector<std::string> input_words(default_words);
            input_words.push_back(word);

            for (auto ans: Ma) {
                if(word == ans) {
                    ++cand_sum;
                    continue;
                }
                candidates = Ma;
                for (auto iw: input_words) {
                    dist(iw, ans, green, orange, gray);
                    cand(green, orange, gray, candidates);
                }
                cand_sum += candidates.size();
            }
            #ifdef _OPENMP
            #pragma omp critical
            #endif
            {
            std::cout << "\r" << count;
            std::flush(std::cout);

            if (cand_sum < cand_min) {
                iw_min = word;
                cand_min = cand_sum;
                std::cout << "\r" << n << ", " << count << ", average: " << cand_sum / double(Ma.size()) << ", word: " << word << std::endl;
            }
            }
            count++;
        }
        if(iw_min == "") {
            std::cout << "n=" << n << ", " << "not found" << std::endl;
            break;
        }
        std::cout << std::endl;
        std::cout << "n=" << n << " word=" << iw_min << std::endl;
        default_words.push_back(iw_min);
    }
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "result: ";
    for (auto word : default_words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
}



void solve() {
    std::vector<std::string> input_words = {"roate"};

    #ifdef _OPENMP
    std::cout << "OpenMP : Enabled (Max # of threads = " << omp_get_max_threads() << ")" << std::endl;
    #else
    std::cout << "OpenMP : Disabled" << std::endl;
    #endif

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

        input_words.push_back(search(candidates, MO, used_char));
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
