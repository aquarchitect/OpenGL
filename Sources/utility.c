//
//  shader.c
//  OpenGL
//
//  Created by Hai Nguyen on 11/14/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include "common.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static char *g_BasePath;

void setBasePathForResources(const char *basePath) {
    g_BasePath = malloc(strlen(basePath) + 1);
    strcpy(g_BasePath, basePath);
}

// Returns a string containing the content of a vertext/fragment shader file.
static char *loadFile(const char *filePath) {
    const size_t blockSize = 512;
    FILE *file;
    
    char buffer[blockSize];
    char *source = NULL;
    
    size_t currLength, totalLength = 0;
    
    // open file; terminate if NULL or empty
    file = fopen(filePath, "r");
    assert(file); // unable to open the file
    
    // read the file into a string
    while ((currLength = fread(buffer, 1, blockSize, file)) > 0) {
        char *_source = malloc(totalLength + currLength + 1);

        if (source) {
            memcpy(_source, source, totalLength);
            free(source);
        }

        memcpy(_source + totalLength, buffer, currLength);
        
        source = _source;
        totalLength += currLength;
    }

    // close file and terminate the string
    fclose(file);
    if (source) source[totalLength] = '\0';
    
    return source;
}

// Returns a shader object containing a shader compiled from a given GLSL file.
void attachShader(GLuint program, GLenum type, const char *filePath) {
    char fullPath[strlen(g_BasePath) + strlen(filePath) + 1];
    strcpy(fullPath, g_BasePath);
    strcat(fullPath, filePath);
    
    // get shader source
    char *source = loadFile(fullPath);
    if (!source) return;
    
    GLuint shader = (GLuint)glCreateShader(type);
    GLint length = (GLint)strlen(source);
    
    // create shader, set the source, and compile
    glShaderSource(shader, 1, (const char **)&source, &length);
    glCompileShader(shader);
    free(source);
 
    // make sure compiling successfully
    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        char *log;
        
        // get the shader info log
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        log = malloc(length);
        glGetShaderInfoLog(shader, length, &result, log);
        fprintf(stderr, "compileShader(): Unable to compile %s: %s.\n", filePath, log);
        free(log);
    } else {
        glAttachShader(program, shader);
    }
    
    glDeleteShader(shader);
    assert(result == GL_TRUE);
}

void linkProgram(GLuint program) {
    GLint result, length;
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        char *log;
        
        // get the program info log
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        log = malloc(length);
        glGetProgramInfoLog(program, length, &result, log);
        fprintf(stderr, "setup(): Unable to link program %s.\n", log);
        free(log);
        
        glDeleteProgram(program);
    }
    
    assert(result == GL_TRUE);
}
