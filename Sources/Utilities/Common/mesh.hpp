//
//  mesh.hpp
//  OpenGL
//
//  Created by Hai Nguyen on 2/22/18.
//  Copyright © 2018 Hai Nguyen. All rights reserved.
//

#ifndef mesh_hpp
#define mesh_hpp

#include "utility.hpp"

using namespace utility;

class mesh {
public:
    struct vertex {
        vec3    position;
        vec3    normal;
        vec2    texCoord;
    };
    
    struct light {
        vec3    color;
        vec3    direction;
        
        GLfloat ambient;
        GLfloat diffuse;
        GLfloat specular;
    };
    
    mesh(string basePath, vector<vertex> vertices, vector<GLubyte> indices, texture texture);
    
    void            draw(light light, mat4 model, mat4 world, mat4 view, mat4 projection);
private:
    vector<GLubyte> indices;
    texture         texture;
    
    GLuint          program = glCreateProgram();
    
    GLuint          arrayBuffer;
    GLuint          verticesBuffer;
    GLuint          indicesBuffer;
    
    GLuint          textureUniformLocation;
    GLuint          modelUniformLocation;
    GLuint          viewUniformLocation;
    GLuint          worldUniformLocation;
    GLuint          projectionUniformLocation;
    
    GLuint          lightColorUniformLocation;
    GLuint          lightDirectionUniformLocation;
    GLuint          lightAmbientUniformLocation;
    GLuint          lightDiffuseUniformLocation;
    GLuint          lightSpecularUniformLocation;
};

#endif /* mesh_hpp */
