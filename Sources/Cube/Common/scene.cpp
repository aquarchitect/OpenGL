//
//  scene.cpp
//  Geometry-iOS
//
//  Created by Hai Nguyen on 11/20/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "scene.hpp"

using namespace utility;

scene::scene(string basePath, vec2 screenResolution) {
    this->basePath = basePath;
    this->pCube = NULL;
    this->screenResolution = screenResolution;
};

void scene::loadCubeTexture(GLsizei width, GLsizei height, GLvoid *pixels) {
    vector<mesh::vertex> vertices = {
        // Front
        {{ 1, -1, 1}, {0, 0, 1}, {1, 0}}, // 0
        {{ 1,  1, 1}, {0, 0, 1}, {1, 1}}, // 1
        {{-1,  1, 1}, {0, 0, 1}, {0, 1}}, // 2
        {{-1, -1, 1}, {0, 0, 1}, {0, 0}}, // 3
        
        // Back
        {{-1, -1, -1}, {0, 0, -1}, {1, 0}}, // 4
        {{-1,  1, -1}, {0, 0, -1}, {1, 1}}, // 5
        {{ 1,  1, -1}, {0, 0, -1}, {0, 1}}, // 6
        {{ 1, -1, -1}, {0, 0, -1}, {0, 0}}, // 7
        
        // Left
        {{-1, -1,  1}, {-1, 0, 0}, {1, 0}}, // 8
        {{-1,  1,  1}, {-1, 0, 0}, {1, 1}}, // 9
        {{-1,  1, -1}, {-1, 0, 0}, {0, 1}}, // 10
        {{-1, -1, -1}, {-1, 0, 0}, {0, 0}}, // 11
        
        // Right
        {{1, -1, -1}, {1, 0, 0}, {1, 0}}, // 12
        {{1,  1, -1}, {1, 0, 0}, {1, 1}}, // 13
        {{1,  1,  1}, {1, 0, 0}, {0, 1}}, // 14
        {{1, -1,  1}, {1, 0, 0}, {0, 0}}, // 15
        
        // Top
        {{ 1, 1,  1}, {0, 1, 0}, {1, 0}}, // 16
        {{ 1, 1, -1}, {0, 1, 0}, {1, 1}}, // 17
        {{-1, 1, -1}, {0, 1, 0}, {0, 1}}, // 18
        {{-1, 1,  1}, {0, 1, 0}, {0, 0}}, // 19
        
        // Bottom
        {{ 1, -1, -1}, {0, -1, 0}, {1, 0}}, // 20
        {{ 1, -1,  1}, {0, -1, 0}, {1, 1}}, // 21
        {{-1, -1,  1}, {0, -1, 0}, {0, 1}}, // 22
        {{-1, -1, -1}, {0, -1, 0}, {0, 0}}, // 23
    };
    
    vector<GLubyte> indices = {
        // Front
        0, 1, 2,
        2, 3, 0,
        
        // Back
        4, 5, 6,
        6, 7, 4,
        
        // Left
        8, 9, 10,
        10, 11, 8,
        
        // Right
        12, 13, 14,
        14, 15, 12,
        
        // Top
        16, 17, 18,
        18, 19, 16,
        
        // Bottom
        20, 21, 22,
        22, 23, 20
    };
    
    texture texture = createTexture(1, {width, height}, pixels);
    this->pCube = new mesh(basePath, vertices, indices, texture);
};

void scene::draw() {
    GLfloat ratio = GLfloat(screenResolution.x) / GLfloat(screenResolution.y);
    vec3 position(0.0f, 0.0f, 5.0f);
    vec3 up(0.0f, 1.0f, 0.0f);
    
    mat4 model = translate(mat4(1.0), vec3(0.0, 0.0, -5.0));
    mat4 world(1.0f);
    mat4 view = lookAt(position, vec3(0.0), up);
    mat4 projection = perspective(radians(45.0f), ratio, 0.1f, 100.0f);
    
    mesh::light light = {vec3(1.0), vec3(0.0, 0.0, -1.0), 0.1, 0.8, 0.0};
    
    glViewport(0, 0, screenResolution.x, screenResolution.y);
    glClearColor(0., 0., 0., 1.);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    pCube->draw(light, model, world, view, projection);
};
