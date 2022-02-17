// wordleio.cpp
#include "wordleio.hpp"

void read_file(std::vector<std::string> &Ma, std::vector<std::string> &MO) {
    std::string str;

    std::ifstream ifs_Ma("Ma.txt");
    std::ifstream ifs_Oa("Oa.txt");
    if (ifs_Oa.fail() || ifs_Ma.fail()) {
        std::cerr << "Failed to open file." << std::endl;
        std::exit(1);
    }
    while (getline(ifs_Ma, str)) {
        Ma.push_back(str);
        MO.push_back(str);
    }
    while (getline(ifs_Oa, str)) {
        //Oa.push_back(str);
        MO.push_back(str);
    }
}

void colorInput(std::string word, char green[5], char orange[5], std::vector<char> &gray) {
    for(int i = 0; i < 5; i++) {
        green[i] = '0';
        orange[i] = '0';
    }
    gray.clear();
    int k = 0;
    std::string s;
    for(int j = 0; j < 10; ++j){
        std::cin >> s;
        for(auto c: s) {
            switch(c) {
                case '1':  // green
                    green[k] = word[k];
                    ++k;
                    break;
                case '2': // orange
                    orange[k] = word[k];
                    ++k;
                    break;
                case '3': // gray
                    gray.push_back(word[k++]);
                    break;
            }
            if(k == 5) break;
        }
        if(k == 5) break;
    }
    if(k != 5) std::exit(1);
}
