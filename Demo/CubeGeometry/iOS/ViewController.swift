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
        setupCube(
            Float(view.bounds.width/view.bounds.height),
            UnsafeMutablePointer<Int8>(mutating: basePath)
        )
        
        if let image = Bundle.main
                .path(forResource: "Dungeon", ofType: "png")
                .flatMap(UIImage.init(contentsOfFile:))?
                .cgImage,
            let bytes = image
                .dataProvider?
                .data
                .map({ $0 as NSData })
                .map({ UnsafeMutableRawPointer(mutating: $0.bytes) })
        {
            loadCubeTexture(Int32(image.width), Int32(image.height), bytes)
        }
    }
}

extension ViewController: GLKViewControllerDelegate {
    
    func glkViewControllerUpdate(_ controller: GLKViewController) {}
}

extension ViewController {
    
    override func glkView(_ view: GLKView, drawIn rect: CGRect) {
        guard let translation = (view as? RootView)?.translation else { return }
        rotateCube(
            GLfloat(translation.x/view.bounds.width),
            GLfloat(translation.y/view.bounds.height),
            0
        )
    }
}
