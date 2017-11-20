//
//  effect.h
//  OpenGL
//
//  Created by Hai Nguyen on 11/18/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef effect_h
#define effect_h
#include "common.h"
#include "size.h"
extern void loadEffectShader(const GLuint program);
extern void drawEffectShader(const GLuint program, const Size resolution);
#endif /* effect_h */
