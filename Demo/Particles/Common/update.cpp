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

using namespace Utility;

Update::Update(string basePath, vec2 size, vec2 resolution, Textures *textures) {
    this->size = size;
    this->resolution = resolution;
    this->textures = textures;
    
    linkShaders(basePath + "/update", program);
    
    resolutionUniformLocation = glGetUniformLocation(program, "uResolution");
    positionsUniformLocation = glGetUniformLocation(program, "uPositions");
    velocitiesUniformLocation = glGetUniformLocation(program, "uVelocities");
    modeUniformLocation = glGetUniformLocation(program, "uMode");
    
    glGenFramebuffers(1, &FBO);
    
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
    
    GLuint positionAttibuteLocation = glGetAttribLocation(program, "aPosition");
    glEnableVertexAttribArray(positionAttibuteLocation);
    glVertexAttribPointer(positionAttibuteLocation, 2, GL_FLOAT, GL_FALSE, 0, NULL);

#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(0);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(0);
#endif
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
};

void Update::draw(GLint mode) {
    glViewport(0, 0, size.x, size.y);
    
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_BLEND);
    glUseProgram(program);
    
    glUniform1i(modeUniformLocation, mode);
    glUniform2fv(resolutionUniformLocation, 1, value_ptr(resolution));
    
    glBindTexture(GL_TEXTURE_2D, get<0>(textures->p0));
    glUniform1i(positionsUniformLocation, get<1>(textures->p0));
    
    glBindTexture(GL_TEXTURE_2D, get<0>(textures->v0));
    glUniform1i(velocitiesUniformLocation, get<1>(textures->v0));
    
#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(VAO);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(VAO);
#endif
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, GLsizei(vertices.size()));
    
#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(0);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(0);
#endif
    
    glBindTexture(GL_TEXTURE_2D, 0);
};

void Update::draw() {
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    if (count >= 2) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, get<0>(textures->p1), 0);
        draw(0);
        textures->swapPositions();

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, get<0>(textures->v1), 0);
        draw(1);
        textures->swapVelocities();
    } else {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, get<0>(textures->v1), 0);
        draw(2);
        textures->swapVelocities();
    }
    
    // unfortunately the default framebuffer is not 0
    glBindFramebuffer(GL_FRAMEBUFFER, 2);
    
    count += 1;
};
