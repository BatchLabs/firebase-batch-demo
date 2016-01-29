//
//  AppDelegate.swift
//  Firebase
//
//  Copyright © 2016 BatchLabs. All rights reserved.
//


import UIKit
import Batch

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate, GIDSignInDelegate {
    
    var window: UIWindow?
    var firebase: Firebase!
    var silentLoginDone = false
    
    static func sharedInstance() -> AppDelegate {
        return UIApplication.sharedApplication().delegate as! AppDelegate
    }
    
    func application(application: UIApplication, didFinishLaunchingWithOptions launchOptions: [NSObject: AnyObject]?) -> Bool {
        
        UIApplication.sharedApplication().statusBarStyle = UIStatusBarStyle.LightContent
        UINavigationBar.appearance().barTintColor = UIColor(red: 63/255, green: 81/255, blue: 181/255, alpha: 1)
        UINavigationBar.appearance().translucent = false
        UINavigationBar.appearance().titleTextAttributes = [NSForegroundColorAttributeName: UIColor.whiteColor()]
        
        // SDKs init
        
        // Important to start Batch first, because we will need the UserProfile methods
        Batch.startWithAPIKey(Consts.kBatchAPIKey)
        
        firebase = Firebase(url: Consts.kFirebaseAppURL)
        
        var gglError: NSError?
        GGLContext.sharedInstance().configureWithError(&gglError)
        if let gglError = gglError {
            print("Error while configuring GGLContext \(gglError.localizedDescription)")
        }
        
        GIDSignIn.sharedInstance().delegate = self
        
        
        if UserProfileManager.sharedInstance.loginType == .Google {
            GIDSignIn.sharedInstance().signInSilently()
        } else {
            UserProfileManager.sharedInstance.readAuthInfo()
            silentLoginDone = true
        }
        
        return true
    }
    
    func applicationWillResignActive(application: UIApplication) {
        // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
        // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
    }
    
    func applicationDidEnterBackground(application: UIApplication) {
        // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
        // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    }
    
    func applicationWillEnterForeground(application: UIApplication) {
        // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
    }
    
    func applicationDidBecomeActive(application: UIApplication) {
        // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    }
    
    func applicationWillTerminate(application: UIApplication) {
        // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    }
    
    // We implement the deprecated method because GIDSignIn doesn't supoprt the new one
    func application(application: UIApplication, openURL url: NSURL, sourceApplication: String?, annotation: AnyObject) -> Bool {
        let batchResult = Batch.handleURL(url)
        let googleResult = GIDSignIn.sharedInstance().handleURL(url, sourceApplication: sourceApplication, annotation: annotation)
        
        return batchResult || googleResult
    }
    
    //MARK: GIDSignInDelegate methods
    func signIn(signIn: GIDSignIn!, didSignInForUser user: GIDGoogleUser!, withError error: NSError!) {
        silentLoginDone = true
        
        if error == nil {
            print("Signed in \(user) with Google. Signing into Firebase")
            UserProfileManager.sharedInstance.loginWithGoogle(user)
        } else {
            print("Error while logging in: \(error.localizedDescription)")
            NSNotificationCenter.defaultCenter().postNotificationName(Consts.kSplashDismissNotification, object: nil)
            NSNotificationCenter.defaultCenter().postNotificationName(Consts.kUserLoginFailNotification, object: nil)
        }
    }
    
    func signIn(signIn: GIDSignIn!, didDisconnectWithUser user: GIDGoogleUser!, withError error: NSError!) {
        silentLoginDone = true
        print("Signing out Google user \(user)")
        UserProfileManager.sharedInstance.logout()
    }
}
