//
//  geometry.cpp
//  OpenGL
//
//  Created by Hai Nguyen on 11/20/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "geometry.hpp"
#include <glm/gtc/matrix_transform.hpp>

Geometry::Geometry(std::string basePath, GLfloat *projection, Vertex *vertices) {
    this->pVertices = &(*vertices);
    this->pProjection = &(*projection);
    
    GLuint vertextShaderID = Utility::loadShader(GL_VERTEX_SHADER, basePath + "geometry.vsh");
    GLuint fragmentShaderID = Utility::loadShader(GL_FRAGMENT_SHADER, basePath + "geometry.fsh");
    
    glBindAttribLocation(programID, (Attribute)position, "a_Position");
    glBindAttribLocation(programID, (Attribute)color, "a_Color");
    glBindAttribLocation(programID, (Attribute)texCoord, "a_TexCoord");
    glBindAttribLocation(programID, (Attribute)normal, "a_Normal");
    
    Utility::linkShaders(vertextShaderID, fragmentShaderID, programID);
    
    this->transformationUniformID = glGetUniformLocation(programID, "u_Transformation");
    this->textureUniformID = glGetUniformLocation(programID, "u_Texture");
    this->projectionUniformID = glGetUniformLocation(programID, "u_Projection");
    
#if GL_APPLE_vertex_array_object
    glGenVertexArraysAPPLE(1, &vertexArrayObjectID);
    glBindVertexArrayAPPLE(vertexArrayObjectID);
#elif GL_OES_vertex_array_object
    glGenVertexArraysOES(1, &vertexArrayObjectID);
    glBindVertexArrayOES(vertexArrayObjectID);
#endif
    
    // generate vertext buffer
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray((Attribute)position);
    glVertexAttribPointer((Attribute)position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, position));
    
    glEnableVertexAttribArray((Attribute)color);
    glVertexAttribPointer((Attribute)color, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, color));
    
    glEnableVertexAttribArray((Attribute)texCoord);
    glVertexAttribPointer((Attribute)texCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, texCoord));

    glEnableVertexAttribArray((Attribute)normal);
    glVertexAttribPointer((Attribute)normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, normal));
    
#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(0);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(0);
#endif
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Geometry::draw(GLfloat *pTransformation) {
    glClearColor(1., 0., 0., 1.);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(programID);
    
    this->pTransformation = pTransformation;
    glUniformMatrix4fv(transformationUniformID, 1, GL_FALSE, pTransformation);
    glUniformMatrix4fv(projectionUniformID, 1, GL_FALSE, pProjection);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureBuffer);
    glUniform1i(textureUniformID, 1);
    
#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(vertexArrayObjectID);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(vertexArrayObjectID);
#endif
    glDrawArrays(GL_TRIANGLES, 0, 3);
#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(0);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(0);
#endif
};
