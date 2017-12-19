//
//  geometry.hpp
//  Geometry-iOS
//
//  Created by Hai Nguyen on 11/20/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef geometry_hpp
#define geometry_hpp

#ifdef __cplusplus
#include "utility.hpp"

class Geometry {
public:
    struct Vertex {
        GLfloat position[3];
        GLfloat color[4];
        GLfloat texCoord[2];
        GLfloat normal[3];
    };
    
    Geometry(string basePath, vector<Vertex> vertices, vector<GLubyte> indices);
    
    void               loadTexture(GLsizei width, GLsizei height, GLvoid *pixels);
    void               draw(mat4 model, mat4 world, mat4 view, mat4 projection);
private:
    vector<GLubyte>    indices;
    vector<Vertex>     vertices;
    
    GLuint             program = glCreateProgram();
    
    GLuint             VAO;
    GLuint             VBOs[2];
    GLuint             texture;
    
    GLuint             modelUniformLocation;
    GLuint             worldUniformLocation;
    GLuint             viewUniformLocation;
    GLuint             projectionUniformLocation;
    GLuint             textureUniformLocation;
};
#endif /* __cplusplus */
#endif /* geometry_hpp */
