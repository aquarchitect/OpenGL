//
//  utility.cpp
//  OpenGL
//
//  Created by Hai Nguyen on 11/20/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "utility.hpp"
#include <fstream>

static GLuint loadShader(GLenum type, string filePath) {
    // read shader code from file path
    string shaderCodes;
    ifstream fileStream(filePath, ios::in);
    
    if (fileStream.is_open()) {
        string line = "";
        while (getline(fileStream, line)) shaderCodes += line + "\n";
        fileStream.close();
    }
    
    // compile shader codes
    GLuint shaderID = glCreateShader(type);
    char const * shaderCodesPointer = shaderCodes.c_str();
    glShaderSource(shaderID, 1, &shaderCodesPointer, NULL);
    glCompileShader(shaderID);

    // check the result
    GLint result;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
    
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
        vector<char> log(length + 1);
        glGetShaderInfoLog(shaderID, length, NULL, &log[0]);
        
        printf("ERROR: Unable to load shader %s.\n", filePath.c_str());
        printf("%s\n", &log[0]);
        exit(EXIT_FAILURE);
    }
    
    return shaderID;
};

void utility::linkShaders(string basePath, GLuint program) {
    GLuint vertexShaderID = loadShader(GL_VERTEX_SHADER, basePath + ".vsh");
    GLuint fragmentShaderID = loadShader(GL_FRAGMENT_SHADER, basePath + ".fsh");
    
    glAttachShader(program, vertexShaderID);
    glAttachShader(program, fragmentShaderID);
    glLinkProgram(program);
    
    GLint result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        vector<char> log(length + 1);
        glGetProgramInfoLog(program, length, NULL, &log[0]);
        
        printf("ERROR: Unable to link program %i.\n", program);
        printf("%s\n", &log[0]);
        exit(EXIT_FAILURE);
    }
    
    glDetachShader(program, vertexShaderID);
    glDetachShader(program, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
};

quat utility::convertToQuat(float pitch, float roll, float yaw) {
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
};

vector<char> utility::loadBytes(string basePath) {
    ifstream ifs(basePath, ios::binary | ios::ate);
    ifstream::pos_type position = ifs.tellg();
    vector<char> result(position);
    
    ifs.seekg(0, ios::beg);
    ifs.read(result.data(), position);
    
    return result;
};

mesh utility::createMesh(int rows, int columns) {
    vector<vec2> vertices = vector<vec2>(rows * columns);
    vector<int> indexes = vector<int>((rows - 1) * 2 * (columns + 1));
    
    for (int i = 0; i < rows; i++) {
        indexes[i * 2 * (columns + 1)] = i * columns;
        
        for (int j = 0; j < columns; j++) {
            vertices[i * columns + j] = {float(i) / float(rows - 1), float(j) / float(columns - 1)};
            
            indexes[i * 2 * (columns + 1) + 1 + 2 * j] = i * columns + j;
            indexes[i * 2 * (columns + 1) + 2 + 2 * j] = (i + 1) * columns + j;
        }
        
        indexes[(i + 1) * 2 * (columns + 1) - 1] = (i + 2) * columns - 1;
    }
    
    return {vertices, indexes};
};
