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
    
    Utility::linkShaders(vertextShaderID, fragmentShaderID, programID);
    
    projectionUniformLocation = glGetUniformLocation(programID, "uProjection");
    transformationUniformLocation = glGetUniformLocation(programID, "uTransformation");
    
    glGenBuffers(1, &vertexArrayObject);
    glBindVertexArrayOES(vertexArrayObject);
    
    // generate vertex buffer
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices.front(), GL_STATIC_DRAW);
    
    // generate index buffer
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLubyte), &indices.front(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(ATTRIBUTE_POSITION);
    glVertexAttribPointer(ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, position));
    
    glEnableVertexAttribArray(ATTRIBUTE_COLOR);
    glVertexAttribPointer(ATTRIBUTE_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, color));
    
    glBindVertexArrayOES(0);
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
    
    glBindVertexArrayOES(vertexArrayObject);
    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_BYTE, &indices.front());
    glBindVertexArrayOES(0);
};
