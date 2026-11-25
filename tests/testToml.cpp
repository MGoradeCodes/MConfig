#include "../src/MConfig.hpp"
#include <iostream>

int main() {
    MConfig config;
    config.LoadFile("test.toml");
    std::unordered_map<string, string> data = config.fetchData();
    std::vector<string> parsed = config.returnParse();
    for(std::string s: parsed){
        std::cout << s << "\n";
    }
    return 0;
}