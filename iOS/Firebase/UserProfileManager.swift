//
//  UserProfileManager.swift
//  Firebase
//
//  Copyright © 2016 BatchLabs. All rights reserved.
//

import Foundation
import Batch

struct User {
    let UID: String
    let name: String
    let email: String
    let profileImage: String
    
    init(UID: String, name: String, email: String, profileImage: String) {
        self.UID = UID
        self.name = name
        self.email = email
        self.profileImage = profileImage
    }
}

enum LoginType: String {
    case Google = "google"
    case Anonymous = "anon"
    case LoggedOut = "logged_out"
}

class UserProfileManager {
    static let sharedInstance = UserProfileManager()
    
    var currentUser: User?
    var userFirebase: Firebase?
    var friends: [User] = []
    
    var loginType:LoginType {
        get {
            return LoginType(rawValue: NSUserDefaults.standardUserDefaults().stringForKey(Consts.kLoginTypeKey) ?? "") ?? .LoggedOut
        }
        set(newLoginType) {
            let defaults = NSUserDefaults.standardUserDefaults()
            defaults.setValue(newLoginType.rawValue, forKey: Consts.kLoginTypeKey)
            defaults.synchronize()
        }
    }
    
    func isLoggedIn() -> Bool {
        return currentUser != nil || loginType == .Anonymous
    }
    
    func readAuthInfo() {
        let firebase = AppDelegate.sharedInstance().firebase;
        if let auth = firebase.authData where "anonymous" == auth.provider {
            self.currentUser = User(
                UID: auth.uid,
                name: "Anonymous",
                email: "anon@anon.com",
                profileImage: "")
            self.userFirebase = firebase.childByAppendingPath("users").childByAppendingPath(self.currentUser!.UID)
        }
    }
    
    func loginAnonymously() {
        AppDelegate.sharedInstance().firebase.authAnonymouslyWithCompletionBlock { (error: NSError!, data: FAuthData!) -> Void in
            if error == nil {
                print("Signed in into Firebase")
                self.currentUser = User(
                    UID: data.uid,
                    name: "Anonymous",
                    email: "anon@anon.com",
                    profileImage: "")
                
                self.loginType = .Anonymous
                
                let firebase = AppDelegate.sharedInstance().firebase.childByAppendingPath("users")
                self.userFirebase = firebase.childByAppendingPath(self.currentUser!.UID)
                
                self.userFirebase!.setValue([
                    "provider": "anonymous",
                    "name": self.currentUser!.name,
                    "email": self.currentUser!.email,
                    "profileImageURL": self.currentUser!.profileImage
                    ])
                
                Batch.defaultUserProfile()?.customIdentifier = self.currentUser!.UID
                
                NSNotificationCenter.defaultCenter().postNotificationName(Consts.kUserLoggedInNotification, object: nil)
                NSNotificationCenter.defaultCenter().postNotificationName(Consts.kSplashDismissNotification, object: nil)
            } else {
                print("Error while singing in Firebase \(error.localizedDescription)")
                NSNotificationCenter.defaultCenter().postNotificationName(Consts.kUserLoginFailNotification, object: nil)
            }
        }
    }
    
    func loginWithGoogle(user: GIDGoogleUser) {
        AppDelegate.sharedInstance().firebase.authWithOAuthProvider("google", token: user.authentication.accessToken, withCompletionBlock: { (error: NSError!, data: FAuthData!) in
            if error == nil {
                print("Signed in into Firebase")
                self.saveGoogleInfo(user, firebaseAuthData: data)
                NSNotificationCenter.defaultCenter().postNotificationName(Consts.kUserLoggedInNotification, object: nil)
                NSNotificationCenter.defaultCenter().postNotificationName(Consts.kSplashDismissNotification, object: nil)
            } else {
                print("Error while singing in Firebase \(error.localizedDescription)")
                NSNotificationCenter.defaultCenter().postNotificationName(Consts.kUserLoginFailNotification, object: nil)
            }
        })
    }
    
    func saveGoogleInfo(googleUser: GIDGoogleUser, firebaseAuthData: FAuthData) {
        currentUser = User(
            UID: firebaseAuthData.uid,
            name: googleUser.profile.name,
            email: googleUser.profile.email,
            profileImage: googleUser.profile.imageURLWithDimension(128).absoluteString ?? "")
        
        loginType = .Google
        
        let firebase = AppDelegate.sharedInstance().firebase.childByAppendingPath("users")
        userFirebase = firebase.childByAppendingPath(currentUser!.UID)
        
        userFirebase!.setValue([
            "provider": "google",
            "name": currentUser!.name,
            "email": currentUser!.email,
            "profileImageURL": currentUser!.profileImage,
            "googleAuthToken": googleUser.authentication.idToken,
            "googleUserID": googleUser.userID,
            "googleDomain": googleUser.hostedDomain ?? "",
            ])
        
        Batch.defaultUserProfile()?.customIdentifier = currentUser!.UID
    }
    
    func logout() {
        Batch.defaultUserProfile()?.customIdentifier = nil
        AppDelegate.sharedInstance().firebase.unauth()
        loginType = LoginType.LoggedOut
        currentUser = nil
        userFirebase = nil
    }
    
}