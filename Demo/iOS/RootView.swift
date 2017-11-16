//
//  RootView.swift
//  Demo-iOS
//
//  Created by Hai Nguyen on 11/15/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

import UIKit
import GLKit
import MyKit

final class RootView: GLKView {
 
    // MARK: Properties
    
    private(set) var transformMatrix = GLKMatrix4Identity
    
    // MARK: Initialization
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    init() {
        super.init(frame: UIScreen.main.bounds)
 
        if let context = EAGLContext(api: .openGLES2) {
            self.context = context
        }
        
        UIPanGestureRecognizer()
            .then({ $0.addTarget(self, action: #selector(pan(_:))) })
            .andThen(self.addGestureRecognizer(_:))
    }
}

extension RootView {
    
    @objc func pan(_ gesture: UIPanGestureRecognizer) {
        let translation = gesture.translation(in: nil)

        transformMatrix = GLKMatrix4MakeTranslation(
            Float(translation.x/self.bounds.width),
            Float(translation.y/self.bounds.height),
            0
        )
    }
}
