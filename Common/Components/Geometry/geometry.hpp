//
//  geometry.hpp
//  OpenGL
//
//  Created by Hai Nguyen on 11/20/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef geometry_hpp
#define geometry_hpp

#include "utility.hpp"
#include <string>
#include <glm/glm.hpp>
class Geometry {
private:
    enum Attribute {
        position = 0,
        color,
        texCoord,
        normal
    };
    
public:
    struct Vertex {
        GLfloat position[3];
        GLfloat color[4];
        GLfloat texCoord[2];
        GLfloat normal[3];
    };
    
    Geometry(std::string basePath, GLfloat *projection, Vertex *vertices);
    
    void            draw(GLfloat *pTransformation);
    
private:
    const GLuint    programID = glCreateProgram();

    Vertex          *pVertices;
    GLfloat         *pProjection;
    GLfloat         *pTransformation;
    
    GLuint          vertexBuffer;
    GLuint          textureBuffer;
    
    GLuint          projectionUniformID;
    GLuint          transformationUniformID;
    GLuint          textureUniformID;
    
    GLuint          vertexArrayObjectID;
};

#endif /* geometry_hpp */
