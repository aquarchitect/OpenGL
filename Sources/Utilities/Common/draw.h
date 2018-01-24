//
//  draw.h
//  OpenGL
//
//  Created by Hai Nguyen on 12/18/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef draw_h
#define draw_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
    extern void setup(char *basePath, int resolution[2]);
    extern void draw(float deltaTime);

#if CUBE
    extern void loadTexture(int width, int height, void *pixels);
    extern void rotateCamera(float pitch, float yaw, float roll);
#endif

#if RAIN
    extern void addObstacle(int x, int y);
#endif
    
#if RIPPLE
    extern void loadTexture(int texture);
#endif
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* draw_h */
