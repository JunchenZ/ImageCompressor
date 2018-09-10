//
//  main.cpp
//  PbmGenerator
//
//  Created by Junchen Zhang on 2/7/18.
//  Copyright © 2018 Junchen Zhang. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, const char * argv[]) {
    for(int i = 0; i < 15; i++){
        string str = to_string(i);
        if(i < 10){
            str = "0" + str;
        }
        ofstream os;
        str = "x-00" + str + ".pbm";
        os.open(str);
        int width = rand() % 1000 + 100;
        int height = rand() % 1000 + 100;
        os << "P1\n" << width << " " << height << "\n";
        for(int h = 0; h < height; h++){
            for(int w = 0; w < width; w++){
                os << rand() % 2;
            }
            os << "\n";
        }
        os.close();
    }
//    for(int i = 0; i < 15; i++){
//        string str = to_string(i);
//        if(i < 10){
//            str = "0" + str;
//        }
//        ofstream os;
//        os.open("/large/x-00" + str + ".pbm");
//        int width = rand() % 1000;
//        int height = rand() % 1000;
//        os << "P1\n" << width << " " << height << "\n";
//        for(int h = 0; h < height; h++){
//            for(int w = 0; w < width; w++){
//                os << rand() % 2;
//            }
//            os << "\n";
//        }
//        os.close();
//    }
}
