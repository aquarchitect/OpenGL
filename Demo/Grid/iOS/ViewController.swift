//
//  ViewController.swift
//  GridPoints-iOS
//
//  Created by Hai Nguyen on 12/4/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

import GLKit

final class ViewController: GLKViewController {
    
    // MARK: Properties
    
    fileprivate let anchorTime = Date()
    
    // MARK: View Lifecycle
    
    override func viewDidLoad() {
        super.viewDidLoad()

        self.preferredFramesPerSecond = 60
        
        if let context = EAGLContext(api: .openGLES2) {
            (view as? GLKView)?.context = context
            EAGLContext.setCurrent(context)
        }
        
        var basePath = Bundle.main.resourcePath?.cString(using: .utf8) ?? []
        var resolution = view.resolution
        setupGrid(&basePath, &resolution)
    }
}

extension ViewController {
    
    override func glkView(_ view: GLKView, drawIn rect: CGRect) {
        let deltaTime = Date().timeIntervalSince(anchorTime)
        drawGrid(Float(deltaTime))
    }
}
