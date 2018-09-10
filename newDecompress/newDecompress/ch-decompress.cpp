//
//  main.cpp
//  ch-decompress
//
//  Created by Junchen Zhang on 2/1/18.
//  Copyright © 2018 Junchen Zhang. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "pbmcompress-v1.h"
#include "huff.h"
#include "assert.h"
#include <string.h>
#include <vector>

int main(int argc, const char * argv[]) {
    
    std::string inputFile = "x-0005.ch";

    std::tuple<bool, int, int, std::vector<bool> *> unrleData = unrle(inputFile);

    if(!std::get<0>(unrleData)){
        std::cout << "error\n";
        return 0;
    }

    std::string filename = "x-0005_new.pbm";
    std::ofstream file;
    file.open(filename);

    int width = std::get<1>(unrleData);
    int height = std::get<2>(unrleData);

    file << "P1\n" << width << " " << height << std::endl;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int data = std::get<3>(unrleData)->at(i * width + j);
            file << data;
        }
        file << std::endl;
    }
    file.close();
}

