//
//  UIView+.swift
//  OpenGL
//
//  Created by Hai Nguyen on 12/18/17.
//  Copyright © 2017 Hai Nguyen. All rights reserved.
//

import UIKit

extension UIView {

    var resolution: [Int32] {
        return [
            Int32(self.bounds.width * self.contentScaleFactor),
            Int32(self.bounds.height * self.contentScaleFactor)
        ]
    }
}
