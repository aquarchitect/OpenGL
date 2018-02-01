//
//  ViewController.swift
//  Ripple-iOS
//
//  Created by Hai Nguyen on 1/18/18.
//  Copyright © 2018 Hai Nguyen. All rights reserved.
//

import GLKit
import AVFoundation

final class ViewController: RootController {
    
    // MARK: Properties
    
    private let startTime = Date()
    private var videoController: VideoController?
    
    // MARK: View Lifecycle
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        videoController = EAGLContext.current().map {
            let preset: AVCaptureSession.Preset
            switch self.traitCollection.userInterfaceIdiom {
            case .pad: preset = .hd1280x720
            default: preset = .vga640x480
            }
            
            return VideoController(context: $0, preset: preset)
        }
        videoController?._delegate = self
        videoController?.start()
    }
}

extension ViewController: VideoControllerDelegate {
    
    func videoControllerDidCaptureVideoTexture(_ texture: CVOpenGLESTexture) {
        loadTexture(Int32(CVOpenGLESTextureGetName(texture)))
    }
}

extension ViewController {
    
    override func glkView(_ view: GLKView, drawIn rect: CGRect) {
        let deltaTime = Date().timeIntervalSince(startTime)
        draw(Float(deltaTime))
    }
}
