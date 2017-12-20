//
//  update.hpp
//  Particles-iOS
//
//  Created by Hai Nguyen on 12/18/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

#ifndef update_hpp
#define update_hpp

#include "utility.hpp"

class Update {
public:
    Update(string basePath);
    void draw();
private:
    vector<vec2>   vertices = {
                        {-1.0, -1.0},
                        {-1.0, +1.0},
                        {+1.0, -1.0},
                        {+1.0, +1.0}
                    };
    
    GLuint          program = glCreateProgram();
    
    GLuint          VAO;
    GLuint          VBO;
};

#endif /* update_hpp */
