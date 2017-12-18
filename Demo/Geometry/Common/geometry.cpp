//
//  geometry.cpp
//  OpenGL
//
//  Created by Hai Nguyen on 11/20/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "geometry.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Utility;

Geometry::Geometry(string basePath, vec2 resolution, vector<Vertex> vertices, vector<GLubyte> indices) {
    this->vertices = vertices;
    this->indices = indices;
    this->resolution = resolution;
    
    linkShaders(basePath + "/geometry", programID);
    
    modelUniformLocation = glGetUniformLocation(programID, "uModel");
    worldUniformLocation = glGetUniformLocation(programID, "uWorld");
    viewUniformLocation = glGetUniformLocation(programID, "uView");
    projectionUniformLocation = glGetUniformLocation(programID, "uProjection");

    textureUniformLocation = glGetUniformLocation(programID, "uTexture");
    
#if GL_APPLE_vertex_array_object
    glGenVertexArraysAPPLE(1, &VAO);
    glBindVertexArrayAPPLE(VAO);
#elif GL_OES_vertex_array_object
    glGenVertexArraysOES(1, &VAO);
    glBindVertexArrayOES(VAO);
#endif
    
    glGenBuffers(GLsizei(sizeof(buffers)/sizeof(GLuint)), buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLubyte), &indices.front(), GL_STATIC_DRAW);
    
    GLuint positionAttributeLocation = glGetAttribLocation(programID, "aPosition");
    glEnableVertexAttribArray(positionAttributeLocation);
    glVertexAttribPointer(positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, position));
    
    GLuint colorAttributeLocation = glGetAttribLocation(programID, "aColor");
    glEnableVertexAttribArray(colorAttributeLocation);
    glVertexAttribPointer(colorAttributeLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, color));
    
    GLuint texCoordAttributeLocation = glGetAttribLocation(programID, "aTexCoord");
    glEnableVertexAttribArray(texCoordAttributeLocation);
    glVertexAttribPointer(texCoordAttributeLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, texCoord));
    
    GLuint normalAttributeLocation = glGetAttribLocation(programID, "aNormal");
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
    glViewport(0, 0, resolution[0], resolution[1]);
    
    glClearColor(0., 0., 0., 1.);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(programID);
    
    glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, value_ptr(model));
    glUniformMatrix4fv(worldUniformLocation, 1, GL_FALSE, value_ptr(world));
    glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, value_ptr(view));
    glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, value_ptr(projection));
    
    glActiveTexture(GL_TEXTURE0);
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

void Geometry::loadTexture(GLsizei width, GLsizei height, GLvoid *pixels) {
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
};
