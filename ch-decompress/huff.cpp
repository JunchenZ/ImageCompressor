//
//  huff.cpp
//  assignment02.pbmcompress
//
//  Created by Matt Josse on 1/25/18.
//  Copyright © 2018 Matt Josse. All rights reserved.
//

#include <array>
#include <assert.h>
#include <iostream>
#include <string>
#include "huff.h"
#include "pbmcompress-v1.h"
#include <tuple>
#include <vector>

// Further compresses runlength compressed data. If any part of the upstream
// data flow encounters an error, this function returns false. Implements
// huffman compression via a pre-computed table incldued in "huff.h". Also
// returns the width and height alongside the data stream.
std::tuple<bool, int, int, std::vector<uint8_t> *> huff(std::string filename) {
    auto rl = rle(filename);
    if (!std::get<0>(rl)) {
        return rl; // if bool is false, forward the uncompressed data
    }
    std::vector<uint8_t> data = *std::get<3>(rl); // rle compressed
    auto result = new std::vector<uint8_t>(); // huffman compressed
    int index = 0;
    int count = 0;
    uint8_t byte = 0;
    while (index < data.size()) {
        for (int i = 0; i < huff_table[data[index]].length(); i++) { // pattern length
            uint8_t mask = 0;
            if (huff_table[data[index]][i] == '1') {
                mask = 1;
            }
            byte <<= 1;
            byte ^= mask;
            count++;
            if (count >= 8) { // packed byte
                result->push_back(byte);
                byte = 0;
                count = 0;
            }
        }
        index++;
    }
    if (count > 0) {
        result->push_back(byte <<= (8 - count)); // pad remaining byte
    }
    return std::make_tuple(std::get<0>(rl), std::get<1>(rl), std::get<2>(rl), result);
}

