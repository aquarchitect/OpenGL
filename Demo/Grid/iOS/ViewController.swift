//
//  ViewController.swift
//  Grid-iOS
//
//  Created by Hai Nguyen on 12/18/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

import GLKit

final class ViewController: RootController {
    
    // MARK: Properties
    
    fileprivate let startTime = Date()
}

extension ViewController {
    
    override func glkView(_ view: GLKView, drawIn rect: CGRect) {
        let deltaTime = Date().timeIntervalSince(startTime)
        draw(Float(deltaTime))
    }
}
