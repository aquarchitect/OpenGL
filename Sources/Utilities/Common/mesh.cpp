//
//  mesh.cpp
//  OpenGL
//
//  Created by Hai Nguyen on 2/22/18.
//  Copyright © 2018 Hai Nguyen. All rights reserved.
//

#include "mesh.hpp"

mesh::mesh(string basePath, vector<vertex> vertices, vector<GLubyte> indices, struct texture texture) {
    this->indices = indices;
    this->texture = texture;
    
    linkShaders(basePath + "/mesh", program);
    
    modelUniformLocation = glGetUniformLocation(program, "uModel");
    worldUniformLocation = glGetUniformLocation(program, "uWorld");
    viewUniformLocation = glGetUniformLocation(program, "uView");
    projectionUniformLocation = glGetUniformLocation(program, "uProjection");
    textureUniformLocation = glGetUniformLocation(program, "uTexture");
    
    lightColorUniformLocation = glGetUniformLocation(program, "uLight.color");
    lightDirectionUniformLocation = glGetUniformLocation(program, "uLight.direction");
    lightAmbientUniformLocation = glGetUniformLocation(program, "uLight.ambient");
    lightDiffuseUniformLocation = glGetUniformLocation(program, "uLight.diffuse");
    lightSpecularUniformLocation = glGetUniformLocation(program, "uLight.specular");
    
#if GL_APPLE_vertex_array_object
    glGenVertexArraysAPPLE(1, &arrayBuffer);
    glBindVertexArrayAPPLE(arrayBuffer);
#elif GL_OES_vertex_array_object
    glGenVertexArraysOES(1, &arrayBuffer);
    glBindVertexArrayOES(arrayBuffer);
#endif
    
    glGenBuffers(1, &verticesBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices.front(), GL_STATIC_DRAW);
    
    glGenBuffers(1, &indicesBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLubyte), &indices.front(), GL_STATIC_DRAW);
    
    GLuint positionAttributeLocation = glGetAttribLocation(program, "aPosition");
    glEnableVertexAttribArray(positionAttributeLocation);
    glVertexAttribPointer(positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (const GLvoid *) offsetof(vertex, position));
    
    GLuint normalAttributeLocation = glGetAttribLocation(program, "aNormal");
    glEnableVertexAttribArray(normalAttributeLocation);
    glVertexAttribPointer(normalAttributeLocation, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (const GLvoid *) offsetof(vertex, normal));
    
    GLuint texCoordAttributeLocation = glGetAttribLocation(program, "aTexCoord");
    glEnableVertexAttribArray(texCoordAttributeLocation);
    glVertexAttribPointer(texCoordAttributeLocation, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (const GLvoid *) offsetof(vertex, texCoord));
};

void mesh::draw(light light, mat4 model, mat4 world, mat4 view, mat4 projection) {
    glUseProgram(program);
    
    glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, value_ptr(model));
    glUniformMatrix4fv(worldUniformLocation, 1, GL_FALSE, value_ptr(world));
    glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, value_ptr(view));
    glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, value_ptr(projection));
    
    glUniform3fv(lightColorUniformLocation, 1, value_ptr(light.color));
    glUniform3fv(lightDirectionUniformLocation, 1, value_ptr(light.direction));
    glUniform1f(lightAmbientUniformLocation, light.ambient);
    glUniform1f(lightDiffuseUniformLocation, light.diffuse);
    glUniform1f(lightSpecularUniformLocation, light.specular);
    
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glUniform1i(textureUniformLocation, texture.slot);
    
#if GL_APPLE_vertex_array_object
    glBindVertexArrayAPPLE(arrayBuffer);
#elif GL_OES_vertex_array_object
    glBindVertexArrayOES(arrayBuffer);
#endif
    
    glDrawElements(GL_TRIANGLES, GLsizei(indices.size()), GL_UNSIGNED_BYTE, 0);
};
