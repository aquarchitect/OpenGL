//
//  draw.h
//  OpenGL
//
//  Created by Hai Nguyen on 11/14/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef draw_h
#define draw_h
#include "cube.h"
extern void setup(void);

extern void setCubeProjection(const GLfloat matrix[16]);
extern void setCubeTexture(const GLsizei width, const GLsizei height, const GLenum type, const GLvoid *pixels);
extern void drawCube(const GLfloat transformation[16]);
#endif /* draw_h */
