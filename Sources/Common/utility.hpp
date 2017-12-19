//
//  utility.hpp
//  OpenGL
//
//  Created by Hai Nguyen on 11/20/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef utility_hpp
#define utility_hpp

#define GLM_ENABLE_EXPERIMENTAL

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
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace std;
using namespace glm;

namespace Utility {
    void    linkShaders(string basePath, GLuint program);
    quat    euler2Quat(float pitch, float roll, float yaw);
}
#endif /* utility_hpp */
