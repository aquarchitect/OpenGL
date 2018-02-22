//
//  scene.hpp
//  Geometry-iOS
//
//  Created by Hai Nguyen on 11/20/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef geometry_hpp
#define geometry_hpp

#include "utility.hpp"
#include "mesh.hpp"

class scene {
public:
    scene(string basePath, vec2 screenResolution);
    
    void    loadCubeTexture(GLsizei width, GLsizei height, GLvoid *pixels);
    
    void    draw();
private:
    string      basePath;
    vec2        screenResolution;
    mesh        *pCube;
};
#endif /* geometry_hpp */
