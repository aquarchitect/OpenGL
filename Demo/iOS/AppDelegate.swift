//
//  AppDelegate.swift
//  OpenGL
//
//  Created by Hai Nguyen on 11/13/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

import UIKit
import MyKit
import GLKit

@UIApplicationMain
final class AppDelegate: UIResponder {

    var window: UIWindow?
}

extension AppDelegate: UIApplicationDelegate {
    
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
        window = UIWindow(frame: UIScreen.main.bounds).then {
            $0.rootViewController = ViewController()
            $0.backgroundColor = .white
            $0.makeKeyAndVisible()
        }

        return true
    }
}
