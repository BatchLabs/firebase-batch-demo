# Firebase + Batch

This is Firebase+Batch demo app for iOS and Android.

It shows how to authentify an user, and make Firebase and Batch use a shared identifier so that you can store your data in Firebase and use Batch to push them, very much like Parse used to do. 

Requirements:
 - A Firebase account & app
 - Batch account with one app per platform
 - If you want to use Google+ Authentication, you will need to enable Google+ in your Google Developers Console project (https://console.developers.google.com). 
 	- Then put it in your Firebase App configuration

Android requirements:
 - A GCM Sender ID and auth key
 - Android Studio 1.5
 - For Google+ Auth:
 	- A generated `google-services.json` that you'll put in `Android/Firebase/app/`

iOS Requirements:
 - Push certificates from your Apple Provisioning Profile portal
 - Xcode 6
 - Cocoapods
 	- Pods are preinstalled
 - For Google+ Auth:
 	- A generated `GoogleService-Info.plist` that you'll put in `iOS/Firebase/`

# How to use

## Android  

 - Open the project in Android Studio
 - Put your API Key, GCM Sender ID and Firebase URL in Config.java
 - (optional) Put the google-services.json file in `Android/Firebase/app/` for Google+ Login
 - Run it on a real device or a Google API simulator :)

## iOS  

 - Open the xcworkspace in Xcode
 - Put your API Key and Firebase URL in Consts.swift
 - Provision it correctly: Change the app ID to your own, and make sure it has push notification configured
 - (optional) Put the GoogleService-Info.plist file in `iOS/Firebase/` for Google+ Login
 - Run it on a real device, since push isn't supported in the simulator

More info on how to setup Batch's dashboard here: https://dashboard.batch.com/doc
