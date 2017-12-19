//
//  update.hpp
//  Particles-iOS
//
//  Created by Hai Nguyen on 12/18/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef update_hpp
#define update_hpp

#include "utility.hpp"

using BytePair = tuple<GLubyte, GLubyte>;

class Update {
public:
    Update(string basePath, vec2 grid, vec2 resolution);
    void draw();
private:
    struct RGBA { GLubyte r, g, b, a; };
    struct Textures { GLuint p0, p1, v0, v1; };
    
    const GLint    base = 255;
    
    vector<vec2>   vertices = {
                        {-1.0, -1.0},
                        {-1.0, +1.0},
                        {+1.0, -1.0},
                        {+1.0, +1.0}
                    };
    
    vec2            grid;
    vec2            scale;
    
    GLuint          program = glCreateProgram();
    
    GLuint          VAO;
    GLuint          VBO;
    GLuint          FBO;
    
    Textures        textures;
    
    GLuint          scaleUniformLocation;
    
    GLuint          createTexture(GLuint slot, GLvoid *pixels);
    
    BytePair        encode(GLfloat value, GLfloat scale);
    GLfloat         decode(BytePair bytes, GLfloat scale);
};

#endif /* update_hpp */
