//
//  unhuff.cpp
//  ImageCompress
//
//  Created by Chaofan Su on 1/31/18.
//  Copyright © 2018 su. All rights reserved.
//
//  Modified by Junchen Zhang on latter assignment
//

#include "huff.h"
#include <stdio.h>
#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include <assert.h>
#include <map>
#include "pbmcompress-v1.h"

bool debug;

//unhuff version 1
std::tuple<bool, int, int, std::vector<uint8_t> *> unhuff(std::string filename) {
	bool valid;
	int width, height;
	std::vector<uint8_t> *data_in, * data_out = new std::vector<uint8_t>;

    std::tie(valid, width, height, data_in) = read_ch_file(filename);
    
    if (debug) {
        std::cout << "The size of the vector of uint8_t's from read_ch_file: " << data_in->size() << std::endl;
    }
    
    //check if the output from last function is valid or not
	if (!valid) {
        if (debug) {
            std::cout << "Got invalid CH from read_ch" << std::endl;
        }
		return make_tuple(false, width, height, data_out);
	}

    //build a map so it will be easier to find elements in the huff table
	std::map<std::string, uint8_t> table_map;
	for (int i = 0; i <= 255; i++) {
		table_map.insert(std::pair<std::string, uint8_t>(huff_table[i], i));
	}

    int size = (int) data_in->size() * 8;
    assert(size > 0);

    //modify str ?
	std::string str = "";
	int count = 0, row = 0;

    while (count < size) {
		str += (*data_in)[row] & ((uint8_t) 1 << (7 - (count % 8))) ? "1" : "0";

        //make sure the string size is not bigger than largest string in huff
        assert(str.length() <= 29);
        
        count++;
        
        //8 elements makes a row
		if (count % 8 == 0) {
			row++;
        }
        
        //if find the string then push it back
        //modify find?
		if (table_map.find(str) != table_map.end()) {
			data_out->push_back(table_map[str]);
			str = "";
		}
	}
    
    delete data_in;
    
    if (debug) {
        std::cout << "The size of the data out is: " << data_out->size() << std::endl;
    }
    
    return std::make_tuple(valid, width, height, data_out);
}

