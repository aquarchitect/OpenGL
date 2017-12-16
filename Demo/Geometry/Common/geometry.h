//
//  geometry.h
//  OpenGL
//
//  Created by Hai Nguyen on 11/20/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

//#ifndef GLM_ENABLE_EXPERIMENTAL
//#define GLM_ENABLE_EXPERIMENTAL

#ifndef geometry_h
#define geometry_h

// geometry.cpp
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
    
    const GLuint       programID = glCreateProgram();
    
    GLuint             VAO;
    GLuint             buffers[2];
    GLuint             texture;
    
    GLuint             modelUniformLocation;
    GLuint             worldUniformLocation;
    GLuint             viewUniformLocation;
    GLuint             projectionUniformLocation;
    GLuint             textureUniformLocation;
};
#endif /* __cplusplus */

// geometry+.cpp
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
    extern void setupCube(float screenRatio, char *basePath);
    
    extern void moveCamera(float pitch, float yaw, float roll);
    
    extern void loadCubeTexture(int width, int height, void *pixels);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* geometry_h */
//#endif /* GLM_ENABLE_EXPERIMENTAL */

