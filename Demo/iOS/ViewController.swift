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
    
    // MARK: Initialization
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    init() {
        super.init(nibName: nil, bundle: nil)
        super.delegate = self
    }
    
    // MARK: View Lifecycle
    
    override func loadView() {
        view = RootView()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        _ = (view as? GLKView).map({ EAGLContext.setCurrent($0.context) })
        
        setBasePathForResources("\(Bundle.main.bundlePath)/")
        transformMatrix = GLKMatrix4Identity.m
        
        setup()
    }
}

extension ViewController: GLKViewControllerDelegate {
    
    func glkViewControllerUpdate(_ controller: GLKViewController) {
        (view as? RootView).map({ transformMatrix = $0.transformMatrix.m })
    }
}

extension ViewController {
    
    override func glkView(_ view: GLKView, drawIn rect: CGRect) {
        draw()
    }
}
