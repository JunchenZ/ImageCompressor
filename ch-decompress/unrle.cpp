//
//  main.cpp
//  ImageCompression
//
//  Created by Myriah Gibbons on 1/29/18.
//  Copyright © 2018 Myriah Gibbons. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <fstream>
#include "pbmcompress-v1.h"


using namespace std;


//std::tuple<bool, int, int, std::vector<uint8_t> *> unhuff(std::string filename){
//
//    bool wasSuccessful = true;
//    int width = 10;
//    int height = 5;
//
//    vector<uint8_t> * unhuffData = new vector<uint8_t>;
//
//    unhuffData -> push_back((uint8_t)0x05);
//    unhuffData -> push_back((uint8_t)0x85);
//    unhuffData -> push_back((uint8_t)0x05);
//    unhuffData -> push_back((uint8_t)0x85);
//    unhuffData -> push_back((uint8_t)0x05);
//
//
//    return make_tuple(wasSuccessful, width, height, unhuffData);
//
//}


std::tuple<bool, int, int, std::vector<bool> *> unrle(std::string filename){
    
    
    
    int width;
    int height;
    int oneOrZero;
    int length;
    bool wasSuccessful;
    vector<uint8_t>* unhuffData;
    vector<bool>* unrleData = new vector<bool>;
    
    tie(wasSuccessful, width, height, unhuffData) = unhuff(filename);
    
    if(!wasSuccessful){
        
        return make_tuple(wasSuccessful, width, height, unrleData);
    }
    
    
    for(int i = 0; i < unhuffData -> size(); i++){
        
        oneOrZero = unhuffData -> at(i) >> 7;
        length = unhuffData -> at(i) & 0x7F;
        
        for(int j = 0; j < length + 1; j++){
            
            if(oneOrZero == 0){
                
                unrleData -> push_back(0);
                
            } else {
                
                unrleData -> push_back(1);
            }
            
        }
        
    }
    
    delete unhuffData;
    
    return make_tuple(wasSuccessful, width, height, unrleData);
}


//int main(int argc, const char * argv[]) {
//
//    bool wasSuccessful;
//    int width;
//    int height;
//    vector<bool>* unrleData;
//
//    tie(wasSuccessful, width, height, unrleData) = unrle("filename");
//
//    cout << "wasSuccessful: " << wasSuccessful << endl;
//    cout << "width: " << width << endl;
//    cout << "height: " << height << endl;
//
//    for(int i = 0; i < unrleData -> size(); i++){
//
//        cout << unrleData -> at(i) << endl;
//
//    }
//
//
//
//    return 0;
//}

