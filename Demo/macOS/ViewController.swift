//
//  ViewController.swift
//  Demo-macOS
//
//  Created by Hai Nguyen on 11/17/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

import AppKit

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
}
