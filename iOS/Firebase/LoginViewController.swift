//
//  LoginViewController.swift
//  Firebase
//
//  Copyright © 2016 BatchLabs. All rights reserved.
//

import UIKit
import Batch

class LoginViewController: UIViewController, GIDSignInUIDelegate {

    @IBOutlet weak var loginOverlayView: UIView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        GIDSignIn.sharedInstance().uiDelegate = self
        
        NSNotificationCenter.defaultCenter().addObserver(self, selector: "dismiss", name: Consts.kUserLoggedInNotification, object: nil)
        NSNotificationCenter.defaultCenter().addObserver(self, selector: "showLoginError", name: Consts.kUserLoginFailNotification, object: nil)
    }
    
    deinit {
        GIDSignIn.sharedInstance().uiDelegate = nil
    }
    
    func showLoginError() {
        dismissLoadingView()
        
        let alertController = UIAlertController(title: "Login error",
            message: "An error occurred while trying to log in.\n\nPlease check your internet connection and try again!",
            preferredStyle: .Alert)
        alertController.addAction(UIAlertAction(title: "OK", style: .Default, handler: nil))
        
        presentViewController(alertController, animated: true, completion: nil)
    }
    
    func dismiss() {
        dismissLoadingView()
        dismissViewControllerAnimated(true, completion: nil)
    }
    
    func showLoadingView() {
        loginOverlayView.hidden = false
    }
    
    func dismissLoadingView() {
        loginOverlayView.hidden = true
    }
    
    @IBAction func googleSignIn(sender: AnyObject) {
        showLoadingView()
    }
    
    @IBAction func anonymousSignIn(sender: AnyObject) {
        showLoadingView()
        UserProfileManager.sharedInstance.loginAnonymously()
    }
    
    //MARK: GIDSignInUIDelegate methods
    func signIn(signIn: GIDSignIn!, presentViewController viewController: UIViewController!) {
        dismissLoadingView()
        presentViewController(viewController, animated: true, completion: nil)
    }
    
    func signIn(signIn: GIDSignIn!, dismissViewController viewController: UIViewController!) {
        viewController.dismissViewControllerAnimated(true, completion: nil)
    }
    
    func signInWillDispatch(signIn: GIDSignIn!, error: NSError!) {
        dismissLoadingView()
    }
}