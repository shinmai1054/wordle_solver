// main.cpp
#include "solve.hpp"

#ifdef _OPENMP
    #include <omp.h>
#endif

int main(int argc, char* argv[]) {
    #ifdef _OPENMP
    std::cout << "OpenMP : Enabled (Max # of threads = " << omp_get_max_threads() << ")" << std::endl;
    #else
    std::cout << "OpenMP : Disabled" << std::endl;
    #endif

    if(argc == 2){
        if(std::string(argv[1]) == "--solution") {
            searchOptimalSolution();
            return 0;
        }
    }

    solve("roate");
    return 0;
}
