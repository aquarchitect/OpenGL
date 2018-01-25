//
//  flat.cpp
//  Ripple-iOS
//
//  Created by Hai Nguyen on 1/20/18.
//  Copyright © 2018 Hai Nguyen. All rights reserved.
//

#include "flat.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Utility;

Flat::Flat(string basePath, vec2 resolution) {
    this->resolution = resolution;
    
    linkShaders(basePath + "/flat", program);
    
    positionAttributeLocation = glGetAttribLocation(program, "aPosition");
    textureUniformLocation = glGetUniformLocation(program, "uTexture");
    timeUniformLocation = glGetUniformLocation(program, "uTime");
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices.front(), GL_STATIC_DRAW);
};

void Flat::draw(float deltaTime) {
    glViewport(0, 0, resolution.x, resolution.y);
    
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_BLEND);
    glUseProgram(program);
    
    glBindTexture(GL_TEXTURE_2D, this->texture.object);
    glUniform1i(textureUniformLocation, this->texture.slot);
    
    glUniform1f(timeUniformLocation, deltaTime);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(positionAttributeLocation);
    glVertexAttribPointer(positionAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, GLsizei(vertices.size()));
};

void Flat::loadTexture(GLuint texture) {
    this->texture = {texture, 1};
    glActiveTexture(GL_TEXTURE0 + this->texture.slot);
    glBindTexture(GL_TEXTURE_2D, this->texture.object);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
};
