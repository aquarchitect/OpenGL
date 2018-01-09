//
//  flat.cpp
//  Particles-iOS
//
//  Created by Hai Nguyen on 1/9/18.
//  Copyright © 2018 Hai Nguyen. All rights reserved.
//

#include "flat.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Utility;

Flat::Flat(string basePath, vec2 resolution, Textures *textures) {
    this->resolution = resolution;
    this->textures = textures;
    
    linkShaders(basePath + "/flat", program);
    
    positionAttributeLocation = glGetAttribLocation(program, "aPosition");
    backgroundUniformLocation = glGetUniformLocation(program, "uBackground");
    resolutionUniformLocation = glGetUniformLocation(program, "uResolution");
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), vertices.data(), GL_STATIC_DRAW);
};

void Flat::_draw() {
    glViewport(0, 0, resolution.x, resolution.y);
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glUseProgram(program);

    glUniform2fv(resolutionUniformLocation, 1, value_ptr(resolution));
    
    glBindTexture(GL_TEXTURE_2D, get<0>(textures->o));
    glUniform1i(backgroundUniformLocation, get<1>(textures->o));
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(positionAttributeLocation);
    glVertexAttribPointer(positionAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, GLsizei(vertices.size()));
};

void Flat::draw() {
    glBindFramebuffer(GL_FRAMEBUFFER, 2);
    _draw();
};
