//
//  ViewController.swift
//  Demo-iOS
//
//  Created by Hai Nguyen on 11/15/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

import GLKit
import CoreMotion

final class ViewController: RootController {
    
    // MARK: Properties
    
    fileprivate let motionManager = CMMotionManager()
    fileprivate let motionQueue = OperationQueue()
    
    fileprivate var attitude: CMAttitude?
    
    // MARK: View Lifecycle
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
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
            loadTexture(Int32(image.width), Int32(image.height), bytes)
        }
        
        motionManager.gyroUpdateInterval = 1
        motionManager.startDeviceMotionUpdates(to: motionQueue) { [weak self] (motion, _) in
            self?.attitude = motion?.attitude
        }
    }
}

extension ViewController {
    
    override func glkView(_ view: GLKView, drawIn rect: CGRect) {
        guard let attitude = self.attitude else { return }
        
        rotateCamera(
            Float(attitude.roll),
            Float(attitude.pitch),
            Float(attitude.yaw)
        )
    }
}
