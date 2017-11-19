//
//  utility.h
//  OpenGL
//
//  Created by Hai Nguyen on 11/15/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef utility_h
#define utility_h
extern void setBasePathForResources(const char *basePath);
extern GLuint loadShader(const GLenum type, const char *filePath);
extern GLuint loadTexture(const GLsizei width, const GLsizei height, const GLenum type, const GLvoid *pixels);
extern void linkProgram(const GLuint program);
#endif /* utility_h */
