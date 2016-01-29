//
//  MainViewController.swift
//  Firebase
//
//  Copyright © 2016 BatchLabs. All rights reserved.
//

import UIKit
import Batch.Push

class MainViewController: UITableViewController {

    @IBOutlet weak var loginLabel: UILabel!
    @IBOutlet weak var uidLabel: UILabel!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    override func viewWillAppear(animated: Bool) {
        loginLabel.text = {
            switch UserProfileManager.sharedInstance.loginType {
            case .Google:
                return "Google Sign-In"
            case .Anonymous:
                return "Anonymous"
            case .LoggedOut:
                return "Logged out"
            }
        }()
        uidLabel.text = UserProfileManager.sharedInstance.currentUser?.UID ?? "<unknown>"
    }
    
    override func viewDidAppear(animated: Bool) {
        super.viewDidAppear(animated)
        
        if !AppDelegate.sharedInstance().silentLoginDone {
            performSegueWithIdentifier("splashSegue", sender: self)
        } else {
            if !UserProfileManager.sharedInstance.isLoggedIn() {
                performSegueWithIdentifier("loginSegue", sender: self)
            } else {
                BatchPush.registerForRemoteNotifications()
            }
        }
    }
    
    override func tableView(tableView: UITableView, didSelectRowAtIndexPath indexPath: NSIndexPath) {
        tableView.deselectRowAtIndexPath(indexPath, animated: true)
        switch indexPath.section {
        case 2:
            UserProfileManager.sharedInstance.logout()
            performSegueWithIdentifier("loginSegue", sender: self)
            break;
        case 1:
            UIApplication.sharedApplication().openURL(NSURL(string: "https://batch-demo-alpha.firebaseapp.com/")!)
            break;
        default:
            break;
        }
    }
    
    override func tableView(tableView: UITableView, shouldShowMenuForRowAtIndexPath indexPath: NSIndexPath) -> Bool {
        return indexPath.section == 0
    }
    
    override func tableView(tableView: UITableView, canPerformAction action: Selector, forRowAtIndexPath indexPath: NSIndexPath, withSender sender: AnyObject?) -> Bool {
        return action == "copy:"
    }
    
    override func tableView(tableView: UITableView, performAction action: Selector, forRowAtIndexPath indexPath: NSIndexPath, withSender sender: AnyObject?) {
        if indexPath.section == 0 {
            let stringToCopy:String = {
                if indexPath.row == 0 {
                    return loginLabel.text ?? ""
                }
                return uidLabel.text ?? ""
            }()
            
            UIPasteboard.generalPasteboard().string = stringToCopy
        }
    }

}

