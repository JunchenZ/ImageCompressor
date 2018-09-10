/*    rle.cpp
 *    Part of larger Group 1 project
 *    Huffman compression assignment
 *    UofU MSD, Software Engineering
 *    Spring 2018
 *
 *    Created by Ted Pochmara,  1/28/2018
 */

#include <tuple>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <bitset>
#include "pbmcompress-v1.h"

using tupleReadFile = std::tuple<bool, int, int, std::vector<bool> *>;
using tupleRLE = std::tuple<bool, int, int, std::vector<uint8_t> *>;

uint8_t setByte(uint8_t arg, uint8_t value, int b){
    return arg |= (value << b);
}

//parameter is currently set for testing | will change to 'string filename'
std::tuple<bool, int, int, std::vector<uint8_t> *> rle(std::string filename){
    tupleReadFile readFile = read_pbm_file(filename);
    std::vector<uint8_t>* destination = new std::vector<uint8_t>;
    
    //unpack the tuple but use std::tie instead
    bool success = std::get<0>(readFile); //do some actual error checking
    int width = std::get<1>(readFile);
    int height = std::get<2>(readFile);
    std::vector<bool>* unPackedBools = std::get<3>(readFile);
    
    //get the first bool of a run
    for (int runPos = 0; runPos < unPackedBools->size(); runPos++){
        uint8_t destByte = 0b00000000;
        destByte = setByte(destByte, unPackedBools->at(runPos), 7);
        
        //count the run length for the above bool
        int runCount = 1;
        while(runPos + 1 < unPackedBools->size() &&
              unPackedBools->at(runPos) == unPackedBools->at(runPos + 1)){
            if (runCount == 128){
                break;
            }
            runCount++;
            runPos++;
        }
        //add the length of this bool's run
        destByte = setByte(destByte, (uint8_t) runCount - 1, 0);
        destination->push_back(destByte);
    }
    //make and return the final tuple result
    //delete pointer of read_file
    return std::make_tuple(success, width, height, destination);
}
