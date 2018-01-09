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
    
    extern void addObstacle(int x, int y);
    extern void rotateCamera(float pitch, float yaw, float roll);
    extern void loadTexture(int width, int height, void *pixels);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* draw_h */
