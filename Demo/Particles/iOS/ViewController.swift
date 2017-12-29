//
//  ViewController.swift
//  Particles-iOS
//
//  Created by Hai Nguyen on 12/14/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

import GLKit

final class ViewController: RootController {}

extension ViewController {
    
    override func glkView(_ view: GLKView, drawIn rect: CGRect) {
         draw(0)
    }
}

