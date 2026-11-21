#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../src/MConfig.hpp"

void runTests() {
    MParse helper;
    helper.LoadFile("test.json");

    std::unordered_map<std::string, std::string> data = helper.fetchData();
    std::vector<std::string> parsedData = helper.returnParse();

    // Verify file loaded and tokens were parsed
    assert(!parsedData.empty() && "Token list is empty — ensure you run from the tests/ folder");
    assert(!data.empty() && "Parsed map is empty");

    // Verify expected keys exist
    assert(data.find("Name") != data.end());
    assert(data.find("Gender") != data.end());
    assert(data.find("Employed") != data.end());
    assert(data.find("Address.Street") != data.end());
    assert(data.find("Address.Building") != data.end());

    // Print parsed values
    std::cout << "Name is: " << data["Name"] << "\n";
    std::cout << "Gender: " << data["Gender"] << "\n";
    std::cout << "Employed?: " << data["Employed"] << "\n";
    std::cout << "Address: Street: " << data["Address.Street"] << "\n";
    std::cout << "Building: " << data["Address.Building"] << "\n";
    std::cout << "Friends: " << typeid(data["Friends"]).name() << "\n";
    
}

int main() {
    std::cout << "Running MParse tests...\n\n";
    runTests();
    std::cout << "\n[PASS] All checks passed!\n";
    return 0;
}


