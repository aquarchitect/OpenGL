//
//  obstacles.cpp
//  Particles-iOS
//
//  Created by Hai Nguyen on 1/8/18.
//  Copyright © 2018 Hai Nguyen. All rights reserved.
//

#include "obstacles.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace utility;

Obstacles::Obstacles(string basePath, vec2 resolution, Textures *textures) {
    const int count = 128;

    this->resolution = resolution;
    this->textures = textures;
    this->vertices.reserve(count);
    
    linkShaders(basePath + "/obstacles", program);
    
    positionAttributeLocation = glGetAttribLocation(program, "aPosition");
    modeUniformLocation = glGetUniformLocation(program, "uMode");
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(vec2), vertices.data(), GL_DYNAMIC_DRAW);
    
    glGenFramebuffers(1, &FBO);
};

void Obstacles::draw(GLint mode) {
    glViewport(0, 0, resolution.x, resolution.y);
    
    if (mode == 0) {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_BLEND);
    } else {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
    glUseProgram(program);
    
    glUniform1i(modeUniformLocation, mode);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(positionAttributeLocation);
    glVertexAttribPointer(positionAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    glDrawArrays(GL_POINTS, 0, GLsizei(vertices.size()));
};

void Obstacles::addObstacle(vec2 position) {
    vec2 vertex = position / resolution;
    vertices.push_back(vertex);
    
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textures->o.object, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, (vertices.size() - 1) * sizeof(vec2), sizeof(vec2), &vertex);
    
    draw(0);
};
