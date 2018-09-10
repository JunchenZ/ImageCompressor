//
//  main.cpp
//  ch-compress
//
//  Created by Junchen Zhang on 2/1/18.
//  Copyright © 2018 Junchen Zhang. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "pbmcompress-v1.h"
#include "assert.h"
#include <string.h>
#include <vector>

int main(int argc, const char * argv[]) {
    std::string inputFile = argv[1];

    std::tuple<bool, int, int, std::vector<uint8_t> *> huffData = huff(inputFile);

    if(!std::get<0>(huffData)){
        std::cout << "error\n";
        return 0;
    }

    std::string filename = std::string(inputFile).substr(0, std::string(inputFile).find(".pbm")) + ".ch";

    std::ofstream file(filename, std::ios::out | std::ios::binary);
    int width = std::get<1>(huffData);
    int height = std::get<2>(huffData);

    file << "ch";
    file.write(reinterpret_cast<char *>(&width), sizeof(width));
    file.write(reinterpret_cast<char *>(&height), sizeof(height));

    for(int i = 0; i < std::get<3>(huffData)->size(); i++){
        file.write(reinterpret_cast<char *>(&std::get<3>(huffData)->at(i)), sizeof(std::get<3>(huffData)->at(i)));
    }
    file.close();
    
}

