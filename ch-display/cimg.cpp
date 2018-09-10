//
//  main.cpp
//  ch-display
//
//  Created by Junchen Zhang on 2/1/18.
//  Copyright © 2018 Junchen Zhang. All rights reserved.
//

#include <iostream>
#include "CImg.h"
#include <stdio.h>

using namespace cimg_library;

int main(int argc, const char * argv[]) {
    CImg<unsigned char> img(argv[1]);
    img.display();
}
