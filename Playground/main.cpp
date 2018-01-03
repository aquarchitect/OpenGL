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
    string basePath = "velocities";
    
    ifstream ifs(basePath, ios::binary | ios::ate);
    ifstream::pos_type position = ifs.tellg();
    vector<char> result(position);
    
    ifs.seekg(0, ios::beg);
    ifs.read(result.data(), position);

    cout << result.size();
    
    return 0;
}
