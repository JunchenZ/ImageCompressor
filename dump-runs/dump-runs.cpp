#include <iostream>
#include <fstream>
#include "pbmcompress-v1.h"
#include "assert.h"
#include <string.h>
#include <vector>

using namespace std;
int main(int argc, const char * argv[]) {
    std::tuple<bool, int, int, std::vector<uint8_t> *> rleData = rle(argv[1]);

    if(!std::get<0>(rleData)){
        std::cout << "error\n";
        return 0;
    }

    std::string filename = std::string(argv[1]).substr(0, std::string(argv[1]).find(".pbm")) + ".bin";
    std::ofstream file(filename, std::ios::out | std::ios::binary);

    for(int i = 0; i < std::get<3>(rleData)->size(); i++){
        char data = std::get<3>(rleData)->at(i);
        file.write(&data, sizeof(uint8_t));
    }
    file.close();
}


