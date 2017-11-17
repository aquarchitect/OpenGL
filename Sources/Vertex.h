//
//  Vertex.h
//  OpenGL
//
//  Created by Hai Nguyen on 11/14/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef Vertex_h
#define Vertex_h
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
#endif /* Vertex_h */
