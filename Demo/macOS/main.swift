//
//  main.swift
//  Demo-macOS
//
//  Created by Hai Nguyen on 11/17/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

import AppKit

@objc(Application)
final class Application: NSApplication {
    
    // MARK: Properties
    
    fileprivate let _delegate = AppDelegate()
    
    // MARK: Initialization
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override init() {
        super.init()
        super.delegate = _delegate
    }
}

Application.shared.run()
