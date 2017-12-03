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
#include <vector>
#include <glm/glm.hpp>

class Geometry {
public:
    struct Vertex {
        GLfloat position[3];
        GLfloat color[4];
        GLfloat texCoord[2];
        GLfloat normal[3];
    };
    
    Geometry(std::string basePath, std::vector<Vertex> vertices, std::vector<GLubyte> indices);
    
    void                    draw(glm::mat4 transformation, glm::mat4 projection);
    void                    loadTexture(GLsizei width, GLsizei height, GLvoid *pixels);
    
private:
    std::vector<GLubyte>    indices;
    std::vector<Vertex>     vertices;
    
    const GLuint            programID = glCreateProgram();
    
    GLuint                  vertexArrayObject;
    GLuint                  bufferObjects[2];
    GLuint                  textureObject;
    
    GLuint                  projectionUniformLocation;
    GLuint                  transformationUniformLocation;
    GLuint                  textureUniformLocation;
};

#endif /* geometry_hpp */
