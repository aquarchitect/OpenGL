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
    Textures(string basePath, vec2 size);
    
    void        swap();
    vec2        size;
    
    GLuint      p0, v0, p1, v1;
};
#endif /* textures_hpp */
