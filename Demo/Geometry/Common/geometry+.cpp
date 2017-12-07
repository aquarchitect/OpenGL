//
//  geometry+.cpp
//  OpenGL
//
//  Created by Hai Nguyen on 11/20/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "geometry.h"
#include <glm/gtc/matrix_transform.hpp>

static Geometry                 *pCube;

static glm::mat4                lastTransformation;
static glm::mat4                constPerspective;

void setupCube(float screenRatio, char *basePath) {
    std::vector<Geometry::Vertex> vertices = {
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
    
    std::vector<GLubyte> indices = {
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
    
    lastTransformation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -5.0));
    constPerspective = glm::perspective(glm::radians(85.0f), screenRatio, 1.0f, 150.0f);
};

void rotateCube(float xAngle, float yAngle, float zAngle) {
    lastTransformation = glm::rotate(lastTransformation, glm::pi<float>() * xAngle, glm::vec3(1.0, 0.0, 0.0)); // rotate x-axis
    lastTransformation = glm::rotate(lastTransformation, glm::pi<float>() * yAngle, glm::vec3(0.0, 1.0, 0.0)); // rotate y-axis
    lastTransformation = glm::rotate(lastTransformation, glm::pi<float>() * zAngle, glm::vec3(0.0, 0.0, 1.0)); // rotate z-axis
    
    pCube->draw(lastTransformation, constPerspective);
};

void loadCubeTexture(int width, int height, void *pixels) {
    pCube->loadTexture(width, height, pixels);
};
