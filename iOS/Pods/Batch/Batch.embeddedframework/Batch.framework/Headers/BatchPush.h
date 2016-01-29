//
//  BatchPush.h
//  Batch
//
//  https://batch.com
//  Copyright (c) 2014 Batch SDK. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 @const BatchPushReceivedNotification
 @abstract Notification send by Batch Push when it gets a remote notification. This includes the one your app is started with (even though it is only sent when Batch starts)
 */
FOUNDATION_EXPORT NSString *const BatchPushReceivedNotification;

/*!
 @enum BatchNotificationType
 @abstract Remote notification types wrapper.
 @discussion Wrap iOS 8 and inferior remote notification types.
 */
typedef NS_OPTIONS(NSUInteger, BatchNotificationType)
{
    BatchNotificationTypeNone    = 0,
    BatchNotificationTypeBadge   = 1 << 0,
    BatchNotificationTypeSound   = 1 << 1,
    BatchNotificationTypeAlert   = 1 << 2,
};

/*!
 @class BatchPush
 @abstract Provides the Batch-related Push methods
 @discussion Actions you can perform in BatchPush.
 */
@interface BatchPush : NSObject

/*!
 @method init
 @warning Never call this method.
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 @method setupPush
 @abstract Activate Batch Push system.
 @discussion You can call this method from any thread.
 */
+ (void)setupPush NS_AVAILABLE_IOS(6_0);

/*!
@method setRemoteNotificationTypes:
@abstract Change the used remote notification types.
@discussion Default value is: BatchNotificationTypeBadge | BatchNotificationTypeSound | BatchNotificationTypeAlert
@param type : A bit mask specifying the types of notifications the app accepts.
*/
+ (void)setRemoteNotificationTypes:(BatchNotificationType)type NS_AVAILABLE_IOS(6_0);

/*!
 @method registerForRemoteNotifications
 @abstract Call to trigger the iOS popup that asks the user if he wants to allow Push Notifications and register to APNS.
 @discussion Default registration is made with Badge, Sound and Alert. If you want another configuration: call `setRemoteNotificationTypes:`.
 @discussion You should call this at a strategic moment, like at the end of your welcome.
 */
+ (void)registerForRemoteNotifications NS_AVAILABLE_IOS(6_0);

/*!
 @method registerForRemoteNotificationsWithCategories:
 @abstract Call to trigger the iOS popup that asks the user if he wants to allow Push Notifications and register to APNS.
 @discussion Default registration is made with Badge, Sound and Alert. If you want another configuration: call `setRemoteNotificationTypes:`.
 @discussion You should call this at a strategic moment, like at the end of your welcome.
 @param categories  : A set of UIUserNotificationCategory objects that define the groups of actions a notification may include.
 */
+ (void)registerForRemoteNotificationsWithCategories:(NSSet *)categories NS_AVAILABLE_IOS(8_0);

/*!
 @method clearBadge
 @abstract Clear the application's badge on the homescreen.
 @discussion You do not need to call this if you already call dismissNotifications.
 */
+ (void)clearBadge NS_AVAILABLE_IOS(6_0);

/*!
 @method dismissNotifications
 @abstract Clear the app's notifications in the notification center. Also clears your badge.
 @discussion Call this when you want to remove the notifications. Your badge is removed afterwards, so if you want one, you need to set it up again.
 */
+ (void)dismissNotifications NS_AVAILABLE_IOS(6_0);

/*!
 @method enableAutomaticDeeplinkHandling:
 @abstract Set whether Batch Push should automatically try to handle deeplinks
 @discussion By default, this is set to YES. You need to call everytime your app is restarted, this option is not persisted.
 @warning If Batch is set to handle your deeplinks, it will *automatically* call the fetch completion handler (if applicable) with UIBackgroundFetchResultNewData.
 */
+ (void)enableAutomaticDeeplinkHandling:(BOOL)handleDeeplinks NS_AVAILABLE_IOS(6_0);

/*!
 @method deeplinkFromUserInfo:
 @abstract Get Batch Push's deeplink from a notification's userInfo.
 @return Batch's Deeplink, or nil if not found.
 */
+ (NSString *)deeplinkFromUserInfo:(NSDictionary *)userData NS_AVAILABLE_IOS(6_0);

/*!
 @method lastKnownPushToken
 @abstract Get the last known push token.
 @warning The returned token might be outdated and invalid if this method is called too early in your application lifecycle.
 @discussion Your application should still register for remote notifications once per launch, in order to keep this value valid.
 @return A push token, nil if unavailable.
 */
+ (NSString *)lastKnownPushToken NS_AVAILABLE_IOS(6_0);

@end
