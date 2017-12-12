//
//  geometry.h
//  OpenGL
//
//  Created by Hai Nguyen on 11/20/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef geometry_h
#define geometry_h

// geometry.cpp
#ifdef __cplusplus
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
    
    void                    loadTexture(GLsizei width, GLsizei height, GLvoid *pixels);
    void                    draw(glm::mat4 model, glm::mat4 world, glm::mat4 view, glm::mat4 projection);
private:
    std::vector<GLubyte>    indices;
    std::vector<Vertex>     vertices;
    
    const GLuint            programID = glCreateProgram();
    
    GLuint                  vertexArrayObject;
    GLuint                  bufferObjects[2];
    GLuint                  textureObject;
    
    GLuint                  modelUniformLocation;
    GLuint                  worldUniformLocation;
    GLuint                  viewUniformLocation;
    GLuint                  projectionUniformLocation;
    
    GLuint                  textureUniformLocation;
};
#endif /* __cplusplus */

// geometry+.cpp
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
    extern void setupCube(float screenRatio, char *basePath);
    extern void rotateCube(float xAngle, float yAngle, float zAngle);
    
    extern void loadCubeTexture(int width, int height, void *pixels);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* geometry_h */
