//
//  textures.cpp
//  Particles-iOS
//
//  Created by Hai Nguyen on 12/21/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "textures.hpp"

using namespace Utility;

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
    
    return make_tuple(texture, slot);
};

Textures::Textures(string basePath, vec2 size, vec2 resolution) {
    // data size is 128x128
    vector<char> pixels = loadBytes(basePath + "/data");
    
    this->p0 = createTexture(1, size, &pixels[0]);
    this->v0 = createTexture(2, size, &pixels[pixels.size()/2]);
    
    this->p1 = createTexture(3, size, NULL);
    this->v1 = createTexture(4, size, NULL);
    
    this->o = createTexture(5, resolution, NULL);
};

void Textures::swapPositions() {
    GLuint object = get<0>(p0);
    p0 = make_tuple(get<0>(p1), get<1>(p0));
    p1 = make_tuple(object, get<1>(p1));
};

void Textures::swapVelocities() {
    GLuint object = get<0>(v0);
    v0 = make_tuple(get<0>(v1), get<1>(v0));
    v1 = make_tuple(object, get<1>(v1));
};
