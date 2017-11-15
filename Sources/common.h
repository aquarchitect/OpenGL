//
//  common.h
//  OpenGL
//
//  Created by Hai Nguyen on 11/14/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef common_h
#define common_h
#if __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
        #include <OpenGLES/ES2/gl.h>
        #include <OpenGLES/ES2/glext.h>
    #elif TARGET_OS_MAC
        #include <OpenGL/gl.h>
        #include <OpenGL/glu.h>
        #include <GLUT/glut.h>
    #else
        #error "Unknown Apple Plaform"
    #endif
#endif
#endif /* common_h */
