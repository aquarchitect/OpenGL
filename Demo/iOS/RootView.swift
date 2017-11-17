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
    
    private(set) var panFeatures: (translation: CGPoint, velocity: CGPoint) = (.zero, .zero)
    private(set) var tapLocation: CGPoint = .zero
    
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
        let tap = UITapGestureRecognizer(target: self, action: #selector(tap(_:)))
        tap.require(toFail: pan)
        
        [tap, pan].forEach(self.addGestureRecognizer(_:))
    }
}

extension RootView {
    
    @objc func tap(_ gesture: UITapGestureRecognizer) {
        tapLocation = gesture.location(in: nil)
    }
    
    @objc func pan(_ gesture: UIPanGestureRecognizer) {
        let translation = gesture.translation(in: nil)
        let velocity = gesture.velocity(in: nil)
        
        panFeatures = (translation, velocity)
        
    }
}
