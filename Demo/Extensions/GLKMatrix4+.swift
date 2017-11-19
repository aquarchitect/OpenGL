//
//  GLKMatrix4+.swift
//  OpenGL
//
//  Created by Hai Nguyen on 11/18/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

import GLKit

extension GLKMatrix4 {
    
    var cm: UnsafePointer<Float> {
        let result = Mirror(reflecting: self.m)
            .children
            .flatMap({ $0.value as? Float })
        
        return UnsafePointer(result)
    }
}
