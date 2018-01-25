//
//  flat.hpp
//  Ripple-iOS
//
//  Created by Hai Nguyen on 1/20/18.
//  Copyright © 2018 Hai Nguyen. All rights reserved.
//

#ifndef flat_hpp
#define flat_hpp

#include "utility.hpp"

class Flat {
public:
    Flat(string basePath, vec2 resolution);
    
    void        loadTexture(GLuint texture);
    void        draw(float deltaTime);
private:
    vector<vec2>    vertices = {
                        {-1.0, -1.0},
                        {-1.0, +1.0},
                        {+1.0, -1.0},
                        {+1.0, +1.0}
                    };
    
    GLuint          program = glCreateProgram();
    
    vec2            resolution;
    
    GLuint          VBO;
    Texture         texture;
    
    GLuint          textureUniformLocation;
    GLuint          timeUniformLocation;
    GLuint          positionAttributeLocation;
};

#endif /* flat_hpp */
