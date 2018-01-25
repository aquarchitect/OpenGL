//
//  VideoController.swift
//  OpenGL
//
//  Created by Hai Nguyen on 1/25/18.
//  Copyright © 2018 Hai Nguyen. All rights reserved.
//

import AVFoundation

protocol VideoControllerDelegate: class {
    
    func videoControllerDidCaptureVideoTexture(_ texture: CVOpenGLESTexture)
}

final class VideoController: NSObject {
    
    // MARK: Properties
    
    weak var _delegate: VideoControllerDelegate?
    
    private let session = AVCaptureSession()
    private var textureCache: CVOpenGLESTextureCache?
    
    // MARK: Initialization
    
    init(context: EAGLContext, preset: AVCaptureSession.Preset) {
        super.init()
        
        CVOpenGLESTextureCacheCreate(kCFAllocatorDefault, nil, context, nil, &textureCache)
        
        session.beginConfiguration()
        session.sessionPreset = preset
        
        // create input
        let input = AVCaptureDevice.default(for: .video)
            .flatMap({ try? AVCaptureDeviceInput(device: $0) })
        input.map(session.addInput)
        
        // create output
        let output = AVCaptureVideoDataOutput()
        output.alwaysDiscardsLateVideoFrames = true
        output.videoSettings = [
            kCVPixelBufferPixelFormatTypeKey as String: NSNumber(value: kCVPixelFormatType_420YpCbCr8BiPlanarFullRange)
        ]
        output.setSampleBufferDelegate(self, queue: .main)
        session.addOutput(output)
        
        session.commitConfiguration()
    }
    
    // MARK: Support Method
    
    func start() {
        session.startRunning()
    }
    
    func stop() {
        session.stopRunning()
    }
}

extension VideoController: AVCaptureVideoDataOutputSampleBufferDelegate {
    
    func captureOutput(_ output: AVCaptureOutput, didOutput sampleBuffer: CMSampleBuffer, from connection: AVCaptureConnection) {
        guard let textureCache = self.textureCache,
            let pixelBuffer = CMSampleBufferGetImageBuffer(sampleBuffer)
            else { return }
        
        let width = CVPixelBufferGetWidth(pixelBuffer)
        let height = CVPixelBufferGetHeight(pixelBuffer)
        
        CVOpenGLESTextureCacheFlush(textureCache, 0);
        var texture: CVOpenGLESTexture?
        if case let error = CVOpenGLESTextureCacheCreateTextureFromImage(
            kCFAllocatorDefault,
            textureCache,
            pixelBuffer,
            nil,
            GLenum(GL_TEXTURE_2D),
            GL_RED_EXT,
            GLsizei(width),
            GLsizei(height),
            GLenum(GL_RED_EXT),
            GLenum(GL_UNSIGNED_BYTE),
            0,
            &texture
            ), error != kCVReturnSuccess
        {
            fatalError("Error occurred: \(error)")
        }
        
        texture.flatMap({ _delegate?.videoControllerDidCaptureVideoTexture($0) })
    }
}
