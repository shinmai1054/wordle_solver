#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <climits>

#ifdef _OPENMP
    #include <omp.h>
#endif

extern void dist(std::string word, std::string ans, char green[5], char orange[5], std::vector<char> &gray);
extern void cand(char green[5], char orange[5], std::vector<char> gray, std::vector<std::string> &candidates);
extern std::string search(std::vector<std::string> candidates, std::vector<std::string> MO, bool blacklist[26]);


