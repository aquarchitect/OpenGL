//
//  ViewController.swift
//  GridPoints-iOS
//
//  Created by Hai Nguyen on 12/4/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

import GLKit

final class ViewController: GLKViewController {
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let basePath = (Bundle.main.resourcePath.map({ "\($0)/" }) ?? "").cString(using: .utf8)
//        setupGrid(UnsafeMutablePointer<Int8>(mutating: basePath))
    }
}

extension ViewController {
    
    override func glkView(_ view: GLKView, drawIn rect: CGRect) {
//        drawGrid()
    }
}
