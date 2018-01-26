//
//  Update.cpp
//  Particles-iOS
//
//  Created by Hai Nguyen on 12/18/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "update.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace utility;

Update::Update(string basePath, vec2 size, vec2 resolution, Textures *textures) {
    this->size = size;
    this->resolution = resolution;
    this->textures = textures;
    
    linkShaders(basePath + "/update", program);
    
    resolutionUniformLocation = glGetUniformLocation(program, "uResolution");
    positionsUniformLocation = glGetUniformLocation(program, "uPositions");
    velocitiesUniformLocation = glGetUniformLocation(program, "uVelocities");
    obstaclesUniformLocation = glGetUniformLocation(program, "uObstacles");
    modeUniformLocation = glGetUniformLocation(program, "uMode");
    randomUniformLocation = glGetUniformLocation(program, "uRandom");
    positionAttributeLocation = glGetAttribLocation(program, "aPosition");
    
    glGenFramebuffers(1, &FBO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices.front(), GL_STATIC_DRAW);
};

void Update::draw(GLint mode) {
    glViewport(0, 0, size.x, size.y);
    
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_BLEND);
    glUseProgram(program);
    
    const float MAX = 100.0;
    glUniform1f(randomUniformLocation, fmod(rand(), MAX) / MAX);
    
    glUniform1i(modeUniformLocation, mode);
    glUniform2fv(resolutionUniformLocation, 1, value_ptr(resolution));
    
    glBindTexture(GL_TEXTURE_2D, textures->p0.object);
    glUniform1i(positionsUniformLocation, textures->p0.slot);
    
    glBindTexture(GL_TEXTURE_2D, textures->v0.object);
    glUniform1i(velocitiesUniformLocation, textures->v0.slot);
    
    glBindBuffer(GL_TEXTURE_2D, textures->o.object);
    glUniform1i(obstaclesUniformLocation, textures->o.slot);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(positionAttributeLocation);
    glVertexAttribPointer(positionAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, GLsizei(vertices.size()));
};

void Update::draw() {
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    if (count >= 2) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textures->p1.object, 0);
        draw(0);
        textures->swapPositions();

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textures->v1.object, 0);
        draw(1);
        textures->swapVelocities();
    } else {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textures->v1.object, 0);
        draw(2);
        textures->swapVelocities();
    }
    
    count += 1;
};