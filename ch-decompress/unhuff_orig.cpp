//
//  unhuff2.cpp
//  Image Compression and Decompression
//
//  Created by Jennifer Niang on 2/1/18.
//  Copyright © 2018 Jennifer Niang. All rights reserved.
//


#include <stdio.h>
#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include <assert.h>
#include <map>
#include "huff.h"
#include "pbmcompress-v1.h"
using namespace std;


//TODO: I have tested and have fixed to what I know I am sure their are mistakes and will be happy to fix them

uint8_t findTable(string element){
    for(uint8_t i = 0; i <= 255; i++){
        if (element == huff_table[i]){
            return i;
        }
    }
    return -1;
}
//
tuple<bool, int, int, vector<uint8_t>*> unhuff(string filename){
    bool isValid;
    int heightTable;
    int widthTable;
    vector<uint8_t> *inputOfData;
    vector<uint8_t> *outputOfData = new vector<uint8_t>();
    tie(isValid, widthTable, heightTable, inputOfData)= read_ch_file(filename);
    // checking these values
    //cout << "Printing out values from the Huff:" << heightTable << " " << widthTable << endl;
    //        for (int i=0; i < inputOfData->size(); i++){
    //
    //            cout << "Input of Data from Huff:" << inputOfData->at(i) << endl;
    //        }
    if(!isValid){
        return make_tuple(false, widthTable, heightTable, outputOfData);
    }
    map<std::string, uint8_t> map;
    for (int i = 0; i <= 255; i++) {
        map.insert(pair<string, uint8_t>(huff_table[i], i));
    }
    
    string stringOfData;
    int count =0;// byte count
    int i = 0; //bit count
    uint8_t mask = 1;
    stringOfData = "";
    
    while(count < (inputOfData->size() * 8)){
        //TODO: need to replace with the old code and add hash map
        //I fixed this part on 2.2.18 7:00 p.m.
        
        if((inputOfData->at(i)&(mask << (7 - (count % 8)))) >= 1){
            stringOfData += "1";
        } else {
            stringOfData += "0";
        }
        count ++;
        if(count % 8 == 0){
            i++;
        }
        if (map.find(stringOfData) != map.end()) {
            outputOfData->push_back(map[stringOfData]);
            stringOfData = "";
        }
    }
    return make_tuple(isValid, widthTable, heightTable, outputOfData);
}

//int main(int argc, const char * argv[]) {
//std::tuple<bool, int, int, std::vector<uint8_t> *> unhuffData = unhuff("test.ch");
//    std::vector<uint8_t> * vector = std::get<3>(unhuffData);
////    cout << vector->size() << endl;
//    for(int i = 0; i < vector->size(); i++){
//        cout << (int) vector->at(i)<< endl;
//    }
//    cout << endl;
//}

