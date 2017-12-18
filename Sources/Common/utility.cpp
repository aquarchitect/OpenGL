//
//  utility.cpp
//  OpenGL
//
//  Created by Hai Nguyen on 11/20/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "utility.hpp"
#include <vector>
#include <fstream>

GLuint Utility::loadShader(GLenum type, string filePath) {
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
}

void Utility::linkShaders(string basePath, GLuint program) {
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
}
