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
        let basePath = (Bundle.main.resourcePath.map({ "\($0)/" }) ?? "").cString(using: .utf8)
        setupCube(
            Float(view.bounds.width/view.bounds.height),
            UnsafeMutablePointer<Int8>(mutating: basePath)
        )
        
        if let image = Bundle.main
                .path(forResource: "Dungeon", ofType: "png")
                .flatMap(NSImage.init(contentsOfFile:))?
                .cgImage(forProposedRect: nil, context: nil, hints: nil),
            let bytes = image
                .dataProvider?
                .data
                .map({ $0 as NSData })
                .map({ UnsafeMutableRawPointer(mutating: $0.bytes) })
        {
            loadCubeTexture(Int32(image.width), Int32(image.height), bytes)
        }
    }
    
    func openGLView(_ view: NSOpenGLView, drawIn rect: NSRect) {
        rotateCube(0, 0, 0)
        glFlush()
    }
}
