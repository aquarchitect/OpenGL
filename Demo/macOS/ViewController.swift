//
//  ViewController.swift
//  Demo-macOS
//
//  Created by Hai Nguyen on 11/17/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

import AppKit
import GLKit

final class ViewController: NSViewController {
    
    // MARK: Initialization
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    init() {
        super.init(nibName: nil, bundle: nil)
    }
    
    // MARK: View Lifecycle
    
    override func loadView() {
        view = RootView()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        (view as? RootView)?.delegate = self
    }
}

extension ViewController: NSOpenGLViewDelegate {
    
    func openGLViewDidPrepareOpenGL(_ view: NSOpenGLView) {
        Bundle.main.resourcePath.map({ setBasePathForResources("\($0)/") })
        
        if let image = Bundle.main
            .path(forResource: "Dungeon", ofType: "png")
            .flatMap(NSImage.init(contentsOfFile:))?
            .cgImage(forProposedRect: nil, context: nil, hints: nil),
            let bytes = image
                .dataProvider?
                .data
                .map({ $0 as NSData })?
                .bytes
        {
            setCubeTexture(Int32(image.width), Int32(image.height), UInt32(GL_RGBA), bytes)
        }
        
        let projection = GLKMatrix4MakePerspective(
            GLKMathDegreesToRadians(85),
            Float(view.bounds.width/view.bounds.height),
            1, 150
        )
        setCubeProjection(projection.cm)
    }
    
    func openGLView(_ view: NSOpenGLView, drawIn rect: NSRect) {
        setup()
        
        let transformation = GLKMatrix4MakeTranslation(0, 0, -5)
        drawCube(transformation.cm)
        
        glFlush()
    }
}
