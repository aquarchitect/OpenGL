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
    VertexAttribColor
} VertexAttributes;
typedef struct {
    GLfloat Position[3];
    GLfloat Color[4];
} Vertex;
#endif /* Vertex_h */
