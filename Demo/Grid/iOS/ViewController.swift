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
        
        let basePath = (Bundle.main.resourcePath.map({ "\($0)/" }) ?? "").cString(using: .utf8)
        setupGrid(UnsafeMutablePointer<Int8>(mutating: basePath))
    }
}

extension ViewController {
    
    override func glkView(_ view: GLKView, drawIn rect: CGRect) {
        let deltaTime = Date().timeIntervalSince(anchorTime)
        drawGrid(
            Float(deltaTime),
            Int32(view.drawableWidth),
            Int32(view.drawableHeight)
        )
    }
}
