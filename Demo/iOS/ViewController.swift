//
//  ViewController.swift
//  Demo-iOS
//
//  Created by Hai Nguyen on 11/15/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

import UIKit
import GLKit

final class ViewController: GLKViewController {
    
    // MARK: View Lifecycle
    
    override func loadView() {
        view = RootView()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        _ = (view as? GLKView).map({ EAGLContext.setCurrent($0.context) })
    
        let basePath = (Bundle.main.resourcePath.map({ "\($0)/" }) ?? "").cString(using: .utf8)
        setup(
            Float(view.bounds.width),
            Float(view.bounds.height),
            UnsafeMutablePointer<Int8>(mutating: basePath)
        )
    }
}

extension ViewController: GLKViewControllerDelegate {
    
    func glkViewControllerUpdate(_ controller: GLKViewController) {}
}

extension ViewController {
    
    override func glkView(_ view: GLKView, drawIn rect: CGRect) {
        guard let translation = (view as? RootView)?.translation else { return }
        translate(GLfloat(translation.x), GLfloat(translation.y), GLfloat(translation.z))
    }
}
