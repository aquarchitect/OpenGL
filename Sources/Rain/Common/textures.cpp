//
//  textures.cpp
//  Particles-iOS
//
//  Created by Hai Nguyen on 12/21/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "textures.hpp"

using namespace utility;

Texture createTexture(GLuint slot, vec2 size, GLvoid *pixels) {
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)size.x, (GLsizei)size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    
    return {texture, slot};
};

Textures::Textures(string basePath, vec2 size, vec2 resolution) {
    // data size is 128x128
    vector<char> pixels = loadBytes(basePath + "/data");
    
    this->o = createTexture(5, resolution, NULL);
    
    this->p0 = createTexture(1, size, &pixels[0]);
    this->v0 = createTexture(2, size, &pixels[pixels.size()/2]);
    
    this->p1 = createTexture(3, size, NULL);
    this->v1 = createTexture(4, size, NULL);
};

void Textures::swapPositions() {
    GLuint object = p0.object;
    p0 = {p1.object, p0.slot};
    p1 = {object, p1.slot};
};

void Textures::swapVelocities() {    
    GLuint object = v0.object;
    v0 = {v1.object, v0.slot};
    v1 = {object, v1.slot};
};
