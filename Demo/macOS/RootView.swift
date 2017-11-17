//
//  RootView.swift
//  Demo-macOS
//
//  Created by Hai Nguyen on 11/17/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

import AppKit

final class RootView: NSOpenGLView {
    
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
}
