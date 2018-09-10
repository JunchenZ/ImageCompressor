//
//  pbmCheck.cpp
//  dump-runs
//
//  Created by Junchen Zhang on 2/14/18.
//  Copyright © 2018 Junchen Zhang. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream input1 (argv[1]);
    ifstream input2 (argv[2]);
    char ch1, ch2;
    while(input1 >> ch1){
        if(ch1 == '\n'){
            continue;
        }else{
            input2 >> ch2;
            if(ch2 == '\n'){
                continue;
            }
            if(ch1 != ch2){
                cout << "ERROR! The new pbm file is not same as the original one!\n";
                return 0;
            }
        }
        
    }
    cout << "Succeed! The new pbm file is same as the original one!\n";
}
