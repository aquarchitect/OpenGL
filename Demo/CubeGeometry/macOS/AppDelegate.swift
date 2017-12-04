//
//  AppDelegate.swift
//  Demo-macOS
//
//  Created by Hai Nguyen on 11/17/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

import AppKit

final class AppDelegate: NSObject {
    
    private var window: NSWindow?
}

extension AppDelegate: NSApplicationDelegate {
    
    func applicationDidFinishLaunching(_ notification: Notification) {
        window = NSWindow()
        window?.contentViewController = ViewController()
        window?.contentMinSize = CGSize(width: 400, height: 400)
        window?.contentMaxSize = CGSize(width: 400, height: 400)
        window?.backgroundColor = .red
        window?.makeKeyAndOrderFront(nil)
        window?.center()
    }
}

