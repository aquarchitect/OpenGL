//
//  main.cpp
//  Playground
//
//  Created by Hai Nguyen on 12/29/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>

using namespace std;

int main(int argc, const char * argv[]) {
//    cout << modff(float(rand()), float(100.0)) / float(100.0);
    
    for (int i = 0; i < 10; i++) {
        cout << fmod(rand(), 100.0) / 100.0 << "\n";
    }
    
    return 0;
}
