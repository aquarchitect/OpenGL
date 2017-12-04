//
//  draw.hpp
//  OpenGL
//
//  Created by Hai Nguyen on 11/20/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef draw_hpp
#define draw_hpp

#ifdef __cplusplus
extern "C" {
#endif
    extern void setupCube(float screenRatio, char *basePath);
    extern void rotateCube(float xAngle, float yAngle, float zAngle);
    
    extern void loadCubeTexture(int width, int height, void *pixels);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* draw_hpp */
