//
//  SplashViewController.swift
//  Firebase
//
//  Copyright © 2016 BatchLabs. All rights reserved.
//

import UIKit

class SplashViewController: UIViewController {
    
    override func viewDidLoad() {
        super.viewDidLoad()
        NSNotificationCenter.defaultCenter().addObserver(self, selector: "dismiss", name: Consts.kSplashDismissNotification, object: nil)
    }
    
    func dismiss() {
        dismissViewControllerAnimated(true, completion: nil)
    }
}
