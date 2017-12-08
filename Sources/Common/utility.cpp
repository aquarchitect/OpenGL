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

GLuint Utility::loadShader(const GLenum type, const std::string filePath) {
    // read shader code from file path
    std::string shaderCodes;
    std::ifstream fileStream(filePath, std::ios::in);
    
    if (fileStream.is_open()) {
        std::string line = "";
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
        std::vector<char> log(length + 1);
        glGetShaderInfoLog(shaderID, length, NULL, &log[0]);
        
        printf("ERROR: Unable to load shader %s.\n", filePath.c_str());
        printf("%s\n", &log[0]);
        exit(EXIT_FAILURE);
    }
    
    return shaderID;
}

void Utility::linkShaders(const GLuint vertexShaderID, const GLuint fragmentShaderID, const GLuint programID) {
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);
    
    GLint result;
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> log(length + 1);
        glGetProgramInfoLog(programID, length, NULL, &log[0]);
        
        printf("ERROR: Unable to link program %i.\n", programID);
        printf("%s\n", &log[0]);
        exit(EXIT_FAILURE);
    }
    
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

