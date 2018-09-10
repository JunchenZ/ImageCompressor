//
//  ReadChFile.cpp
//  ReadFile
//
//  Created by Westley Kirkham on 1/30/18.
//  Copyright © 2018 Westley Kirkham. All rights reserved.
//

#include "pbmcompress-v1.h"
#include <tuple>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>

std::tuple<bool, int, int, std::vector<uint8_t> *> read_ch_file(std::string filename) {
    
    int width = 0, height = 0;
    std::vector<uint8_t> *vec_uint = new std::vector<uint8_t>();
    char file_type[2];
    bool check = false;
    
    std::ifstream my_stream (filename);
    if(!my_stream.good()) {
        auto tup_ch_file = make_tuple( check, width, height, vec_uint);
        std::cout << "Error: File Not Found" << std::endl;
        return tup_ch_file;
    }
    
    my_stream.read(file_type, 2);
    check = (file_type[0] == 'c') && (file_type[1] == 'h');
    if(!check) {
        auto tup_ch_file = make_tuple( check, width, height, vec_uint);
        std::cout << "Error: File Type. Expected: ch";
        std::cout << ". Received: " << file_type << std::endl;
        return tup_ch_file;
    }
    
    char num_buff[4];
    my_stream.read(num_buff, 4);
    width = (uint8_t) num_buff[3] << 24 | (uint8_t) num_buff[2] << 16 |
    (uint8_t) num_buff[1] << 8 | (uint8_t) num_buff[0];
    
    my_stream.read(num_buff, 4);
    height = (uint8_t) num_buff[3] << 24 | (uint8_t) num_buff[2] << 16 |
    (uint8_t) num_buff[1] << 8 | (uint8_t) num_buff[0];
    
    uint8_t next_byte = my_stream.get();
    while (my_stream.good()) {
        
        vec_uint -> push_back(next_byte);
        next_byte = my_stream.get();
    }
    
    auto tup_ch_file = make_tuple( check, width, height, vec_uint);
    return tup_ch_file;
}
