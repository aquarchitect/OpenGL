//
//  geometry.cpp
//  OpenGL
//
//  Created by Hai Nguyen on 11/20/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "geometry.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum AttributeLayout {
    ATTRIBUTE_POSITION = 0,
    ATTRIBUTE_COLOR,
    ATTRIBUTE_TEXCOORD,
    ATTRIBUTE_COORD
};

Geometry::Geometry(std::string basePath, std::vector<Vertex> vertices, std::vector<GLubyte> indices) {
    this->vertices = vertices;
    this->indices = indices;
    
    GLuint vertextShaderID = Utility::loadShader(GL_VERTEX_SHADER, basePath + "geometry.vsh");
    GLuint fragmentShaderID = Utility::loadShader(GL_FRAGMENT_SHADER, basePath + "geometry.fsh");
    
    glBindAttribLocation(programID, ATTRIBUTE_POSITION, "aPosition");
    glBindAttribLocation(programID, ATTRIBUTE_COLOR, "aColor");
    glBindAttribLocation(programID, ATTRIBUTE_TEXCOORD, "aTexCoord");
    
    Utility::linkShaders(vertextShaderID, fragmentShaderID, programID);
    
    projectionUniformLocation = glGetUniformLocation(programID, "uProjection");
    transformationUniformLocation = glGetUniformLocation(programID, "uTransformation");
    textureUniformLocation = glGetUniformLocation(programID, "uTexture");
    
#if GL_APPLE_vertex_array_object
    glGenVertexArraysAPPLE(1, &vertexArrayObject);
    glBindVertexArrayAPPLE(vertexArrayObject);
#elif GL_OES_vertex_array_object
    glGenVertexArraysOES(1, &vertexArrayObject);
    glBindVertexArrayOES(vertexArrayObject);
#endif
    
    glGenBuffers((GLsizei)sizeof(bufferObjects)/sizeof(GLuint), bufferObjects);
    glBindBuffer(GL_ARRAY_BUFFER, bufferObjects[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObjects[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLubyte), &indices.front(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(ATTRIBUTE_POSITION);
    glVertexAttribPointer(ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, position));
    
    glEnableVertexAttribArray(ATTRIBUTE_COLOR);
    glVertexAttribPointer(ATTRIBUTE_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, color));
    
    glEnableVertexAttribArray(ATTRIBUTE_TEXCOORD);
    glVertexAttribPointer(ATTRIBUTE_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, texCoord));
    
#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(0);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(0);
#endif
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
};

void Geometry::draw(glm::mat4 transformation, glm::mat4 projection) {
    glClearColor(1., 0., 0., 1.);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(programID);
    
    glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(transformationUniformLocation, 1, GL_FALSE, glm::value_ptr(transformation));
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureObject);
    glUniform1i(textureUniformLocation, 0); // 0 is corresponded with the texture slot
    
#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(vertexArrayObject);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(vertexArrayObject);
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
    glGenTextures(1, &textureObject);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureObject);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
};
