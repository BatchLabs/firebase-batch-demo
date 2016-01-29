//
//  BatchUserProfile.h
//  Batch
//
//  https://batch.com
//  Copyright (c) 2014 Batch SDK. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 @class BatchUserProfile
 @abstract Describe a complete user profile.
 @discussion Use this object to access all the user info.
 */
@interface BatchUserProfile : NSObject

/*!
 @property customIdentifier
 @abstract Set a custom user identifier to Batch, you should use this method if you have your own login system.
 @warning Be careful: Do not use it if you don't know what you are doing, giving a bad custom user ID can result in failure of targeted push notifications delivery or offer delivery and restore.
 */
@property (strong, nonatomic) NSString *customIdentifier;

/*!
 @property language
 @abstract The application language, default value is the device language.
 @discussion Set to nil to reset to default value.
 */
@property (strong, nonatomic) NSString *language;

/*!
 @property region
 @abstract The application region, default value is the device region.
 @discussion Set to nil to reset to default value.
 */
@property (strong, nonatomic) NSString *region;

@end