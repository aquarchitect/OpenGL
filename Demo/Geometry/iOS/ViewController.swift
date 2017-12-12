//
//  ViewController.swift
//  Demo-iOS
//
//  Created by Hai Nguyen on 11/15/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

import GLKit

final class ViewController: GLKViewController {
    
    // MARK: View Lifecycle
    
    override func loadView() {
        view = RootView()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
    
        EAGLContext.setCurrent((view as? GLKView)?.context)
        
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

extension ViewController {
    
    override func glkView(_ view: GLKView, drawIn rect: CGRect) {
        let translation = (view as? RootView).flatMap {
            $0.translation == (0, 0, 0) ? nil : (
                Float($0.translation.x/view.bounds.width),
                Float($0.translation.y/view.bounds.height),
                Float(0)
            )
        } ?? (0, 0, 0)
        rotateCube(translation.0, translation.1, translation.2)
    }
}
