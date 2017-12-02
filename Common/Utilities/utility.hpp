//
//  utility.hpp
//  OpenGL
//
//  Created by Hai Nguyen on 11/20/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef utility_hpp
#define utility_hpp

#if __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
        #include <OpenGLES/ES2/gl.h>
        #include <OpenGLES/ES2/glext.h>
    #elif TARGET_OS_MAC
        #include <OpenGL/gl.h>
        #include <OpenGL/glext.h>
        #include <OpenGL/glu.h>
        #include <GLUT/glut.h>
    #else
        #error "Unknown Apple Plaform"
    #endif
#endif

#include <string>
namespace Utility {
    GLuint  loadShader(const GLenum type, const std::string filePath);
    void    linkShaders(const GLuint vertexShaderID, const GLuint fragmentShaderID, const GLuint programID);
}
#endif /* utility_hpp */
