//
//  geometry.cpp
//  Geometry-iOS
//
//  Created by Hai Nguyen on 11/20/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "geometry.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace utility;

void Geometry::loadTexture(GLsizei width, GLsizei height, GLvoid *pixels) {
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
};

Geometry::Geometry(string basePath, vector<Vertex> vertices, vector<GLubyte> indices) {
    this->vertices = vertices;
    this->indices = indices;
    
    linkShaders(basePath + "/geometry", program);
    
    modelUniformLocation = glGetUniformLocation(program, "uModel");
    worldUniformLocation = glGetUniformLocation(program, "uWorld");
    viewUniformLocation = glGetUniformLocation(program, "uView");
    projectionUniformLocation = glGetUniformLocation(program, "uProjection");
    textureUniformLocation = glGetUniformLocation(program, "uTexture");
    
#if GL_APPLE_vertex_array_object
    glGenVertexArraysAPPLE(1, &VAO);
    glBindVertexArrayAPPLE(VAO);
#elif GL_OES_vertex_array_object
    glGenVertexArraysOES(1, &VAO);
    glBindVertexArrayOES(VAO);
#endif
    
    glGenBuffers(GLsizei(sizeof(VBOs)/sizeof(GLuint)), VBOs);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLubyte), &indices.front(), GL_STATIC_DRAW);
    
    GLuint positionAttributeLocation = glGetAttribLocation(program, "aPosition");
    glEnableVertexAttribArray(positionAttributeLocation);
    glVertexAttribPointer(positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, position));
    
    GLuint colorAttributeLocation = glGetAttribLocation(program, "aColor");
    glEnableVertexAttribArray(colorAttributeLocation);
    glVertexAttribPointer(colorAttributeLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, color));
    
    GLuint texCoordAttributeLocation = glGetAttribLocation(program, "aTexCoord");
    glEnableVertexAttribArray(texCoordAttributeLocation);
    glVertexAttribPointer(texCoordAttributeLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, texCoord));
    
    GLuint normalAttributeLocation = glGetAttribLocation(program, "aNormal");
    glEnableVertexAttribArray(normalAttributeLocation);
    glVertexAttribPointer(normalAttributeLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, normal));
    
#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(0);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(0);
#endif
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
};

void Geometry::draw(mat4 model, mat4 world, mat4 view, mat4 projection) {
    glUseProgram(program);
    
    glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, value_ptr(model));
    glUniformMatrix4fv(worldUniformLocation, 1, GL_FALSE, value_ptr(world));
    glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, value_ptr(view));
    glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, value_ptr(projection));
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureUniformLocation, 0); // 0 is corresponded with the texture slot
    
#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(VAO);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(VAO);
#endif
    
    // TODO: why the last value is 0 instead of the indices pointer.
    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_BYTE, 0);
    
#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(0);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(0);
#endif
    
    glBindTexture(GL_TEXTURE_2D, 0);
};
