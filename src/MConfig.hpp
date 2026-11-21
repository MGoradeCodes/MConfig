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

using std::vector;
using std::string;


class MParse{
public:
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

    void trim(std::string& str) {
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
                string item = "";
                if(word.find(",") != std::string::npos){
                    for(int c = 0; c < word.size(); c++){
                        while(word[c]!=','){
                            item += word[c];
                            c++;
                        }
                        trim(item);
                        arr.push_back(item);
                        item.clear();
                        c++;
                    }
                }
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
};