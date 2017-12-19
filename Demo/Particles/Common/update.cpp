//
//  update.cpp
//  Particles-iOS
//
//  Created by Hai Nguyen on 12/18/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "update.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Utility;

tuple<GLubyte, GLubyte> Update::encode(GLfloat value, GLfloat scale) {
    value = value * scale + base * base / 2;
    
    GLubyte firstByte = floorf(fmod(value, base) / base * 255);
    GLubyte secondByte = floorf(floorf(value / base) / base * 255);
    
    return make_tuple(firstByte, secondByte);
};

GLfloat Update::decode(tuple<GLubyte, GLubyte> bytes, GLfloat scale) {
    GLubyte firstByte = get<0>(bytes);
    GLubyte secondByte = get<1>(bytes);
    
    return ((firstByte / 255 * base) + (secondByte / 255 * base * base) - base * base / 2) / scale;
};

GLuint Update::createTexture(GLuint slot, GLvoid *pixels) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)grid.x, (GLsizei)grid.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    
    return textureID;
};

Update::Update(string basePath, vec2 grid, vec2 resolution) {
    this->grid = grid;
    
    // scale
    float scale = floorf(base * base / fmax(resolution.x, resolution.y) / 3.0); // TODO: not yet understand the factor of 3
    this->scale = vec2(scale, scale * 100);
    
    RGBA rgbaP0[int(grid.x * grid.y)];
    RGBA rgbaV0[int(grid.x * grid.y)];
    
    for (int j = 0; j < grid[1]; j++) {     // y
        for (int i = 0; i < grid[0]; i++) { // x
            int index = j * int(grid[0]) + i;
            
            BytePair rgP0Bytes = encode(rand() + resolution.x, this->scale.x);
            BytePair baP0Bytes = encode(rand() + resolution.y, this->scale.x);
            
            rgbaP0[index] = {
                get<0>(rgP0Bytes),  // r
                get<1>(rgP0Bytes),  // g
                get<0>(baP0Bytes),  // b
                get<1>(baP0Bytes)   // a
            };
            
            BytePair rgV0Bytes = encode(rand() * 1.0 - 0.5, this->scale.y);
            BytePair baV0Bytes = encode(rand() * 2.5, this->scale.y);
            
            rgbaV0[index] = {
                get<0>(rgV0Bytes),  // r
                get<1>(rgV0Bytes),  // g
                get<0>(baV0Bytes),  // b
                get<1>(baV0Bytes)   // a
            };
        };
    };
    
    this->textures.p0 = createTexture(0, rgbaP0);
    this->textures.v0 = createTexture(1, rgbaV0);
    this->textures.p1 = createTexture(2, NULL);
    this->textures.v1 = createTexture(3, NULL);

    linkShaders(basePath + "/update", program);
    
    scaleUniformLocation = glGetUniformLocation(program, "uScale");
    
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

void Update::draw() {
    glUseProgram(program);
    
    glUniform2fv(scaleUniformLocation, 1, value_ptr(scale));
    
    glBindTexture(GL_TEXTURE_2D, textures.p0);
    glUniform1i(textures.p0, 0); // slot 0
    
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
};
