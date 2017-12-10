//
//  RootView.swift
//  Demo-iOS
//
//  Created by Hai Nguyen on 11/15/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

import UIKit
import GLKit

final class RootView: GLKView {
 
    // MARK: Properties
    
    private(set) var translation: (x: CGFloat, y: CGFloat, z: CGFloat) = (0, 0, 0)
    fileprivate var previousLocation: CGPoint = .zero
    
    // MARK: Initialization
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    init() {
        super.init(frame: UIScreen.main.bounds)
        
        if let context = EAGLContext(api: .openGLES2) {
            self.context = context
        }
        
        let pan = UIPanGestureRecognizer(target: self, action: #selector(pan(_:)))
        self.addGestureRecognizer(pan)
    }
}

extension RootView {
    
    @objc func pan(_ gesture: UIPanGestureRecognizer) {
        let location = gesture.location(in: nil)
        
        switch gesture.state {
        case .began:
            previousLocation = location
        case .changed:
            translation = (
                x: location.x - previousLocation.x,
                y: location.y - previousLocation.y,
                z: 0
            )
            previousLocation = location
        default:
            translation = (0, 0, 0)
        }
        
    }
}
