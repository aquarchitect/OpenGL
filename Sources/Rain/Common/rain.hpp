//
//  rain.hpp
//  Particles-iOS
//
//  Created by Hai Nguyen on 2/21/18.
//  Copyright © 2018 Hai Nguyen. All rights reserved.
//

#ifndef rain_hpp
#define rain_hpp

#include "utility.hpp"

class rain {
public:
    rain(string basePath, vec2 particlesSize, vec2 screenResolution);
    
    void            addObstacle(vec2 position);
    void            draw();
private:
    vec2            screenResolution;
    vec2            particlesSize;
    
    int             frame = 0;
    vector<vec2>    particles;
    vector<vec2>    obstacles;
    vector<vec2>    quad = {
                        {-1.0, -1.0},
                        {-1.0, +1.0},
                        {+1.0, -1.0},
                        {+1.0, +1.0}
                    };
    
    GLuint          particlesProgram = glCreateProgram();
    GLuint          obstablesProgram = glCreateProgram();
    GLuint          drawProgram = glCreateProgram();
    
    texture         position0Texture, position1Texture;
    texture         velocity0Texture, velocity1Texture;
    texture         obstacleTexture;
    
    GLuint          particlesVertexBuffer;
    GLuint          obstaclesVertexBuffer;
    GLuint          quadVertexBuffer;
    
    GLuint          particlesFramebuffer;
    GLuint          obstableFramebuffer;
    GLuint          defaultFramebuffer = 3;
    
    GLuint          particlesPositionsUniformLocation;
    GLuint          particlesVelocitiesUniformLocation;
    GLuint          particlesObstaclesUniformLocation;
    GLuint          particlesRandomUniformLocation;
    GLuint          particlesResolutionUniformLocation;
    GLuint          particlesModeUniformLocation;
    GLuint          particlesQuadAttributeLocation;
    
    GLuint          obstaclesModeUniformLocation;
    GLuint          obstaclesPointAttributeLocation;
    
    GLuint          drawPositionsUniformLocation;
    GLuint          drawVelocitiesUniformLocation;
    GLuint          drawPointAttributeLocation;
    
    void            swapPositionsTextures();
    void            swapVelocitiesTextures();
    
    void            updateParticles(GLint mode);
    void            drawObstacles(GLint mode);
    void            drawOnScreen();
};

#endif /* rain_hpp */
