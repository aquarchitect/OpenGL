//
//  rain.cpp
//  Particles-iOS
//
//  Created by Hai Nguyen on 2/21/18.
//  Copyright © 2018 Hai Nguyen. All rights reserved.
//

#include "rain.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const float RANDOM_MAX = 100.0;
static const int OBSTACLE_SIZE = 128;

using namespace utility;

rain::rain(string basePath, vec2 particlesSize, vec2 screenResolution) {
    // data size is 128x128
    vector<char> pixels = loadBytes(basePath + "/data");
    
    this->screenResolution = screenResolution;
    this->particlesSize = particlesSize;
    
    this->particles = createPlane(int(particlesSize.x), int(particlesSize.y)).vertices;
    this->obstacles.reserve(OBSTACLE_SIZE);
    
    this->obstacleTexture = createTexture(5, screenResolution, NULL);

    this->position0Texture = createTexture(1, particlesSize, &pixels[0]);
    this->velocity0Texture = createTexture(2, particlesSize, &pixels[pixels.size()/2]);

    this->position1Texture = createTexture(3, particlesSize, NULL);
    this->velocity1Texture = createTexture(4, particlesSize, NULL);
    
    linkShaders(basePath + "/draw", drawProgram);
    linkShaders(basePath + "/particles", particlesProgram);
    linkShaders(basePath + "/obstacles", obstablesProgram);
    
    particlesPositionsUniformLocation = glGetUniformLocation(particlesProgram, "uPositions");
    particlesVelocitiesUniformLocation = glGetUniformLocation(particlesProgram, "uVelocities");
    particlesObstaclesUniformLocation = glGetUniformLocation(particlesProgram, "uObstacles");
    particlesRandomUniformLocation = glGetUniformLocation(particlesProgram, "uRandom");
    particlesResolutionUniformLocation = glGetUniformLocation(particlesProgram, "uResolution");
    particlesModeUniformLocation = glGetUniformLocation(particlesProgram, "uMode");
    particlesQuadAttributeLocation = glGetAttribLocation(particlesProgram, "aQuad");
    
    obstaclesModeUniformLocation = glGetUniformLocation(obstablesProgram, "uMode");
    obstaclesPointAttributeLocation = glGetAttribLocation(obstablesProgram, "aQuad");
    
    drawPositionsUniformLocation = glGetUniformLocation(drawProgram, "uPositions");
    drawVelocitiesUniformLocation = glGetUniformLocation(drawProgram, "uVelocities");
    drawPointAttributeLocation = glGetAttribLocation(drawProgram, "aIndex");
    
    glGenFramebuffers(1, &particlesFramebuffer);
    glGenFramebuffers(1, &obstableFramebuffer);
    
    glGenBuffers(1, &quadVertexBuffer);
    glGenBuffers(1, &particlesVertexBuffer);
    glGenBuffers(1, &obstaclesVertexBuffer);
    
    glBindBuffer(GL_ARRAY_BUFFER, quadVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, quad.size() * sizeof(vec2), &quad.front(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, particlesVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(vec2), &particles.front(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, obstaclesVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, OBSTACLE_SIZE * sizeof(vec2), &obstacles.front(), GL_DYNAMIC_DRAW);
};

void rain::updateParticles(GLint mode) {
    glPushGroupMarkerEXT(0, "Update Particles");
    glUseProgram(particlesProgram);
    
    glUniform1i(particlesModeUniformLocation, mode);
    glUniform1f(particlesRandomUniformLocation, fmod(rand(), RANDOM_MAX) / RANDOM_MAX);
    glUniform2fv(particlesResolutionUniformLocation, 1, value_ptr(screenResolution));
    
    glBindTexture(GL_TEXTURE_2D, position0Texture.object);
    glUniform1i(particlesPositionsUniformLocation, position0Texture.slot);
    
    glBindTexture(GL_TEXTURE_2D, velocity0Texture.object);
    glUniform1i(particlesVelocitiesUniformLocation, velocity0Texture.slot);
    
    glBindTexture(GL_TEXTURE_2D, obstacleTexture.object);
    glUniform1i(particlesObstaclesUniformLocation, obstacleTexture.slot);
    
    glBindBuffer(GL_ARRAY_BUFFER, quadVertexBuffer);
    glEnableVertexAttribArray(particlesQuadAttributeLocation);
    glVertexAttribPointer(particlesQuadAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, GLsizei(quad.size()));
    glPopGroupMarkerEXT();
};

void rain::drawOnScreen() {
    glPushGroupMarkerEXT(0, "Draw On Screen");
    glUseProgram(drawProgram);
    
    glBindTexture(GL_TEXTURE_2D, position0Texture.object);
    glUniform1i(drawPositionsUniformLocation, position0Texture.slot);
    
    glBindTexture(GL_TEXTURE_2D, velocity0Texture.object);
    glUniform1i(drawVelocitiesUniformLocation, velocity0Texture.slot);
    
    glBindBuffer(GL_ARRAY_BUFFER, particlesVertexBuffer);
    glEnableVertexAttribArray(drawPointAttributeLocation);
    glVertexAttribPointer(drawPointAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glDrawArrays(GL_POINTS, 0, GLsizei(particles.size()));
    glPopGroupMarkerEXT();
};

void rain::drawObstacles(GLint mode) {
    glPushGroupMarkerEXT(0, "Draw Obstacles");
    glUseProgram(obstablesProgram);
    
    glUniform1i(obstaclesModeUniformLocation, mode);
    
    glBindBuffer(GL_ARRAY_BUFFER, obstaclesVertexBuffer);
    glEnableVertexAttribArray(obstaclesPointAttributeLocation);
    glVertexAttribPointer(obstaclesPointAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glDrawArrays(GL_POINTS, 0, GLsizei(obstacles.size()));
    glPopGroupMarkerEXT();
};

void rain::addObstacle(vec2 position) {
    vec2 obstacle = position / screenResolution;
    obstacles.push_back(obstacle);
    
    glBindBuffer(GL_ARRAY_BUFFER, obstaclesVertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, (obstacles.size() - 1) * sizeof(vec2), sizeof(vec2), &obstacle);
    
    glBindFramebuffer(GL_FRAMEBUFFER, obstableFramebuffer);
    glViewport(0, 0, screenResolution.x, screenResolution.y);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, obstacleTexture.object, 0);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    drawObstacles(0);
};

void rain::swapPositionsTextures() {
    GLuint object = position0Texture.object;
    position0Texture = {position1Texture.object, position0Texture.slot};
    position1Texture = {object, position1Texture.slot};
};

void rain::swapVelocitiesTextures() {
    GLuint object = velocity0Texture.object;
    velocity1Texture = {velocity1Texture.object, velocity0Texture.slot};
    velocity1Texture = {object, velocity1Texture.slot};
};

void rain::draw() {
    glBindFramebuffer(GL_FRAMEBUFFER, particlesFramebuffer);
    glViewport(0, 0, particlesSize.x, particlesSize.y);

    if (frame >= 2) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, position1Texture.object, 0);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_BLEND);
        updateParticles(0);
        swapPositionsTextures();

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, velocity1Texture.object, 0);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_BLEND);
        updateParticles(1);
        swapVelocitiesTextures();
    } else {
        // scale down the initial velocities
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, velocity1Texture.object, 0);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_BLEND);
        updateParticles(2);
        swapVelocitiesTextures();
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
    glViewport(0, 0, screenResolution.x, screenResolution.y);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    drawOnScreen();
    drawObstacles(1);
    
    frame += 1;
};
