//
//  unhuff.cpp
//  ImageCompress
//
//  Created by Chaofan Su on 1/31/18.
//  Copyright © 2018 su. All rights reserved.
//

#include "unhuff.hpp"

std::tuple<bool, int, int, std::vector<uint8_t> *> unhuff(std::string filename) {
    bool debugFlag = true;  //fix later?
	bool valid;
	int height, width;
	std::vector<uint8_t> *data_in;
	std::vector<std::uint8_t> * data_out = new std::vector<std::uint8_t>;  //declare varible ??
	tie(valid, width, height, data_in) = read_ch_file(filename);    //std ??
    if (debugFlag) {
        std::cout << "The size of the vector of uint8_t's from read_ch_file: " << data_in->size() << std::endl;
    }
	if (!valid) {
        if (debugFlag) {
            std::cout << "Got invalid CH from read_ch" << std::endl;
        }
		return make_tuple(false, width, height, data_out);
	}

	std::map<std::string, uint8_t> table_map;
	for (int i = 0; i <= 255; i++) {
		table_map.insert(std::pair<std::string, uint8_t>(huff_table[i], i));
	}

	int size = (int) data_in->size();
	std::string str = "";   //less string stuff, deal with bits
	int count = 0, row = 0;
	uint8_t mask = 1;
	while (count < (size * 8)) {
		str += data_in->at(row) & (mask << (7 - (count % 8))) ? "1" : "0";  //turn ->at to [] sometimes
        //assert string length less than 29
		count++;
		if (count % 8 == 0) {
			row++;
		}
		if (table_map.find(str) != table_map.end()) {
			data_out->push_back(table_map[str]);
			str = "";
		}
	}
    if (debugFlag) {
        std::cout << "The size of the data out is: " << data_out->size() << std::endl;
    }
	return std::make_tuple(valid, width, height, data_out);
}

/*
std::vector<uint8_t> * unhuff(std::vector<uint8_t> * data_in) {
	std::vector<uint8_t> * data_out = new std::vector<uint8_t>;
	int size = (int) data_in->size();
	std::string str = "";
	int count = 0, row = 0;
	uint8_t mask = 1;
	std::map<std::string, uint8_t> table_map;
	for (int i = 0; i <= 255; i++) {
		table_map.insert(std::pair<std::string, uint8_t>(huff_table[i], i));
	}
	while (count < (size * 8)) {
		str += data_in->at(row) & (mask << (7 - (count % 8))) ? "1" : "0";
		count++;
		if (count % 8 == 0) {
			row++;
		}
		if (table_map.find(str) != table_map.end()) {
			data_out->push_back(table_map[str]);
			str = "";
		}
	}
	return data_out;
}

void testHuff_Unhuff() {
	std::vector<uint8_t> huff_input = {0x02, 0x0C, 0x11, 0x16, 0x1B, 0x20, 0x25, 0x2A, 0X2F, 0X34};
	std::vector<uint8_t> * huff_res = huff(&huff_input);
	//std::vector<uint8_t> unhuff_input = {0x8B, 0x60, 0x12, 0x46, 0x1F, 0xD7, 0x71, 0x93, 0xED, 0xD8};
	std::vector<uint8_t> * unhuff_output = unhuff(huff_res);
	std::cout << "unhuff result: " << std::endl;
	for (int i = 0; i < unhuff_output->size(); i++) {
		std::cout << (int) unhuff_output->at(i) << std::endl;
	}
}

int main() {
	testHuff_Unhuff();
}
*/
