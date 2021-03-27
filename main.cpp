#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <bits/stdc++.h>

int main(){
    std::ifstream file("test.in");
    std::string line;

    while (getline(file,line)){
        std::istringstream liner(line);
        std::string word;
        liner>>word;
        std::cout <<  std::stoi(word)  << "|";
        liner>>word;
        std::cout << std::stoi(word) << std::endl;
    }
    return 0;
}
 