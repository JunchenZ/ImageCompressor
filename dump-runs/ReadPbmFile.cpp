//
//  ReadFile.cpp
//  ReadFile
//
//  Created by Westley Kirkham on 1/29/18.
//  Copyright © 2018 Westley Kirkham. All rights reserved.
//  https://stackoverflow.com/questions/11719538/how-to-use-stringstream-to-separate-comma-separated-strings

#include "pbmcompress-v1.h"
#include <tuple>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>

std::tuple<bool, int, int, std::vector<bool> *> read_pbm_file(std::string filename) {
    
    int width, height;
    std::vector<bool> *vec_bools = new std::vector<bool>();
    std::string expected_type = "P1";
    std::string file_type;
    bool check = false;
    
    std::ifstream my_stream (filename);
    if(!my_stream.good()) {
        auto tup_pbm_file = make_tuple( check, width, height, vec_bools);
        std::cout << "Error: File Not Found" << std::endl;
        return tup_pbm_file;
    }
    
    my_stream >> file_type;
    check = (file_type == expected_type);
    if(!check) {
        auto tup_pbm_file = make_tuple( check, width, height, vec_bools);
        std::cout << "Error: File Type. Expected: " << expected_type;
        std::cout << ". Received: " << file_type << std::endl;
        return tup_pbm_file;
    }
    
    my_stream >> width;
    my_stream >> height;
    char next_char = my_stream.get();
    while (my_stream.good()) {
        
        bool next_bool;
        
        if( next_char == '1') {
            next_bool = true;
        }
        else if (next_char == '0') {
            next_bool = false;
        }
        else if (next_char == '\n') {
            next_char = my_stream.get();
            continue;
        }
        else {
            check = false;
            std::cout << "Error: File Corrupted. " << next_char;
            std::cout << " is not an expected value from ";
            std::cout << filename << ". " << std::endl;
            break;
        }
        vec_bools -> push_back(next_bool);
        next_char = my_stream.get();
    }
    
    auto tup_pbm_file = make_tuple( check, width, height, vec_bools);
    return tup_pbm_file;
}

