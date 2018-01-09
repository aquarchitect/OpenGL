//
//  ViewController.swift
//  Particles-iOS
//
//  Created by Hai Nguyen on 12/14/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

import GLKit

final class ViewController: RootController {
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let tap = UITapGestureRecognizer(target: self, action: #selector(tap(_:)))
        self.view.addGestureRecognizer(tap)
    }
}

extension ViewController {
    
    @objc func tap(_ sender: UITapGestureRecognizer) {
        let scale = view.contentScaleFactor
        let location = sender.location(in: view)
        
        addObstacle(
            Int32(location.x * scale),
            Int32((view.bounds.height - location.y) * scale)
        )
    }
}

extension ViewController {
    
    override func glkView(_ view: GLKView, drawIn rect: CGRect) {
         draw(0)
    }
}

