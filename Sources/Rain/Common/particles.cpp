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
    texCoordAttributeLocation = glGetAttribLocation(program, "aTexCoord");
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices.front(), GL_STATIC_DRAW);
};

void Particles::_draw() {
    glViewport(0, 0, resolution.x, resolution.y);
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glUseProgram(program);
    
    glUniform2fv(resolutionUniformLocation, 1, value_ptr(resolution));
    
    glBindTexture(GL_TEXTURE_2D, textures->p0.object);
    glUniform1i(positionsUniformLocation, textures->p0.slot);
    
    glBindTexture(GL_TEXTURE_2D, textures->v0.object);
    glUniform1i(velocitiesUniformLocation, textures->v0.slot);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(texCoordAttributeLocation);
    glVertexAttribPointer(texCoordAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glDrawArrays(GL_POINTS, 0, GLsizei(vertices.size()));
};

void Particles::draw() {
    glBindFramebuffer(GL_FRAMEBUFFER, 3);
    _draw();
}
