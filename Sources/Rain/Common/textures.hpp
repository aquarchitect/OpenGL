//
//  textures.hpp
//  Particles-iOS
//
//  Created by Hai Nguyen on 12/21/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef textures_hpp
#define textures_hpp

#include "utility.hpp"

class Textures {
public:
    Textures(string basePath, vec2 size, vec2 resolution);
    
    void        swapPositions();
    void        swapVelocities();
    
    Texture     p0, p1; // position
    Texture     v0, v1; // velocity
    Texture     o;  // obstacle
};
#endif /* textures_hpp */
