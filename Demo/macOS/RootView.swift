//
//  RootView.swift
//  Demo-macOS
//
//  Created by Hai Nguyen on 11/17/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

import AppKit

protocol NSOpenGLViewDelegate: class {
    
    func openGLViewDidPrepareOpenGL(_ view: NSOpenGLView)
    func openGLView(_ view: NSOpenGLView, drawIn rect: NSRect)
}

final class RootView: NSOpenGLView {
    
    weak var delegate: NSOpenGLViewDelegate?
    
    // MARK: Initialization
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override init(frame frameRect: NSRect) {
        super.init(frame: frameRect)
        super.frame.size = CGSize(width: 400, height: 400)
    }
    
    override init?(frame frameRect: NSRect, pixelFormat format: NSOpenGLPixelFormat?) {
        super.init(frame: frameRect, pixelFormat: format)
        super.frame.size = CGSize(width: 400, height: 400)
    }
    
    // MARK: System Methods
    
    override func prepareOpenGL() {
        super.prepareOpenGL()
        
        delegate?.openGLViewDidPrepareOpenGL(self)
    }
    
    override func draw(_ dirtyRect: NSRect) {
        super.draw(dirtyRect)
        delegate?.openGLView(self, drawIn: dirtyRect)
    }
}
