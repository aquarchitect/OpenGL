//
//  cube.h
//  Demo-iOS
//
//  Created by Hai Nguyen on 11/15/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef cube_h
#define cube_h
#include "common.h"
typedef enum {
    VertexAttribPosition = 0,
    VertexAttribColor,
    VertexAttribTexCoord,
    VertexAttribNormal
} VertexAttributes;
typedef struct {
    GLfloat position[3];
    GLfloat color[4];
    GLfloat texCoord[2];
    GLfloat normal[3];
} Vertex;

extern GLfloat transformationMatrix[16];
extern GLfloat projectionMatrix[16];
extern void setFacadeImage(const GLsizei width, const GLsizei height, const GLenum type, const GLvoid *pixels);
#endif /* cube_h */
