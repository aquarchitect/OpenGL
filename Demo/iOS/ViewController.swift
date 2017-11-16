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
        
        _ = rootView.map({ EAGLContext.setCurrent($0.context) })
    
        setBasePathForResources("\(Bundle.main.bundlePath)/")
        
        if let image = Bundle.main
                .path(forResource: "Dungeon", ofType: "png")
                .flatMap(UIImage.init(contentsOfFile:))?
                .cgImage,
            let bytes = image
                .dataProvider?
                .data
                .map({ $0 as NSData })?
                .bytes
        {
            setFacadeImage(Int32(image.width), Int32(image.height), UInt32(GL_RGBA), bytes)
        }
        
        transformationMatrix = rootView?.transformationMatrix.m ??  GLKMatrix4Identity.m
        projectionMatrix = GLKMatrix4MakePerspective(
            GLKMathDegreesToRadians(85),
            Float(view.bounds.width/view.bounds.height),
            1, 150
        ).m
        
        setup()
    }
}

private extension ViewController {
    
    var rootView: RootView? {
        return view as? RootView
    }
}

extension ViewController: GLKViewControllerDelegate {
    
    func glkViewControllerUpdate(_ controller: GLKViewController) {
        (view as? RootView).map({ transformationMatrix = $0.transformationMatrix.m })
    }
}

extension ViewController {
    
    override func glkView(_ view: GLKView, drawIn rect: CGRect) {
        draw()
    }
}
