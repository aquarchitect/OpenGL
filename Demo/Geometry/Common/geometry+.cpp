//
//  geometry+.cpp
//  OpenGL
//
//  Created by Hai Nguyen on 11/20/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#define GLM_ENABLE_EXPERIMENTAL

#include "geometry.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

static Geometry                 *pCube;
static mat4                projection;

void setupCube(float screenRatio, char *basePath) {
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
    
    pCube = new Geometry(basePath, vertices, indices);
    projection = perspective(radians(85.0f), screenRatio, 0.1f, 100.0f);
};

quat toQuaternion(float pitch, float roll, float yaw)
{
    quat q;
    // Abbreviations for the various angular functions
    float cy = cos(yaw * 0.5);
    float sy = sin(yaw * 0.5);
    float cr = cos(roll * 0.5);
    float sr = sin(roll * 0.5);
    float cp = cos(pitch * 0.5);
    float sp = sin(pitch * 0.5);
    
    q.w = cy * cr * cp + sy * sr * sp;
    q.x = cy * sr * cp - sy * cr * sp;
    q.y = cy * cr * sp + sy * sr * cp;
    q.z = sy * cr * cp - cy * sr * sp;
    return q;
}

void moveCamera(float pitch, float yaw, float roll) {
//    vec3 position;
//    position.x = distance * sin(yaw) * cos(pitch);
//    position.y = distance * sin(pitch);
//    position.z = distance * cos(yaw) * cos(pitch);
    
    quat quat = toQuaternion(yaw, pitch, 0.0);
    vec3 position = rotate(quat, vec3(0.0,0.0,5.0));
    
    vec3 up(0.0f, 1.0f, 0.0f);
    
    mat4 model(1.0f);
    model = translate(model, vec3(0.0,1.0,0.0));
    
    mat4 world(1.0f);
    mat4 view = lookAt(position, vec3(0.0), up);
    
    pCube->draw(model, world, view, projection);
};

void loadCubeTexture(int width, int height, void *pixels) {
    pCube->loadTexture(width, height, pixels);
};
