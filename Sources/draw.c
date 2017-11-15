//
//  draw.c
//  OpenGL
//
//  Created by Hai Nguyen on 11/14/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#if __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
        #include <OpenGLES/ES2/gl.h>
    #elif TARGET_OS_MAC
        #include <OpenGL/gl.h>
        #include <OpenGL/glu.h>
        #include <GLUT/glut.h>
    #else
        #error "Unknown Apple Plaform"
    #endif
#endif

extern void attachShader(GLuint program, GLenum type, const char *filePath);

const char        *g_base_path;
static GLuint      g_program;
static const char  g_fragment_file_name[] = "sample.fsh";
static const char  g_vertex_file_name[]   = "sample.vsh";

void setup() {
    fprintf(stderr, "%s\n", g_base_path);
    g_program = glCreateProgram();
    
    // attach fragment shader file
    char *fragmentFilePath = malloc(strlen(g_base_path) + strlen(g_fragment_file_name) + 1);
    strcat(fragmentFilePath, g_base_path);
    strcat(fragmentFilePath, g_fragment_file_name);
    attachShader(g_program, GL_FRAGMENT_SHADER, fragmentFilePath);
    free(fragmentFilePath);
    
    // attach vertext shader file
    char *vertexFilePath = malloc(strlen(g_base_path) + strlen(g_vertex_file_name) + 1);
    strcat(vertexFilePath, g_base_path);
    strcat(vertexFilePath, g_vertex_file_name);
    attachShader(g_program, GL_VERTEX_SHADER, vertexFilePath);
    free(vertexFilePath);
    
    GLint result, length;
    glLinkProgram(g_program);
    glGetProgramiv(g_program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        char *log;
        
        // get the program info log
        glGetProgramiv(g_program, GL_INFO_LOG_LENGTH, &length);
        log = malloc(length);
        glGetProgramInfoLog(g_program, length, &result, log);
        fprintf(stderr, "setup(): Unable to link program %s.\n", log);
        free(log);
        
        glDeleteProgram(g_program);
        g_program = 0;
    }
}

void draw(void) {
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    //glUseProgram(g_program);
}


