//
//  renderer.hpp
//  OpenGL
//
//  Created by Hai Nguyen on 11/20/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef renderer_hpp
#define renderer_hpp

#ifdef __cplusplus
extern "C" {
#endif
    extern void setup(float width, float height, char *basePath);
    extern void translate(float x, float y, float z);
    
    extern void loadTexture(int width, int height, void *pixels);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* renderer_hpp */
