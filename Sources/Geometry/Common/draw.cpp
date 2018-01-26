//
//  draw.cpp
//  Geometry-iOS
//
//  Created by Hai Nguyen on 11/20/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "draw.h"
#include "utility.hpp"
#include "geometry.hpp"
#include <glm/gtc/matrix_transform.hpp>

using namespace utility;

static Geometry     *pCube;
static vec2         resolution;

static void setup(char *basePath, int width, int height) {
    vector<Geometry::Vertex> vertices = {
        // Front
        {{ 1, -1, 1}, {1, 0, 0, 1}, {1, 0}, {0, 0, 1}}, // 0
        {{ 1,  1, 1}, {0, 1, 0, 1}, {1, 1}, {0, 0, 1}}, // 1
        {{-1,  1, 1}, {0, 0, 1, 1}, {0, 1}, {0, 0, 1}}, // 2
        {{-1, -1, 1}, {0, 0, 0, 1}, {0, 0}, {0, 0, 1}}, // 3
        
        // Back
        {{-1, -1, -1}, {0, 0, 1, 1}, {1, 0}, {0, 0, -1}}, // 4
        {{-1,  1, -1}, {0, 1, 0, 1}, {1, 1}, {0, 0, -1}}, // 5
        {{ 1,  1, -1}, {1, 0, 0, 1}, {0, 1}, {0, 0, -1}}, // 6
        {{ 1, -1, -1}, {0, 0, 0, 1}, {0, 0}, {0, 0, -1}}, // 7
        
        // Left
        {{-1, -1,  1}, {1, 0, 0, 1}, {1, 0}, {-1, 0, 0}}, // 8
        {{-1,  1,  1}, {0, 1, 0, 1}, {1, 1}, {-1, 0, 0}}, // 9
        {{-1,  1, -1}, {0, 0, 1, 1}, {0, 1}, {-1, 0, 0}}, // 10
        {{-1, -1, -1}, {0, 0, 0, 1}, {0, 0}, {-1, 0, 0}}, // 11
        
        // Right
        {{1, -1, -1}, {1, 0, 0, 1}, {1, 0}, {1, 0, 0}}, // 12
        {{1,  1, -1}, {0, 1, 0, 1}, {1, 1}, {1, 0, 0}}, // 13
        {{1,  1,  1}, {0, 0, 1, 1}, {0, 1}, {1, 0, 0}}, // 14
        {{1, -1,  1}, {0, 0, 0, 1}, {0, 0}, {1, 0, 0}}, // 15
        
        // Top
        {{ 1, 1,  1}, {1, 0, 0, 1}, {1, 0}, {0, 1, 0}}, // 16
        {{ 1, 1, -1}, {0, 1, 0, 1}, {1, 1}, {0, 1, 0}}, // 17
        {{-1, 1, -1}, {0, 0, 1, 1}, {0, 1}, {0, 1, 0}}, // 18
        {{-1, 1,  1}, {0, 0, 0, 1}, {0, 0}, {0, 1, 0}}, // 19
        
        // Bottom
        {{ 1, -1, -1}, {1, 0, 0, 1}, {1, 0}, {0, -1, 0}}, // 20
        {{ 1, -1,  1}, {0, 1, 0, 1}, {1, 1}, {0, -1, 0}}, // 21
        {{-1, -1,  1}, {0, 0, 1, 1}, {0, 1}, {0, -1, 0}}, // 22
        {{-1, -1, -1}, {0, 0, 0, 1}, {0, 0}, {0, -1, 0}}, // 23
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
    
    resolution = {width, height};
    pCube = new Geometry(basePath, vertices, indices);
}

void setup(char *basePath, int resolution[2]) {
    setup(basePath, resolution[0], resolution[1]);
};

void rotateCamera(float pitch, float yaw, float roll) {
    glViewport(0, 0, resolution[0], resolution[1]);
    
    glClearColor(0., 0., 0., 1.);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
//    vec3 position;
//    position.x = distance * sin(yaw) * cos(pitch);
//    position.y = distance * sin(pitch);
//    position.z = distance * cos(yaw) * cos(pitch);
    
    quat quat = convertToQuat(yaw, pitch, 0.0);
    vec3 position = rotate(quat, vec3(0.0,0.0,5.0));
    
    vec3 up(0.0f, 1.0f, 0.0f);
    
    mat4 model(1.0f);
    model = translate(model, vec3(0.0,1.0,0.0));
    
    mat4 world(1.0f);
    mat4 view = lookAt(position, vec3(0.0), up);
    
    GLfloat ratio = GLfloat(resolution[0]) / GLfloat(resolution[1]);
    mat4 projection = perspective(radians(85.0f), ratio, 0.1f, 100.0f);
    
    pCube->draw(model, world, view, projection);
};

void loadTexture(int width, int height, void *pixels) {
    pCube->loadTexture(width, height, pixels);
};
