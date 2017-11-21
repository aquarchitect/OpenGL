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
    extern void setup(const float width, const float height, char *basePath);
    extern void translate(const float x, const float y, const float z);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* renderer_hpp */
