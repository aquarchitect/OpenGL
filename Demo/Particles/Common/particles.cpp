//
//  particles.cpp
//  Particles-iOS
//
//  Created by Hai Nguyen on 12/14/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "particles.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Utility;

Particles::Particles(string basePath, vec2 size, vec2 resolution, Textures *textures) {
    vector<vec2> vertices(size[0] * size[1], {0.0, 0.0});
    for (int j = 0; j < size.y; j++) {
        for (int i = 0; i < size.x; i++) {
            int index = j * int(size.x) + i;
            
            vertices[index] = {
                GLfloat(i/size.x),
                GLfloat(j/size.y)
            };
        };
    };
    
    this->textures = textures;
    this->resolution = resolution;
    this->vertices = vertices;
    
    linkShaders(basePath + "/particles", program);
    
    resolutionUniformLocation = glGetUniformLocation(program, "uResolution");
    positionsUniformLocation = glGetUniformLocation(program, "uPositions");
    velocitiesUniformLocation = glGetUniformLocation(program, "uVelocities");
    
#if GL_APPLE_vertex_array_object
    glGenVertexArraysAPPLE(1, &VAO);
    glBindVertexArrayAPPLE(VAO);
#elif GL_OES_vertex_array_object
    glGenVertexArraysOES(1, &VAO);
    glBindVertexArrayOES(VAO);
#endif
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices.front(), GL_STATIC_DRAW);
    
    GLuint texCoordAttributeLocation = glGetAttribLocation(program, "aTexCoord");
    glEnableVertexAttribArray(texCoordAttributeLocation);
    glVertexAttribPointer(texCoordAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(0);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(0);
#endif

    glBindBuffer(GL_ARRAY_BUFFER, 0);
};

void Particles::draw() {
    glViewport(0, 0, resolution.x, resolution.y);
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glUseProgram(program);
    
    glBindTexture(GL_TEXTURE_2D, get<0>(textures->p0));
    glUniform1i(positionsUniformLocation, get<1>(textures->p0));
    
    glBindTexture(GL_TEXTURE_2D, get<0>(textures->v0));
    glUniform1i(velocitiesUniformLocation, get<1>(textures->v0));
    
#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(VAO);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(VAO);
#endif

    glDrawArrays(GL_POINTS, 0, GLsizei(vertices.size()));

#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(0);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(0);
#endif
    
    glBindTexture(GL_TEXTURE_2D, 0);
};
