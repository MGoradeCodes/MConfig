// Custom Config File Parser
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <string_view>
#include <cctype>
#include <algorithm>
#include <variant>
#include <unordered_map>
#include <stdexcept>
#include <type_traits>

using std::vector;
using std::string;

class MConfig{
public:

    template<typename T = std::string>
    T get(const std::string& s){
        auto it = result.find(s);
        if(it == result.end()){
            throw std::runtime_error("Error: cannot find key '" + s + "'");
        }
        return parseValue<T>(it->second);
    }
    template <typename T = std::string>
    std::vector<T> getVector(const std::string& key) const {
        auto it = result.find(key);
        if (it == result.end()) {
            throw std::runtime_error("Key not found: " + key);
        }
        return convertVector<T>(it->second);
    }


    std::unordered_map<string, string> result;
    void LoadFile(const char* filepath){
        std::ifstream file(filepath);
        if(!file){
            std::cerr << "File couldnt be loaded" << "\n";
            return;
        }
        std::ostringstream buffer;
        buffer << file.rdbuf();
        content = buffer.str();
        result = tokenizer(content);
        
    }
    std::unordered_map<string, string> fetchData(){
        return result;
    }

    std::vector<string> returnParse(){
        return parse;
    }


private:
    std::string content;
    vector<std::string> parse;
    std::vector<string> arr;
    std::unordered_map<string, string> tokenizer(string s) {
        string content = s;
        int size = content.size();
        parse.clear(); 
        std::unordered_map<string, string> config;
        string word = "";
        string item;
        int ObracketCount = std::count(content.begin(), content.end(), '{');
        int CBracketCount = std::count(content.begin(), content.end(), '}');
        if (ObracketCount != CBracketCount) {
            std::cerr << "Brackets are not in a proper syntax, recheck fool";
            return config;
        }

        if(size >=2 && content[size-2] == ','){
            std::cerr << "Bad formatting idiot" << "\n";
            return config;
        }

        for (int i = 0; i < size; i++) {

            if (std::isspace(static_cast<unsigned char>(content[i]))) {
                continue;
            }
            if (content[i] == '{' || content[i] == '}') {
                parse.push_back(std::string(1, content[i]));
            } 
            else if (content[i] == '"') {
                i++; 
                word = "";
                while (i < size && content[i] != '"') {
                    word += content[i];
                    i++;
                }
                parse.push_back(word); 
            } 
            else if (content[i] == ':') {
                parse.push_back(":"); 
            } 
            else if (content[i] == ',') {
            }
            else if (std::isalnum(static_cast<unsigned char>(content[i])) || content[i] == '-' || content[i] == '.') {
                word = "";
                while (i < size && (std::isalnum(static_cast<unsigned char>(content[i])) || content[i] == '-' || content[i] == '.')) {
                    word += content[i];
                    i++;
                }
                parse.push_back(word);
                i--; 
            }
            else if (content[i] == '[') {
                i++; 
                word = "";
                while (i < size && content[i] != ']') {
                    word += content[i];
                    i++;
                }
                parse.push_back(word);
            }

        }

        auto makeKey = [](const vector<string>& path, string s){
            string fullkey;
            for(auto& i : path){
                fullkey += i + ".";
            }
            return fullkey + s;

        };

        std::vector<string> path;

        for (int i = 0; i < parse.size(); i++) {
            //My Sub-branch
            if(parse[i] == ":" && i > 0 && i+1 < parse.size() && parse[i+1] == "{" ){
                path.push_back(parse[i-1]); // Push the first key on a sub-branch
                i++;
            }
            else if(parse[i] == ":" && i > 0 && i+1 < parse.size()){
                string fullkey = makeKey(path, parse[i-1]); //Make Key from the existing path, from earlier.
                config[fullkey] = parse[i+1]; // key + add value after the colon.
            }
            else if(parse[i] == "}" && !path.empty() ){
                path.pop_back();
            }
        }

        return config;
        
    } 
    void trim(std::string& str) const {
        const std::string whitespace = " \t\n\r\f\v";
        
        size_t start = str.find_first_not_of(whitespace);
        if (start == std::string::npos) {
            str.clear();
            return;
        }
        
        size_t end = str.find_last_not_of(whitespace);
        
        str.erase(end + 1);
        str.erase(0, start);
    }

    template <typename T>
    T parseValue(const std::string& s) const{
        if constexpr (std::is_same_v<T, std::string>){
            return s;
        } else {
            std::stringstream ss(s);
            T val;
            if (!(ss >> val) || !(ss >> std::ws).eof()) {
                throw std::invalid_argument("Cannot convert : " + s);
            }
            return val;
        }
    }

    template <typename T = std::string>
    std::vector<T> convertVector(const std::string& word) const {
        std::vector<T> arr; // Local vector so old results don't accumulate
        if (word.empty()) return arr;

        std::stringstream ss(word);
        std::string item;
        while (std::getline(ss, item, ',')) {
            trim(item);
            if (!item.empty()) {
                arr.push_back(parseValue<T>(item));
            }
        }
        return arr;
    }
    
    
};