#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <climits>

#ifdef _OPENMP
    #include <omp.h>
#endif

#include "wordleio.hpp"
#include "search.hpp"

extern void solve();
extern void searchOptimalSolution();
