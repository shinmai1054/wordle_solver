#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <climits>


extern void dist(std::string word, std::string ans, char green[5], char orange[5], std::vector<char> &gray);
extern void cand(char green[5], char orange[5], std::vector<char> gray, std::vector<std::string> &candidates);
extern std::string search(std::vector<std::string> candidates, std::vector<std::string> MO, bool blacklist[26], std::vector<std::string> input_words);
extern std::string search(std::vector<std::string> candidates, std::vector<std::string> MO, bool blacklist[26]);


