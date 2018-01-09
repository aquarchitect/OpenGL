//
//  flat.hpp
//  Particles-iOS
//
//  Created by Hai Nguyen on 1/9/18.
//  Copyright © 2018 Hai Nguyen. All rights reserved.
//

#ifndef flat_hpp
#define flat_hpp

#include "utility.hpp"
#include "textures.hpp"

class Flat {
public:
    Flat(string basePath, vec2 resolution, Textures *textures);
    
    void        draw();
private:
    vector<vec2>    vertices = {
                        {-1.0, -1.0},
                        {-1.0, +1.0},
                        {+1.0, -1.0},
                        {+1.0, +1.0}
                    };
    
    GLuint          program = glCreateProgram();
    
    Textures        *textures;
    vec2            resolution;
    
    GLuint          VBO;
    
    GLuint          positionAttributeLocation;
    GLuint          backgroundUniformLocation;
    GLuint          resolutionUniformLocation;
    
    void            _draw();
};

#endif /* flat_hpp */
