// search.cpp
#include "search.hpp"

void dist(std::string word, std::string ans, char green[5], char orange[5], std::vector<char> &gray) {
    for(int i = 0; i < 5; i++) {
        green[i] = '0';
        orange[i] = '0';
    }
    gray.clear();
    for(int i = 0; i < 5; i++) { // word
        if(ans[i] == word[i]) {
            green[i] = word[i];
            continue;
        }
    }
    for(int i = 0; i < 5; i++) {
        if(green[i] != '0') continue;
        bool found = false;
        for(int j = 0; j < 5; j++) { // ans
            if(green[j] != '0') continue;
            if(ans[j] == word[i]) {
                orange[i] = word[i];
                found = true;
                break;
            }
        }
        if (!found) {
            gray.push_back(word[i]);

        }
    }
}


void cand(char green[5], char orange[5], std::vector<char> gray, std::vector<std::string> &candidates) {
    std::vector<std::string> new_cands;
    new_cands.reserve(candidates.size());
    for(std::string ans : candidates) {
        bool is_candidate = true;
        for(int i = 0; i < 5; ++i) {
            // green
            if(ans[i] == green[i]) continue;
            if(green[i] != '0') {
                is_candidate = false;
                break;
            }

            for(char c : gray) {
                if(ans[i] == c) {
                    is_candidate = false;
                    break;
                }
            }
            if(!is_candidate) break;

            // orange
            if(ans[i] == orange[i]) {
                is_candidate = false;
                break;
            }

            if(orange[i] == '0') continue;
            bool found1 = false;
            for(int j = 0; j < 5; ++j) { // w
                if(green[j] != '0') continue;
                if(orange[i] == ans[j]) {
                    found1 = true;
                    break;
                }
            }
            if(!found1) {
                is_candidate = false;
                break;
            }
        }
        if(is_candidate) {
            new_cands.push_back(ans);
        }
    }
    candidates = new_cands;
}

std::string search(std::vector<std::string> candidates, std::vector<std::string> MO, bool blacklist[26], std::vector<std::string> input_words) {
    // search
    std::string iw_min = "";
    int cand_min = INT_MAX;
    int count = 0;
    int MO_size = MO.size();

    #ifdef _OPENMP
    #pragma omp parallel for
    #endif
    for(int i = 0; i < MO_size; i++) {
        std::string word = MO[i];
        ++count;
        bool not_used = true;
        for(char c : word) {
            if(c - 'a' >= 26) std::exit(2);
            if(blacklist[c - 'a']) {
                not_used = false;
                break;
            }
        }
        if(!not_used) continue;
        int cand_sum = 0;
        char green[5], orange[5];
        std::vector<char> gray;
        std::vector<std::string> nextcandidates;
        std::vector<std::string> words(input_words);
        words.push_back(word);
        for (auto ans: candidates) {
            if(word == ans) {
                ++cand_sum;
                continue;
            }
            nextcandidates = candidates;
            for (auto iw: words) {
                dist(iw, ans, green, orange, gray);
                cand(green, orange, gray, nextcandidates);
            }
            cand_sum += nextcandidates.size();
        }
        // print
        #ifdef _OPENMP
        #pragma omp critical
        #endif
        {
            std::cout << "\r" << count << " / " << MO_size;
            std::flush(std::cout);
            if (cand_sum < cand_min) {
                iw_min = word;
                cand_min = cand_sum;
                std::cout << "\r" << count << " / " << MO_size << ", average: " << cand_sum / double(candidates.size()) << ", word: " << word << std::endl;
            }
        }
    }

    std::cout << std::endl;
    return iw_min;
}

std::string search(std::vector<std::string> candidates, std::vector<std::string> MO, bool blacklist[26]) {
    std::vector<std::string> input_words;
    return search(candidates, MO, blacklist, input_words);
}
