//
//  sample.h
//  Demo-iOS
//
//  Created by Hai Nguyen on 11/15/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef sample_h
#define sample_h
#include "common.h"
extern GLfloat transformationMatrix[16];
extern GLfloat projectionMatrix[16];
extern void setFacadeImage(const GLsizei width, const GLsizei height, const GLenum type, const GLvoid *pixels);
#endif /* sample_h */
